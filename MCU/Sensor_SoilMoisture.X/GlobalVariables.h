// *****************************************************************************
#include "../Library/ClockConfig.h"
// *****************************************************************************
#ifndef __GLOBAL_VARIABLES_H__
#define __GLOBAL_VARIABLES_H__
// *****************************************************************************
typedef enum {
    SensorType_Temperature = 1,
    SensorType_Humidity,
    SensorType_Pressure,
    SensorType_SoilTemperature,
    SensorType_SoilMoisture,
    SensorType_Luminosity,
    SensorType_Radiation,
    SensorType_Pluviometer,
    SensorType_WindVane,
    SensorType_Anemometer,
    SensorType_pH,
    SensorType_Nitrate,
    SensorType_UV,
} SensorType;

typedef struct {
    unsigned int ID;
    char Status;
    char Type;
    float Value;
} Sensor;

typedef struct
{
    char            Header[2];
    char            MAC[8];
    char            Status;
    char            SensorID;
    char            Type;
    char            Location;
    short           Sensitivity;
    short           Calibration;
    float           Value;
    char            Reserved[4];
    char            CheckSum[4];
    char            Footer[2];
} PaketSensor;
// *****************************************************************************
#endif
