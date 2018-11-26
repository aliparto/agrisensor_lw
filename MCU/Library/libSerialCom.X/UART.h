// *****************************************************************************
#include "HardwareProfile.h"
// *****************************************************************************
void UART_Init(char select);
void UART_SendChar(char select, char sndChar, char mode);
void UART_SendStringByLength(char select, char* sndStr, int len);
char* UART_GetReceiveFrame(char select);
void UART_Enable(char select);
void UART_Disable(char select);
char UART_IsNewFrameReceive(char select);
void UART_ClearFrameReceive(char select);
void UART_SetReceive(char select, int size);
void UART_SetReceiveLenght(char select, int size);
char* UART_GetReceiveFrame(char select);
int UART_GetReceiveCounter(char select);
// *****************************************************************************
