#include <OneWire.h>
#include <DallasTemperature.h>
#include "ports.h"

enum class TempType {
  F,
  C,
  K
};

class Temperature {
  public:
    Temperature();
    int DeviceCount();
    float Temp(TempType tt, int device);
    void Setup();
  private:
    OneWire _oneWire;
    DallasTemperature _sensors;
    int _deviceCount = 0;
    float tempF(int device);
    float tempC(int device);
    float tempK(int device);
};
