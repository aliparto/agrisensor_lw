// *****************************************************************************
#include "SoilMoisture.h"
// *****************************************************************************
#define SOILMOISTURE_READTRY        1
// *****************************************************************************
volatile char SoilMoisture_TimeOut = 0;

void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void) {
    SoilMoisture_TimeOut = 1;
    _T2IF = 0;
}
// *****************************************************************************

void SoilMoisture_Init() {
    SOILMOINSTURE_TRIS = 1;
    SOILMOINSTURE_PIN = 1;

    //--- Timer
    T1CON = 0;
    TMR1 = 0x0000;
    PR1 = 0xFFFF;
    _T1IP = 0x01;
    _T1IF = 0;
    _T1IE = 1;
    T1CONbits.TON = 0;
}
// *****************************************************************************

float SoilMoisture_ReadTime() {
    float fValue = 0.0f;

    while (SOILMOINSTURE_PIN == 0);
    while (SOILMOINSTURE_PIN == 1);
    while (SOILMOINSTURE_PIN == 0);
    SoilMoisture_TimeOut = 0;
    TMR1 = 0x0000;
    PR1 = 0xFFFF;
    T1CONbits.TON = 1;
    while (SoilMoisture_TimeOut == 0 && SOILMOINSTURE_PIN == 1);
    while (SoilMoisture_TimeOut == 0 && SOILMOINSTURE_PIN == 0);
    T1CONbits.TON = 0;
    if (SoilMoisture_TimeOut) {
        fValue = 0.0f;
    } else {
        fValue = (float) TMR1;
        fValue *= 1000000.0f;
        fValue /= (float) GetInstructionClock();
    }
    return fValue;
}
// *****************************************************************************

float SoilMoisture_Read() {
    float value = 100.0f;
    float tmpvalue = 100.0f;
    int i;
    for (i = 0; i < SOILMOISTURE_READTRY; ++i) {
        tmpvalue = (SoilMoisture_ReadTime() - 10.0f)  * 0.75f;
        if (tmpvalue < value) {
            value = tmpvalue;
        }
    }
    if (value > 100.0f) {
        value = 100.0f;
    }
    if (value < 0.0f) {
        value = 0.0f;
    }
    return value;
}
// *****************************************************************************
