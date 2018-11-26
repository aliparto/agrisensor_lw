// *****************************************************************************
#include "Modbus.h"
#include "UART.h"
// *****************************************************************************
#define MODBUS_IDLE                     1
#define MODBUS_WAITING_FOR_REPLY        2
#define MODBUS_WAITING_FOR_TURNAROUND   3

#define MODBUS_BUFFER_SIZE              UART_MAX_FRAME_SIZE
// *****************************************************************************
unsigned char ModBus_State[UART_MAX_COUNT];
unsigned char ModBus_RetryCount[UART_MAX_COUNT];
unsigned char* ModBus_Frame[UART_MAX_COUNT];
unsigned char ModBus_Buffer[UART_MAX_COUNT];
unsigned int ModBus_Timeout[UART_MAX_COUNT];
unsigned int ModBus_Polling[UART_MAX_COUNT];
unsigned long ModBus_StartDelay[UART_MAX_COUNT];
ModBusPacket* ModBus_Packet[UART_MAX_COUNT];
// *****************************************************************************
void ModBus_Idle(char select);
void ModBus_ConstructPacket(char select);
unsigned char ModBus_ConstructMultipleCoils(char select);
unsigned char ModBus_ConstructMultipleRegisters(char select);
void ModBus_WaitingForReply(char select);
void ModBus_ProcessReply(char select);
void ModBus_WaitingForTurnaround(char select);
void ModBus_ProcessStatus(char select);
void ModBus_ProcessRegister(char select);
void ModBus_ProcessMultiple(char select);
void ModBus_ProcessError(char select);
void ModBus_ProcessSuccess(char select);
unsigned int ModBus_CalculateCRC(char select, unsigned char bufferSize);
void ModBus_Send(char select, unsigned char bufferSize);
// *****************************************************************************
unsigned long ModBus_MiliSecond = 0;

void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void) {
    _T2IF = 0;
    ModBus_MiliSecond++;
}
// *****************************************************************************

void ModBus_Configure(char select, unsigned int timeout, unsigned int polling, unsigned char retrycount) {
    ModBus_State[select] = MODBUS_IDLE;
    ModBus_Timeout[select] = timeout;
    ModBus_Polling[select] = polling;
    ModBus_RetryCount[select] = retrycount;

    UART_Init(select);
    ModBus_Frame[select] = (unsigned char*) UART_GetReceiveFrame(select);

    static char bIsTimerSet = 0;
    if (bIsTimerSet == 0) {
        bIsTimerSet = 1;

        T2CONbits.TON = 0;
        T2CONbits.TCKPS = 0b11; // 1:256
        TMR4 = 0x00;
        PR2 = 1 * (GetInstructionClock() / 256 / 1000); // 1ms
        _T2IP = 0x01;
        _T2IF = 0;
        _T2IE = 1;
        T2CONbits.TON = 1;
    }
}
// *****************************************************************************

void ModBus_Construct(char select, ModBusPacket *_packet, unsigned char id, unsigned char function,
        unsigned int address, unsigned int data, unsigned int* register_array) {
    _packet->id = id;
    _packet->function = function;
    _packet->address = address;
    _packet->data = data;
    _packet->register_array = register_array;
    _packet->connection = 1;
    ModBus_Packet[select] = _packet;
}
// *****************************************************************************

void ModBus_Update() {
    char iSelect;
    for (iSelect = 0; iSelect < UART_MAX_COUNT; ++iSelect) {
        switch (ModBus_State[iSelect]) {
            case MODBUS_IDLE:
                ModBus_Idle(iSelect);
                break;
            case MODBUS_WAITING_FOR_REPLY:
                ModBus_WaitingForReply(iSelect);
                break;
            case MODBUS_WAITING_FOR_TURNAROUND:
                ModBus_WaitingForTurnaround(iSelect);
                break;
        }
    }
}
// *****************************************************************************

void ModBus_Idle(char select) {
    if (ModBus_Packet[select]->connection) {
        ModBus_ConstructPacket(select);
    }
}
// *****************************************************************************

