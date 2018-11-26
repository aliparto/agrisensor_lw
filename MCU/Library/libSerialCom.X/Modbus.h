#ifndef __MODBUS_H__
#define __MODBUS_H__
// *****************************************************************************
#include "HardwareProfile.h"
// *****************************************************************************
#define MODBUS_READ_COIL_STATUS            1
#define MODBUS_READ_INPUT_STATUS           2
#define MODBUS_READ_HOLDING_REGISTERS      3
#define MODBUS_READ_INPUT_REGISTERS        4
#define MODBUS_FORCE_MULTIPLE_COILS        15
#define MODBUS_PRESET_MULTIPLE_REGISTERS   16
// *****************************************************************************

typedef struct {
    // specific packet info
    unsigned char id;
    unsigned char function;
    unsigned int address;
    // For functions 1 & 2 data is the number of points
    // For functions 3, 4 & 16 data is the number of registers
    // For function 15 data is the number of coils
    unsigned int data;
    unsigned int* register_array;

    // modbus information counters
    unsigned int requests;
    unsigned int successful_requests;
    unsigned int failed_requests;
    unsigned int exception_errors;
    unsigned int retries;

    // connection status of packet
    unsigned char connection;

} ModBusPacket;

typedef ModBusPacket* ModBusPacketPointer;
// *****************************************************************************
void ModBus_Configure(char select, unsigned int timeout, unsigned int polling, unsigned char retrycount);
void ModBus_Construct(char select, ModBusPacket *_packet, unsigned char id, unsigned char function,
        unsigned int address, unsigned int data, unsigned int* register_array);
void ModBus_Update();
// *****************************************************************************
#endif
