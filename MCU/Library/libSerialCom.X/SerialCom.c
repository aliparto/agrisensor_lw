// *****************************************************************************
#include "SerialCom.h"
// *****************************************************************************
char SerialCom_IsSetReceived[UART_MAX_COUNT] = {0};
// *****************************************************************************

void SerialCom_Init(char select) {
    UART_Init(select);
}
// *****************************************************************************

void SerialCom_WriteByLength(char select, char* str, int len) {
    UART_ClearFrameReceive(select);
    UART_SendStringByLength(select, (unsigned char*) str, len);
}
// *****************************************************************************

void SerialCom_SetEnable(char select) {
    UART_Enable(select);
}
// *****************************************************************************

void SerialCom_SetDisable(char select) {
    UART_Disable(select);
}
// *****************************************************************************

char SerialCom_IsNewFrameReceive(char select) {
    return (UART_IsNewFrameReceive(select));
}
// *****************************************************************************

void SerialCom_ClearFrameReceive(char select) {
    UART_ClearFrameReceive(select);
}
// *****************************************************************************

void SerialCom_SetReceive(char select, int size) {
    UART_SetReceive(select, size);
}
// *****************************************************************************
char SerialCom_GetFrame(char select, char* pRecChar, int length) {
    if (SerialCom_IsSetReceived[select] == 0) {
        SerialCom_IsSetReceived[select] = 1;
        UART_SetReceive(select, length);
    }
    if (SerialCom_IsNewFrameReceive(select)) {
        char* pC = UART_GetReceiveFrame(select);
        int i;
        for (i = 0; i < length; ++i) {
            pRecChar[i] = pC[i];
        }
        SerialCom_ClearFrameReceive(select);
        SerialCom_IsSetReceived[select] = 0;
        return 1;
    }
    return 0;
}
// *****************************************************************************