void ModBus_ConstructPacket(char select) {
    ModBus_Packet[select]->requests++;
    ModBus_Frame[select][0] = ModBus_Packet[select]->id;
    ModBus_Frame[select][1] = ModBus_Packet[select]->function;
    ModBus_Frame[select][2] = ModBus_Packet[select]->address >> 8; // address Hi
    ModBus_Frame[select][3] = ModBus_Packet[select]->address & 0xFF; // address Lo
    ModBus_Frame[select][4] = ModBus_Packet[select]->data >> 8; // MSB
    ModBus_Frame[select][5] = ModBus_Packet[select]->data & 0xFF; // LSB

    unsigned char frameSize;

    if (ModBus_Packet[select]->function == MODBUS_PRESET_MULTIPLE_REGISTERS)
        frameSize = ModBus_ConstructMultipleRegisters(select);
    else if (ModBus_Packet[select]->function == MODBUS_FORCE_MULTIPLE_COILS)
        frameSize = ModBus_ConstructMultipleCoils(select);
    else
        frameSize = 8;

    unsigned int crc16 = ModBus_CalculateCRC(select, frameSize - 2);
    ModBus_Frame[select][frameSize - 2] = crc16 >> 8;
    ModBus_Frame[select][frameSize - 1] = crc16 & 0xFF;
    ModBus_Send(select, frameSize);

    ModBus_State[select] = MODBUS_WAITING_FOR_REPLY;

    if (ModBus_Packet[select]->id == 0)
        ModBus_ProcessSuccess(select);
}
// *****************************************************************************

unsigned char ModBus_ConstructMultipleCoils(char select) {
    unsigned char no_of_registers = ModBus_Packet[select]->data / 16;
    unsigned char no_of_bytes = no_of_registers * 2;

    // if the number of points dont fit in even 2byte amounts (one register) then use another register and pad
    if (ModBus_Packet[select]->data % 16 > 0) {
        no_of_registers++;
        no_of_bytes++;
    }

    ModBus_Frame[select][6] = no_of_bytes;
    unsigned char bytes_processed = 0;
    unsigned char index = 7; // user data starts at index 7
    unsigned int temp;
    unsigned char i;

    for (i = 0; i < no_of_registers; i++) {
        temp = ModBus_Packet[select]->register_array[i]; // get the data
        ModBus_Frame[select][index] = temp & 0xFF;
        bytes_processed++;

        if (bytes_processed < no_of_bytes) {
            ModBus_Frame[select][index + 1] = temp >> 8;
            bytes_processed++;
            index += 2;
        }
    }
    unsigned char frameSize = (9 + no_of_bytes); // first 7 bytes of the array + 2 bytes CRC + noOfBytes
    return frameSize;
}
// *****************************************************************************

unsigned char ModBus_ConstructMultipleRegisters(char select) {
    unsigned char no_of_bytes = ModBus_Packet[select]->data * 2;

    ModBus_Frame[select][6] = no_of_bytes; // number of bytes
    unsigned char index = 7; // user data starts at index 7
    unsigned char no_of_registers = ModBus_Packet[select]->data;
    unsigned int temp;
    unsigned char i;

    for (i = 0; i < no_of_registers; i++) {
        temp = ModBus_Packet[select]->register_array[i]; // get the data
        ModBus_Frame[select][index] = temp >> 8;
        index++;
        ModBus_Frame[select][index] = temp & 0xFF;
        index++;
    }
    unsigned char frameSize = (9 + no_of_bytes); // first 7 bytes of the array + 2 bytes CRC + noOfBytes
    return frameSize;
}
// *****************************************************************************

void ModBus_WaitingForTurnaround(char select) {
    if ((ModBus_MiliSecond - ModBus_StartDelay[select]) > ModBus_Polling[select])
        ModBus_State[select] = MODBUS_IDLE;
}
// *****************************************************************************

void ModBus_WaitingForReply(char select) {
    if (UART_GetReceiveCounter(select) > 4) {
        char* p = UART_GetReceiveFrame(select);
        ModBus_Buffer[select] = UART_GetReceiveCounter(select);
        int i = 0;
        for (i = 0; i < ModBus_Buffer[select]; ++i) {
            ModBus_Frame[select][i] = p[i];
        }
        UART_ClearFrameReceive(select);

        if (ModBus_Frame[select][0] != ModBus_Packet[select]->id) {
            ModBus_ProcessError(select);
        } else {
            ModBus_ProcessReply(select);
        }
    }
    if ((ModBus_MiliSecond - ModBus_StartDelay[select]) > ModBus_Timeout[select]) {
        ModBus_ProcessError(select);
        ModBus_State[select] = MODBUS_IDLE;
    }
}
// *****************************************************************************

