// *****************************************************************************
#include "UART.h"
// *****************************************************************************
volatile char UART_ReceivedFrame[UART_MAX_COUNT][UART_MAX_FRAME_SIZE] = {'\0'};
volatile char UART_ReceivedFrameHeader[UART_MAX_COUNT][UART_MAX_HEADER_SIZE] = {'\0'};
volatile char UART_FrameHeader[] = UART_MAX_HEADER;
volatile char UART_ReceivedChar[UART_MAX_COUNT];
volatile char UART_IsNewFrameReceived[UART_MAX_COUNT] = {0};
volatile int UART_FrameCounter[UART_MAX_COUNT] = {0};
volatile int UART_ReceivedSize[UART_MAX_COUNT] = {UART_MAX_FRAME_SIZE};
// *****************************************************************************
#ifdef SERIALCOM_USE_UART1

void __attribute__((interrupt, no_auto_psv)) _U1ErrInterrupt(void) {
    char i;

    i = U1RXREG;
    i = U1RXREG;
    i = U1RXREG;
    i = U1RXREG;

    U1STAbits.OERR = 0;
    _U1ERIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
    _U1TXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
    if (U1STAbits.OERR) {
        U1STAbits.OERR = 0;
    }

    if (!U1STAbits.FERR && !U1STAbits.PERR) {
        UART_ReceivedChar[UART1_SELECT] = U1RXREG;

#ifndef UART1_DEBUG_MODE
        char i;
        if (UART_FrameCounter[UART1_SELECT] < UART_MAX_HEADER_SIZE) {
            UART_IsNewFrameReceived[UART1_SELECT] = 0;

            UART_ReceivedFrameHeader[UART1_SELECT][UART_FrameCounter[UART1_SELECT]] = UART_ReceivedChar[UART1_SELECT];
            UART_ReceivedFrame[UART1_SELECT][UART_FrameCounter[UART1_SELECT]] = UART_ReceivedChar[UART1_SELECT];
            UART_FrameCounter[UART1_SELECT]++;

            if (UART_FrameCounter[UART1_SELECT] == UART_MAX_HEADER_SIZE) {
                for (i = 0; i < UART_MAX_HEADER_SIZE; ++i) {
                    if (UART_ReceivedFrameHeader[UART1_SELECT][i] != UART_FrameHeader[i]) {
                        for (i = 0; i < UART_MAX_HEADER_SIZE - 1; ++i) {
                            UART_ReceivedFrameHeader[UART1_SELECT][i] = UART_ReceivedFrameHeader[UART1_SELECT][i + 1];
                        }
                        UART_ReceivedFrameHeader[UART1_SELECT][UART_MAX_HEADER_SIZE - 1] = 0;
                        UART_FrameCounter[UART1_SELECT]--;
                        _U1RXIF = 0;
                        return;
                    }
                }
            }
        } else if (UART_FrameCounter[UART1_SELECT] < UART_ReceivedSize[UART1_SELECT]) {
            UART_ReceivedFrame[UART1_SELECT][UART_FrameCounter[UART1_SELECT]] = UART_ReceivedChar[UART1_SELECT];
            UART_FrameCounter[UART1_SELECT]++;
        }
        if (UART_FrameCounter[UART1_SELECT] == UART_ReceivedSize[UART1_SELECT]) {
            UART_IsNewFrameReceived[UART1_SELECT] = 1;

            for (i = 0; i < UART_MAX_HEADER_SIZE; ++i) {
                UART_ReceivedFrameHeader[UART1_SELECT][i] = 0;
            }
        }
    }
#else
        if (UART_FrameCounter[UART1_SELECT] < UART_ReceivedSize[UART1_SELECT]) {
            UART_ReceivedFrame[UART1_SELECT][UART_FrameCounter[UART1_SELECT]] = UART_ReceivedChar[UART1_SELECT];
            UART_FrameCounter[UART1_SELECT]++;
        }
        if (UART_FrameCounter[UART1_SELECT] == UART_ReceivedSize[UART1_SELECT]) {
            UART_IsNewFrameReceived[UART1_SELECT] = 1;
        }
        if (UART_ReceivedChar[UART1_SELECT] == UART1_ENDPACKET) {
            UART_IsNewFrameReceived[UART1_SELECT] = 1;
        }
    }
#endif
    _U1RXIF = 0;
}

#endif
// *****************************************************************************
#ifdef SERIALCOM_USE_UART2

