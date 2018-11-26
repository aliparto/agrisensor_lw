// *****************************************************************************
#ifndef __CLOCK_CONFIG_H__
#define __CLOCK_CONFIG_H__
// *****************************************************************************
#include <p24Fxxxx.h>
#include <libpic30.h>
// *****************************************************************************
#define GetSystemClock()        (8000000UL)   //->FOSC
#define GetPeripheralClock()    (GetSystemClock() / 2)
#define GetInstructionClock()   (GetSystemClock() / 2) //->FOSC/2
#define FCY()                    GetPeripheralClock()
#define NOP()                   {__asm__ volatile ("nop");}
// *****************************************************************************

#endif
