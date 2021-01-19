#include <OneWire.h>
#include <DallasTemperature.h>
#include "ports.h"
#include "temperature.h"

Temperature::Temperature()
{
  this->_oneWire = OneWire(ONE_WIRE_BUS);
  this->_sensors = DallasTemperature(&this->_oneWire);
}

void Temperature::Setup() {
  this->_deviceCount = this->_sensors.getDeviceCount();
}

int Temperature::DeviceCount() {
  return this->_deviceCount;
}

float Temperature::tempF(int device){
  const uint8_t* c;
  c += device;
  return this->_sensors.getTempF(c);
}
float Temperature::tempC(int device){
  const uint8_t* c;
  c += device;
  return this->_sensors.getTempC(c);
}
float Temperature::tempK(int device){
  float tc = tempC(device);
  float tk = tc + 273.15;
  return tk;
}

float Temperature::Temp(TempType tt, int device) {
  float temp;
  switch(tt)
  {
    case TempType::C:
      temp = tempC(device);
      break;
    case TempType::F:
      temp = tempF(device);
      break;
    default:
      temp = tempK(device);
      break;
  }

  return temp;
}