void __attribute__((interrupt, no_auto_psv)) _U2ErrInterrupt(void) {
    char i;

    i = U2RXREG;
    i = U2RXREG;
    i = U2RXREG;
    i = U2RXREG;

    U2STAbits.OERR = 0;
    _U2ERIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void) {
    _U2TXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void) {
    if (U2STAbits.OERR) {
        U2STAbits.OERR = 0;
    }

    if (!U2STAbits.FERR && !U2STAbits.PERR) {
        UART_ReceivedChar[UART2_SELECT] = U2RXREG;

#ifndef UART2_DEBUG_MODE
        char i;
        if (UART_FrameCounter[UART2_SELECT] < UART_MAX_HEADER_SIZE) {
            UART_IsNewFrameReceived[UART2_SELECT] = 0;
            UART_ReceivedFrame[UART2_SELECT][0] = 0xFF;

            UART_ReceivedFrameHeader[UART2_SELECT][UART_FrameCounter[UART2_SELECT]] = UART_ReceivedChar[UART2_SELECT];
            UART_ReceivedFrame[UART2_SELECT][UART_FrameCounter[UART2_SELECT]] = UART_ReceivedChar[UART2_SELECT];
            UART_FrameCounter[UART2_SELECT]++;

            if (UART_FrameCounter[UART2_SELECT] == UART_MAX_HEADER_SIZE) {
                for (i = 0; i < UART_MAX_HEADER_SIZE; ++i) {
                    if (UART_ReceivedFrameHeader[UART2_SELECT][i] != UART_FrameHeader[i]) {
                        for (i = 0; i < UART_MAX_HEADER_SIZE - 1; ++i) {
                            UART_ReceivedFrameHeader[UART2_SELECT][i] = UART_ReceivedFrameHeader[UART2_SELECT][i + 1];
                        }
                        UART_ReceivedFrameHeader[UART2_SELECT][UART_MAX_HEADER_SIZE - 1] = 0;
                        UART_FrameCounter[UART2_SELECT]--;
                        _U2RXIF = 0;
                        return;
                    }
                }
            }
        } else if (UART_FrameCounter[UART2_SELECT] < UART_ReceivedSize[UART2_SELECT]) {
            UART_ReceivedFrame[UART2_SELECT][UART_FrameCounter[UART2_SELECT]] = UART_ReceivedChar[UART2_SELECT];
            UART_FrameCounter[UART2_SELECT]++;
        }
        if (UART_FrameCounter[UART2_SELECT] == UART_ReceivedSize[UART2_SELECT]) {
            UART_IsNewFrameReceived[UART2_SELECT] = 1;

            for (i = 0; i < UART_MAX_HEADER_SIZE; ++i) {
                UART_ReceivedFrameHeader[UART2_SELECT][i] = 0;
            }
        }
    }
#else
        if (UART_FrameCounter[UART2_SELECT] < UART_ReceivedSize[UART2_SELECT]) {
            UART_ReceivedFrame[UART2_SELECT][UART_FrameCounter[UART2_SELECT]] = UART_ReceivedChar[UART2_SELECT];
            UART_FrameCounter[UART2_SELECT]++;
        }
        if (UART_FrameCounter[UART2_SELECT] == UART_ReceivedSize[UART2_SELECT]) {
            UART_IsNewFrameReceived[UART2_SELECT] = 1;
        }
        if (UART_ReceivedChar[UART2_SELECT] == UART2_ENDPACKET) {
            UART_IsNewFrameReceived[UART2_SELECT] = 1;
        }
    }
#endif
    _U2RXIF = 0;
}

#endif
// *****************************************************************************
#ifdef SERIALCOM_USE_UART3

