/*
  DM02A.h - Library for use with DM02A - MSS ELETRONICA
  MIT License
  ---------------------------------------
  English Version
*/
 
#ifndef DM02A_h
#define DM02A_h
 
#include <Arduino.h>

class DM02A{
    
  public:
    DM02A();
    DM02A(uint8_t pinSIG, uint8_t pinCH, uint8_t pinEN);
    DM02A(uint8_t pinSIG, uint8_t pinCH);
    void SendLevel(uint8_t _level, uint8_t _channel);
    uint8_t Feedback(uint8_t _channel);
 
    private:
      uint8_t _pinSIG;
      uint8_t _pinCH;
      uint8_t _pinEN;
      uint8_t _EN;
      uint32_t _pulse;
      uint8_t _cont;
      
};

#endif
