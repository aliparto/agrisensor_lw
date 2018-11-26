//******************************************************************************#include "../Library/libSerialCom.X/SerialCom.h"#include "../Library/libSoilMoisture.X/SoilMoisture.h"//******************************************************************************void Initialize();void Run();void InitIOs();char HeaderFooterIsOK(unsigned char* packet, int length);char CheckSumIsOK(unsigned char* packet, int length);void SetCheckSum(unsigned char* packet, int length);void HandleCommunication();void ReadSensors();void SendData();//******************************************************************************