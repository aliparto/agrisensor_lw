/*********************************************************************
 *
 *	Hardware specific definitions
 *
 *********************************************************************/
#ifndef __SERIAL_COM_H__
#define __SERIAL_COM_H__
// *****************************************************************************
#include "UART.h"
// *****************************************************************************
#define DEBUG_MODE
// *****************************************************************************
void SerialCom_Init(char select);
void SerialCom_SetEnable(char select);
void SerialCom_SetDisable(char select);
void SerialCom_WriteByLength(char select, char* str, int len);

char SerialCom_IsNewFrameReceive(char select);
void SerialCom_ClearFrameReceive(char select);
void SerialCom_SetReceive(char select, int size);
char SerialCom_GetFrame(char select, char* pRecChar, int length);
// *****************************************************************************
#endif