void __attribute__((interrupt, no_auto_psv)) _U3ErrInterrupt(void) {
    char i;

    i = U3RXREG;
    i = U3RXREG;
    i = U3RXREG;
    i = U3RXREG;

    U3STAbits.OERR = 0;
    _U3ERIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U3TXInterrupt(void) {
    _U3TXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U3RXInterrupt(void) {
    if (U3STAbits.OERR) {
        U3STAbits.OERR = 0;
    }

    if (!U3STAbits.FERR && !U3STAbits.PERR) {
        UART_ReceivedChar[UART3_SELECT] = U3RXREG;

#ifndef UART3_DEBUG_MODE
        char i;
        if (UART_FrameCounter[UART3_SELECT] < UART_MAX_HEADER_SIZE) {
            UART_IsNewFrameReceived[UART3_SELECT] = 0;

            UART_ReceivedFrameHeader[UART3_SELECT][UART_FrameCounter[UART3_SELECT]] = UART_ReceivedChar[UART3_SELECT];
            UART_ReceivedFrame[UART3_SELECT][UART_FrameCounter[UART3_SELECT]] = UART_ReceivedChar[UART3_SELECT];
            UART_FrameCounter[UART3_SELECT]++;

            if (UART_FrameCounter[UART3_SELECT] == UART_MAX_HEADER_SIZE) {
                for (i = 0; i < UART_MAX_HEADER_SIZE; ++i) {
                    if (UART_ReceivedFrameHeader[UART3_SELECT][i] != UART_FrameHeader[i]) {
                        for (i = 0; i < UART_MAX_HEADER_SIZE - 1; ++i) {
                            UART_ReceivedFrameHeader[UART3_SELECT][i] = UART_ReceivedFrameHeader[UART3_SELECT][i + 1];
                        }
                        UART_ReceivedFrameHeader[UART3_SELECT][UART_MAX_HEADER_SIZE - 1] = 0;
                        UART_FrameCounter[UART3_SELECT]--;
                        _U3RXIF = 0;
                        return;
                    }
                }
            }
        } else if (UART_FrameCounter[UART3_SELECT] < UART_ReceivedSize[UART3_SELECT]) {
            UART_ReceivedFrame[UART3_SELECT][UART_FrameCounter[UART3_SELECT]] = UART_ReceivedChar[UART3_SELECT];
            UART_FrameCounter[UART3_SELECT]++;
        }
        if (UART_FrameCounter[UART3_SELECT] == UART_ReceivedSize[UART3_SELECT]) {
            UART_IsNewFrameReceived[UART3_SELECT] = 1;

            for (i = 0; i < UART_MAX_HEADER_SIZE; ++i) {
                UART_ReceivedFrameHeader[UART3_SELECT][i] = 0;
            }
        }
    }
#else
        if (UART_FrameCounter[UART3_SELECT] < UART_ReceivedSize[UART3_SELECT]) {
            UART_ReceivedFrame[UART3_SELECT][UART_FrameCounter[UART3_SELECT]] = UART_ReceivedChar[UART3_SELECT];
            UART_FrameCounter[UART3_SELECT]++;
        }
        if (UART_FrameCounter[UART3_SELECT] == UART_ReceivedSize[UART3_SELECT]) {
            UART_IsNewFrameReceived[UART3_SELECT] = 1;
        }
        if (UART_ReceivedChar[UART3_SELECT] == UART3_ENDPACKET) {
            UART_IsNewFrameReceived[UART3_SELECT] = 1;
        }
    }
#endif
    _U3RXIF = 0;
}
#endif
// *****************************************************************************
#ifdef SERIALCOM_USE_UART4

void __attribute__((interrupt, no_auto_psv)) _U4ErrInterrupt(void) {
    char i;

    i = U4RXREG;
    i = U4RXREG;
    i = U4RXREG;
    i = U4RXREG;

    U4STAbits.OERR = 0;
    _U4ERIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U4TXInterrupt(void) {
    _U4TXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U4RXInterrupt(void) {
    if (U4STAbits.OERR) {
        U4STAbits.OERR = 0;
    }

    if (!U4STAbits.FERR && !U4STAbits.PERR) {
        UART_ReceivedChar[UART4_SELECT] = U4RXREG;

#ifndef UART4_DEBUG_MODE
        char i;
        if (UART_FrameCounter[UART4_SELECT] < UART_MAX_HEADER_SIZE) {
            UART_IsNewFrameReceived[UART4_SELECT] = 0;

            UART_ReceivedFrameHeader[UART4_SELECT][UART_FrameCounter[UART4_SELECT]] = UART_ReceivedChar[UART4_SELECT];
            UART_ReceivedFrame[UART4_SELECT][UART_FrameCounter[UART4_SELECT]] = UART_ReceivedChar[UART4_SELECT];
            UART_FrameCounter[UART4_SELECT]++;

            if (UART_FrameCounter[UART4_SELECT] == UART_MAX_HEADER_SIZE) {
                for (i = 0; i < UART_MAX_HEADER_SIZE; ++i) {
                    if (UART_ReceivedFrameHeader[UART4_SELECT][i] != UART_FrameHeader[i]) {
                        for (i = 0; i < UART_MAX_HEADER_SIZE - 1; ++i) {
                            UART_ReceivedFrameHeader[UART4_SELECT][i] = UART_ReceivedFrameHeader[UART4_SELECT][i + 1];
                        }
                        UART_ReceivedFrameHeader[UART4_SELECT][UART_MAX_HEADER_SIZE - 1] = 0;
                        UART_FrameCounter[UART4_SELECT]--;
                        _U4RXIF = 0;
                        return;
                    }
                }
            }
        } else if (UART_FrameCounter[UART4_SELECT] < UART_ReceivedSize[UART4_SELECT]) {
            UART_ReceivedFrame[UART4_SELECT][UART_FrameCounter[UART4_SELECT]] = UART_ReceivedChar[UART4_SELECT];
            UART_FrameCounter[UART4_SELECT]++;
        }
        if (UART_FrameCounter[UART4_SELECT] == UART_ReceivedSize[UART4_SELECT]) {
            UART_IsNewFrameReceived[UART4_SELECT] = 1;

            for (i = 0; i < UART_MAX_HEADER_SIZE; ++i) {
                UART_ReceivedFrameHeader[UART4_SELECT][i] = 0;
            }
        }
    }
#else
        if (UART_FrameCounter[UART4_SELECT] < UART_ReceivedSize[UART4_SELECT]) {
            UART_ReceivedFrame[UART4_SELECT][UART_FrameCounter[UART4_SELECT]] = UART_ReceivedChar[UART4_SELECT];
            UART_FrameCounter[UART4_SELECT]++;
        }
        if (UART_FrameCounter[UART4_SELECT] == UART_ReceivedSize[UART4_SELECT]) {
            UART_IsNewFrameReceived[UART4_SELECT] = 1;
        }
        if (UART_ReceivedChar[UART4_SELECT] == UART4_ENDPACKET) {
            UART_IsNewFrameReceived[UART4_SELECT] = 1;
        }
    }
#endif
    _U4RXIF = 0;
}
#endif
// *****************************************************************************

void UART_Init(char select) {
    switch (select) {
#ifdef SERIALCOM_USE_UART1
        case UART1_SELECT:
        {
            UART1_SET_TRIS();
            UART_ReceivedSize[UART1_SELECT] = UART_MAX_FRAME_SIZE;

            U1MODEbits.UARTEN = 0; // TX, RX DISABLED, ENABLE
            U1MODEbits.USIDL = 0; // Continue in Idle
            U1MODEbits.IREN = 0; // No IR translation
            U1MODEbits.RTSMD = 0; // Simplex Mode
            U1MODEbits.UEN = 0; // TX,RX enabled, CTS,RTS not
            U1MODEbits.WAKE = 0; // No Wake up (since we don't sleep here)
            U1MODEbits.LPBACK = 0; // No Loop Back
            U1MODEbits.ABAUD = 0; // No Autobaud (would require sending '55')
            //U1MODEbits.URXINV 	= 0;	// IdleState = 1  (for dsPIC)
            U1MODEbits.BRGH = 0; // 16 clocks per bit period
            U1MODEbits.PDSEL = 0; // 8bit, No Parity
            U1MODEbits.STSEL = 0; // One Stop Bit

            U1BRG = ((GetInstructionClock() / UART1_BAUDRATE) / 16) - 1;

            // Configure U1STA
            U1STAbits.UTXISEL1 = 0; // Interrupt when Char is transferred (1/2 config!)
            U1STAbits.UTXISEL0 = 0; // Interrupt after one Tx character is transmitted
            U1STAbits.UTXINV = 0; // IRDA config
            U1STAbits.UTXBRK = 0; // Disabled
            U1STAbits.UTXEN = 0; // TX pins controlled by periph
            U1STAbits.URXISEL = 0; // Interrupt on character received
            U1STAbits.ADDEN = 0; // Address Detect Disabled

            // Configure Interrupt
            _U1TXIE = 0; // Clear the Transmit Interrupt Flag
            _U1TXIF = 0; // Enable Transmit Interrupts
            _U1RXIF = 0; // Clear the Recieve Interrupt Flag
            _U1RXIE = 1; // Enable Recieve Interrupts
            _U1RXIP = 3;
            _U1ERIP = 2;
            _U1ERIF = 0;
            _U1ERIE = 1;

#ifdef UART1_SET_REMAPIO
            __builtin_write_OSCCONL(OSCCON & 0xBF);
            UART1_SET_REMAPIO();
            __builtin_write_OSCCONL(OSCCON | 0x40);
#endif

            // Turn It On...
            U1MODEbits.UARTEN = 1; // And turn the peripheral on
            U1STAbits.UTXEN = 1;

            if (UART1_SERIAL_MODE == SERIALMODE_RS485 || UART1_SERIAL_MODE == SERIALMODE_RS422)
                UART1_SETDIRECTION_RX();
        }
            break;
#endif

#ifdef SERIALCOM_USE_UART2
        case UART2_SELECT:
        {
            UART2_SET_TRIS();
            UART_ReceivedSize[UART2_SELECT] = UART_MAX_FRAME_SIZE;

            U2MODEbits.UARTEN = 0; // TX, RX DISABLED, ENABLE
            U2MODEbits.USIDL = 0; // Continue in Idle
            U2MODEbits.IREN = 0; // No IR translation
            U2MODEbits.RTSMD = 0; // Simplex Mode
            U2MODEbits.UEN = 0; // TX,RX enabled, CTS,RTS not
            U2MODEbits.WAKE = 0; // No Wake up (since we don't sleep here)
            U2MODEbits.LPBACK = 0; // No Loop Back
            U2MODEbits.ABAUD = 0; // No Autobaud (would require sending '55')
            //U2MODEbits.URXINV 	= 0;	// IdleState = 1  (for dsPIC)
            U2MODEbits.BRGH = 0; // 16 clocks per bit period
            U2MODEbits.PDSEL = 0; // 8bit, No Parity
            U2MODEbits.STSEL = 0; // One Stop Bit

            U2BRG = ((GetInstructionClock() / UART2_BAUDRATE) / 16) - 1;

            // Configure U2STA
            U2STAbits.UTXISEL1 = 0; // Interrupt when Char is transferred (1/2 config!)
            U2STAbits.UTXISEL0 = 0; // Interrupt after one Tx character is transmitted
            U2STAbits.UTXINV = 0; // IRDA config
            U2STAbits.UTXBRK = 0; // Disabled
            U2STAbits.UTXEN = 0; // TX pins controlled by periph
            U2STAbits.URXISEL = 0; // Interrupt on character received
            U2STAbits.ADDEN = 0; // Address Detect Disabled

            // Configure Interrupt
            _U2TXIE = 0; // Clear the Transmit Interrupt Flag
            _U2TXIF = 0; // Enable Transmit Interrupts
            _U2RXIF = 0; // Clear the Recieve Interrupt Flag
            _U2RXIE = 1; // Enable Recieve Interrupts
            _U2RXIP = 4;
            _U2ERIP = 5;
            _U2ERIF = 0;
            _U2ERIE = 1;

#ifdef UART2_SET_REMAPIO
            __builtin_write_OSCCONL(OSCCON & 0xBF);
            UART2_SET_REMAPIO();
            __builtin_write_OSCCONL(OSCCON | 0x40);
#endif

            // Turn It On...
            U2MODEbits.UARTEN = 1; // And turn the peripheral on
            U2STAbits.UTXEN = 1;

            if (UART2_SERIAL_MODE == SERIALMODE_RS485 || UART2_SERIAL_MODE == SERIALMODE_RS422)
                UART2_SETDIRECTION_RX();
        }
            break;
#endif

#ifdef SERIALCOM_USE_UART3
        case UART3_SELECT:
        {
            UART3_SET_TRIS();
            UART_ReceivedSize[UART3_SELECT] = UART_MAX_FRAME_SIZE;

            U3MODEbits.UARTEN = 0; // TX, RX DISABLED, ENABLE
            U3MODEbits.USIDL = 0; // Continue in Idle
            U3MODEbits.IREN = 0; // No IR translation
            U3MODEbits.RTSMD = 0; // Simplex Mode
            U3MODEbits.UEN = 0; // TX,RX enabled, CTS,RTS not
            U3MODEbits.WAKE = 0; // No Wake up (since we don't sleep here)
            U3MODEbits.LPBACK = 0; // No Loop Back
            U3MODEbits.ABAUD = 0; // No Autobaud (would require sending '55')
            //U3MODEbits.URXINV 	= 0;	// IdleState = 1  (for dsPIC)
            U3MODEbits.BRGH = 0; // 16 clocks per bit period
            U3MODEbits.PDSEL = 0; // 8bit, No Parity
            U3MODEbits.STSEL = 0; // One Stop Bit

            U3BRG = ((GetInstructionClock() / UART3_BAUDRATE) / 16) - 1;

            // Configure U3STA
            U3STAbits.UTXISEL1 = 0; // Interrupt when Char is transferred (1/2 config!)
            U3STAbits.UTXISEL0 = 0; // Interrupt after one Tx character is transmitted
            U3STAbits.UTXINV = 0; // IRDA config
            U3STAbits.UTXBRK = 0; // Disabled
            U3STAbits.UTXEN = 0; // TX pins controlled by periph
            U3STAbits.URXISEL = 0; // Interrupt on character received
            U3STAbits.ADDEN = 0; // Address Detect Disabled

            // Configure Interrupt
            _U3TXIE = 0; // Clear the Transmit Interrupt Flag
            _U3TXIF = 0; // Enable Transmit Interrupts
            _U3RXIF = 0; // Clear the Recieve Interrupt Flag
            _U3RXIE = 1; // Enable Recieve Interrupts
            _U3RXIP = 4;
            _U3ERIP = 5;
            _U3ERIF = 0;
            _U3ERIE = 1;

#ifdef UART3_SET_REMAPIO
            __builtin_write_OSCCONL(OSCCON & 0xBF);
            UART3_SET_REMAPIO();
            __builtin_write_OSCCONL(OSCCON | 0x40);
#endif

            // Turn It On...
            U3MODEbits.UARTEN = 1; // And turn the peripheral on
            U3STAbits.UTXEN = 1;

            if (UART3_SERIAL_MODE == SERIALMODE_RS485 || UART3_SERIAL_MODE == SERIALMODE_RS422)
                UART3_SETDIRECTION_RX();
        }
            break;
#endif

#ifdef SERIALCOM_USE_UART4
        case UART4_SELECT:
        {
            UART4_SET_TRIS();
            UART_ReceivedSize[UART4_SELECT] = UART_MAX_FRAME_SIZE;

            U4MODEbits.UARTEN = 0; // TX, RX DISABLED, ENABLE
            U4MODEbits.USIDL = 0; // Continue in Idle
            U4MODEbits.IREN = 0; // No IR translation
            U4MODEbits.RTSMD = 0; // Simplex Mode
            U4MODEbits.UEN = 0; // TX,RX enabled, CTS,RTS not
            U4MODEbits.WAKE = 0; // No Wake up (since we don't sleep here)
            U4MODEbits.LPBACK = 0; // No Loop Back
            U4MODEbits.ABAUD = 0; // No Autobaud (would require sending '55')
            //U4MODEbits.URXINV 	= 0;	// IdleState = 1  (for dsPIC)
            U4MODEbits.BRGH = 0; // 16 clocks per bit period
            U4MODEbits.PDSEL = 0; // 8bit, No Parity
            U4MODEbits.STSEL = 0; // One Stop Bit

            U4BRG = ((GetInstructionClock() / UART4_BAUDRATE) / 16) - 1;

            // Configure U4STA
            U4STAbits.UTXISEL1 = 0; // Interrupt when Char is transferred (1/2 config!)
            U4STAbits.UTXISEL0 = 0; // Interrupt after one Tx character is transmitted
            U4STAbits.UTXINV = 0; // IRDA config
            U4STAbits.UTXBRK = 0; // Disabled
            U4STAbits.UTXEN = 0; // TX pins controlled by periph
            U4STAbits.URXISEL = 0; // Interrupt on character received
            U4STAbits.ADDEN = 0; // Address Detect Disabled

            // Configure Interrupt
            _U4TXIE = 0; // Clear the Transmit Interrupt Flag
            _U4TXIF = 0; // Enable Transmit Interrupts
            _U4RXIF = 0; // Clear the Recieve Interrupt Flag
            _U4RXIE = 1; // Enable Recieve Interrupts
            _U4RXIP = 4;
            _U4ERIP = 5;
            _U4ERIF = 0;
            _U4ERIE = 1;

#ifdef UART4_SET_REMAPIO
            __builtin_write_OSCCONL(OSCCON & 0xBF);
            UART4_SET_REMAPIO();
            __builtin_write_OSCCONL(OSCCON | 0x40);
#endif

            // Turn It On...
            U4MODEbits.UARTEN = 1; // And turn the peripheral on
            U4STAbits.UTXEN = 1;

            if (UART4_SERIAL_MODE == SERIALMODE_RS485 || UART4_SERIAL_MODE == SERIALMODE_RS422)
                UART4_SETDIRECTION_RX();
        }
            break;
#endif
    }
}
// *****************************************************************************

void UART_Disable(char select) {
    switch (select) {
#ifdef SERIALCOM_USE_UART1
        case UART1_SELECT:
        {

            U1MODEbits.UARTEN = 0; // And turn the peripheral on
            U1STAbits.UTXEN = 0;
            _U1TXIE = 0; // Clear the Transmit Interrupt Flag
            _U1TXIF = 0; // Enable Transmit Interrupts
        }
            break;
#endif

#ifdef SERIALCOM_USE_UART2
        case UART2_SELECT:
        {

            U2MODEbits.UARTEN = 0; // And turn the peripheral on
            U2STAbits.UTXEN = 0;
            _U2TXIE = 0; // Clear the Transmit Interrupt Flag
            _U2TXIF = 0; // Enable Transmit Interrupts
        }
            break;
#endif

#ifdef SERIALCOM_USE_UART3
        case UART3_SELECT:
        {

            U3MODEbits.UARTEN = 0; // And turn the peripheral on
            U3STAbits.UTXEN = 0;
            _U3TXIE = 0; // Clear the Transmit Interrupt Flag
            _U3TXIF = 0; // Enable Transmit Interrupts
        }
            break;
#endif

#ifdef SERIALCOM_USE_UART4
        case UART4_SELECT:
        {

            U4MODEbits.UARTEN = 0; // And turn the peripheral on
            U4STAbits.UTXEN = 0;
            _U4TXIE = 0; // Clear the Transmit Interrupt Flag
            _U4TXIF = 0; // Enable Transmit Interrupts
        }
            break;
#endif
    }
}
// *****************************************************************************

void UART_Enable(char select) {
    switch (select) {
#ifdef SERIALCOM_USE_UART1
        case UART1_SELECT:
        {
            _U1TXIE = 1; // Clear the Transmit Interrupt Flag
            _U1TXIF = 0; // Enable Transmit Interrupts
            U1MODEbits.UARTEN = 1; // And turn the peripheral on
            U1STAbits.UTXEN = 1;
            U1STAbits.OERR = 0;
        }
            break;
#endif

#ifdef SERIALCOM_USE_UART2
        case UART2_SELECT:
        {
            _U2TXIE = 1; // Clear the Transmit Interrupt Flag
            _U2TXIF = 0; // Enable Transmit Interrupts
            U2MODEbits.UARTEN = 1; // And turn the peripheral on
            U2STAbits.UTXEN = 1;
            U2STAbits.OERR = 0;
        }
            break;
#endif

#ifdef SERIALCOM_USE_UART3
        case UART3_SELECT:
        {
            _U3TXIE = 1; // Clear the Transmit Interrupt Flag
            _U3TXIF = 0; // Enable Transmit Interrupts
            U3MODEbits.UARTEN = 1; // And turn the peripheral on
            U3STAbits.UTXEN = 1;
            U3STAbits.OERR = 0;
        }
            break;
#endif

#ifdef SERIALCOM_USE_UART4
        case UART4_SELECT:
        {
            _U4TXIE = 1; // Clear the Transmit Interrupt Flag
            _U4TXIF = 0; // Enable Transmit Interrupts
            U4MODEbits.UARTEN = 1; // And turn the peripheral on
            U4STAbits.UTXEN = 1;
            U4STAbits.OERR = 0;
        }
            break;
#endif
    }
}
// *****************************************************************************

void UART_SendChar(char select, char sndChar, char mode) {
    switch (select) {
#ifdef SERIALCOM_USE_UART1
        case UART1_SELECT:
        {
            if ((mode == 1) && (UART1_SERIAL_MODE == SERIALMODE_RS422 || UART1_SERIAL_MODE == SERIALMODE_RS485)) {
                UART1_SETDIRECTION_TX();
            }
            U1TXREG = sndChar;
            while (U1STAbits.TRMT == 0);
            if ((mode == 1) && (UART1_SERIAL_MODE == SERIALMODE_RS422 || UART1_SERIAL_MODE == SERIALMODE_RS485)) {
                UART1_SETDIRECTION_RX();
            }
        }
            break;
#endif

#ifdef SERIALCOM_USE_UART2
        case UART2_SELECT:
        {
            if ((mode == 1) && (UART2_SERIAL_MODE == SERIALMODE_RS422 || UART2_SERIAL_MODE == SERIALMODE_RS485)) {
                UART2_SETDIRECTION_TX();
            }
            U2TXREG = sndChar;
            while (U2STAbits.TRMT == 0);
            if ((mode == 1) && (UART2_SERIAL_MODE == SERIALMODE_RS422 || UART2_SERIAL_MODE == SERIALMODE_RS485)) {
                UART2_SETDIRECTION_RX();
            }
        }
            break;
#endif

#ifdef SERIALCOM_USE_UART3
        case UART3_SELECT:
        {
            if ((mode == 1) && (UART3_SERIAL_MODE == SERIALMODE_RS422 || UART3_SERIAL_MODE == SERIALMODE_RS485)) {
                UART3_SETDIRECTION_TX();
            }
            U3TXREG = sndChar;
            while (U3STAbits.TRMT == 0);
            if ((mode == 1) && (UART3_SERIAL_MODE == SERIALMODE_RS422 || UART3_SERIAL_MODE == SERIALMODE_RS485)) {
                UART3_SETDIRECTION_RX();
            }
        }
            break;
#endif

#ifdef SERIALCOM_USE_UART4
        case UART4_SELECT:
        {
            if ((mode == 1) && (UART4_SERIAL_MODE == SERIALMODE_RS422 || UART4_SERIAL_MODE == SERIALMODE_RS485)) {
                UART4_SETDIRECTION_TX();
            }
            U4TXREG = sndChar;
            while (U4STAbits.TRMT == 0);
            if ((mode == 1) && (UART4_SERIAL_MODE == SERIALMODE_RS422 || UART4_SERIAL_MODE == SERIALMODE_RS485)) {
                UART4_SETDIRECTION_RX();
            }
        }
            break;
#endif
    }
}
// *****************************************************************************

void UART_SendString(char select, char* sndStr) {
    switch (select) {
#ifdef SERIALCOM_USE_UART1
        case UART1_SELECT:
        {
            UART1_SETDIRECTION_TX();
            while (*sndStr != '\0') {
                UART_SendChar(select, *sndStr, 0);
                sndStr++;
            }
            UART1_SETDIRECTION_RX();
        }
            break;
#endif

#ifdef SERIALCOM_USE_UART2
        case UART2_SELECT:
        {
            UART2_SETDIRECTION_TX();
            while (*sndStr != '\0') {
                UART_SendChar(select, *sndStr, 0);
                sndStr++;
            }
            UART2_SETDIRECTION_RX();
        }
            break;
#endif
#ifdef SERIALCOM_USE_UART3
        case UART3_SELECT:
        {
            UART3_SETDIRECTION_TX();
            while (*sndStr != '\0') {
                UART_SendChar(select, *sndStr, 0);
                sndStr++;
            }
            UART3_SETDIRECTION_RX();
        }
            break;
#endif

#ifdef SERIALCOM_USE_UART4
        case UART4_SELECT:
        {
            UART4_SETDIRECTION_TX();
            while (*sndStr != '\0') {
                UART_SendChar(select, *sndStr, 0);
                sndStr++;
            }
            UART4_SETDIRECTION_RX();
        }
            break;
#endif
    }
}
// *****************************************************************************

void UART_SendStringByLength(char select, char* sndStr, int len) {
    int i;
    switch (select) {
#ifdef SERIALCOM_USE_UART1
        case UART1_SELECT:
        {
            UART1_SETDIRECTION_TX();
            for (i = 0; i < len; ++i) {
                UART_SendChar(select, sndStr[i], 0);
            }
            UART1_SETDIRECTION_RX();
        }
            break;
#endif

#ifdef SERIALCOM_USE_UART2
        case UART2_SELECT:
        {
            UART2_SETDIRECTION_TX();
            for (i = 0; i < len; ++i) {
                UART_SendChar(select, sndStr[i], 0);
            }
            UART2_SETDIRECTION_RX();
        }
            break;
#endif
#ifdef SERIALCOM_USE_UART3
        case UART3_SELECT:
        {
            UART3_SETDIRECTION_TX();
            for (i = 0; i < len; ++i) {
                UART_SendChar(select, sndStr[i], 0);
            }
            UART3_SETDIRECTION_RX();
        }
            break;
#endif

#ifdef SERIALCOM_USE_UART4
        case UART4_SELECT:
        {
            UART4_SETDIRECTION_TX();
            for (i = 0; i < len; ++i) {
                UART_SendChar(select, sndStr[i], 0);
            }
            UART4_SETDIRECTION_RX();
        }
            break;
#endif
    }
}
// *****************************************************************************

char UART_IsNewFrameReceive(char select) {
    if (select >= 0 && select < UART_MAX_COUNT)
        return UART_IsNewFrameReceived[select];
}
// *****************************************************************************

void UART_ClearFrameReceive(char select) {
    if (select >= 0 && select < UART_MAX_COUNT) {
        UART_IsNewFrameReceived[select] = 0;
        UART_FrameCounter[select] = 0;
    }
}
// *****************************************************************************

void UART_SetReceive(char select, int size) {
    if (select >= 0 && select < UART_MAX_COUNT) {
        UART_ReceivedSize[select] = size;
    }
}

// *****************************************************************************

void UART_SetReceiveLenght(char select, int size) {
    if (select >= 0 && select < UART_MAX_COUNT) {
        UART_ReceivedSize[select] = size;
    }
}
// *****************************************************************************

char* UART_GetReceiveFrame(char select) {
    if (select >= 0 && select < UART_MAX_COUNT) {
        return (char*) &UART_ReceivedFrame[select][0];
    }
}

// *****************************************************************************

int UART_GetReceiveCounter(char select) {
    if (select >= 0 && select < UART_MAX_COUNT) {
        return UART_FrameCounter[select];
    }
}
// *****************************************************************************