void ModBus_ProcessReply(char select) {
    unsigned int received_crc = ((ModBus_Frame[select][ModBus_Buffer[select] - 2] << 8) | ModBus_Frame[select][ModBus_Buffer[select] - 1]);
    unsigned int calculated_crc = ModBus_CalculateCRC(select, ModBus_Buffer[select] - 2);

    if (calculated_crc == received_crc) {
        if ((ModBus_Frame[select][1] & 0x80) == 0x80) {
            ModBus_Packet[select]->exception_errors++;
            ModBus_ProcessError(select);
        } else {
            switch (ModBus_Frame[select][1]) {
                case MODBUS_READ_COIL_STATUS:
                case MODBUS_READ_INPUT_STATUS:
                    ModBus_ProcessStatus(select);
                    break;
                case MODBUS_READ_INPUT_REGISTERS:
                case MODBUS_READ_HOLDING_REGISTERS:
                    ModBus_ProcessRegister(select);
                    break;
                case MODBUS_FORCE_MULTIPLE_COILS:
                case MODBUS_PRESET_MULTIPLE_REGISTERS:
                    ModBus_ProcessMultiple(select);
                    break;
                default: // illegal function returned
                    ModBus_ProcessError(select);
                    break;
            }
        }
    } else // checksum failed
    {
        ModBus_ProcessError(select);
    }
}
// *****************************************************************************

void ModBus_ProcessStatus(char select) {
    unsigned char no_of_registers = ModBus_Packet[select]->data / 16;
    unsigned char number_of_bytes = no_of_registers * 2;

    if (ModBus_Packet[select]->data % 16 > 0) {
        no_of_registers++;
        number_of_bytes++;
    }

    if (ModBus_Frame[select][2] == number_of_bytes) {
        unsigned char bytes_processed = 0;
        unsigned char index = 3;
        unsigned int temp;
        unsigned char i;

        for (i = 0; i < no_of_registers; i++) {
            temp = ModBus_Frame[select][index];
            bytes_processed++;
            if (bytes_processed < number_of_bytes) {
                temp = (ModBus_Frame[select][index + 1] << 8) | temp;
                bytes_processed++;
                index += 2;
            }
            ModBus_Packet[select]->register_array[i] = temp;
        }
        ModBus_ProcessSuccess(select);
    } else
        ModBus_ProcessError(select);
}
// *****************************************************************************

void ModBus_ProcessRegister(char select) {
    if (ModBus_Frame[select][2] == (ModBus_Packet[select]->data * 2)) {
        unsigned char index = 3;
        unsigned char i;
        for (i = 0; i < ModBus_Packet[select]->data; i++) {
            ModBus_Packet[select]->register_array[i] = (ModBus_Frame[select][index] << 8) | ModBus_Frame[select][index + 1];
            index += 2;
        }
        ModBus_ProcessSuccess(select);
    } else
        ModBus_ProcessError(select);
}
// *****************************************************************************

void ModBus_ProcessMultiple(char select) {
    unsigned int recieved_address = ((ModBus_Frame[select][2] << 8) | ModBus_Frame[select][3]);
    unsigned int recieved_data = ((ModBus_Frame[select][4] << 8) | ModBus_Frame[select][5]);

    if ((recieved_address == ModBus_Packet[select]->address) && (recieved_data == ModBus_Packet[select]->data))
        ModBus_ProcessSuccess(select);
    else
        ModBus_ProcessError(select);
}
// *****************************************************************************

void ModBus_ProcessError(char select) {
    ModBus_Packet[select]->retries++;
    ModBus_Packet[select]->failed_requests++;

    if (ModBus_Packet[select]->retries == ModBus_RetryCount[select]) {
        ModBus_Packet[select]->connection = 0;
        ModBus_Packet[select]->retries = 0;
    }
    ModBus_State[select] = MODBUS_WAITING_FOR_TURNAROUND;
    ModBus_StartDelay[select] = ModBus_MiliSecond;
}
// *****************************************************************************

void ModBus_ProcessSuccess(char select) {
    ModBus_Packet[select]->successful_requests++;
    ModBus_Packet[select]->retries = 0;
    ModBus_State[select] = MODBUS_WAITING_FOR_TURNAROUND;
    ModBus_StartDelay[select] = ModBus_MiliSecond;
}
// *****************************************************************************

unsigned int ModBus_CalculateCRC(char select, unsigned char bufferSize) {
    unsigned int temp, temp2, flag;
    temp = 0xFFFF;
    unsigned char i, j;

    for (i = 0; i < bufferSize; i++) {
        temp = temp ^ ModBus_Frame[select][i];
        for (j = 1; j <= 8; j++) {
            flag = temp & 0x0001;
            temp >>= 1;
            if (flag)
                temp ^= 0xA001;
        }
    }
    // Reverse byte order.
    temp2 = temp >> 8;
    temp = (temp << 8) | temp2;
    temp &= 0xFFFF;

    return temp;
}
// *****************************************************************************

void ModBus_Send(char select, unsigned char bufferSize) {
    UART_ClearFrameReceive(select);
    UART_SendStringByLength(select, ModBus_Frame[select], bufferSize);
}
// *****************************************************************************
