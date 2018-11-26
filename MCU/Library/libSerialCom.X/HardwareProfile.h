//******************************************************************************
#ifndef __HARDWARE_PROFILE_SERIALCOM_H__
#define __HARDWARE_PROFILE_SERIALCOM_H__
//******************************************************************************
#include "../ClockConfig.h"
#include "Common/Delay.h"
//******************************************************************************
#define SERIALCOM_USE_UART2
#define UART_MAX_COUNT                  2
#define UART_MAX_FRAME_SIZE             64
#define UART_MAX_HEADER_SIZE            2
#define UART_MAX_HEADER                 {0xFF, 0xAA}      
        
#define UART1_TX_TRIS                   _TRISC1
#define UART1_RX_TRIS                   _TRISC0
#define UART1_DR_TRIS                   _TRISB2
#define UART1_DR_LAT                    _LATB2
#define UART2_TX_TRIS                   _TRISB0
#define UART2_RX_TRIS                   _TRISB1
#define UART2_DR_TRIS                   _TRISB2
#define UART2_DR_LAT                    _LATB2
//******************************************************************************
#define UART1_SELECT                    0
#define UART2_SELECT                    1

#define SERIALMODE_RS232                1
#define SERIALMODE_RS422                2
#define SERIALMODE_RS485                3
#define SERIALMODE_RS485_FD             4

#define SERIAL_RS485_DELAY()            __delay32((long)(GetInstructionClock()/1000UL))
//******************************************************************************
#ifdef SERIALCOM_USE_UART1
#define UART1_BAUDRATE                  9600
#define UART1_SET_REMAPIO()             UART1_TX_REMAP = 3; _U1RXR = UART1_RX_REMAP;
#define UART1_SET_TRIS()                UART1_TX_TRIS = 0; UART1_RX_TRIS = 1;
#define UART1_SERIAL_MODE               SERIALMODE_RS485
#define UART1_SETDIRECTION_RX()         {SERIAL_RS485_DELAY(); UART1_DR_TRIS = 0; UART1_DR_LAT = 0;}
#define UART1_SETDIRECTION_TX()         {SERIAL_RS485_DELAY(); SERIAL_RS485_DELAY(); UART1_DR_TRIS = 0; UART1_DR_LAT = 1; SERIAL_RS485_DELAY();}
#endif
#ifdef SERIALCOM_USE_UART2
#define UART2_BAUDRATE                  9600
#define UART2_SET_TRIS()                UART2_TX_TRIS = 0; UART2_RX_TRIS = 1;
#define UART2_FRAME_SIZE                UART_MAX_FRAME_SIZE
#define UART2_SERIAL_MODE               SERIALMODE_RS485
#define UART2_SETDIRECTION_RX()         {SERIAL_RS485_DELAY(); UART2_DR_TRIS = 0; UART2_DR_LAT = 0;}
#define UART2_SETDIRECTION_TX()         {SERIAL_RS485_DELAY(); SERIAL_RS485_DELAY(); UART2_DR_TRIS = 0; UART2_DR_LAT = 1; SERIAL_RS485_DELAY();}
#endif
//******************************************************************************
#endif
//******************************************************************************

