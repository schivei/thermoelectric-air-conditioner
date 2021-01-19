/*
  DM02A.cpp - Library for use with DM02A - MSS ELETRONICA
  MIT License
  ---------------------------------------
  English Version
*/
 
#include "DM02A.h"
 
DM02A::DM02A(){}

DM02A::DM02A(uint8_t pinSIG, uint8_t pinCH, uint8_t pinEN)
{
  pinMode(pinSIG, OUTPUT);
  pinMode(pinCH, OUTPUT);
  pinMode(pinEN, OUTPUT);
  digitalWrite(pinCH,LOW);
  digitalWrite(pinSIG,HIGH);
  digitalWrite(pinEN,LOW);
  _EN = 1;
  _pinSIG = pinSIG;
  _pinCH = pinCH;
  _pinEN = pinEN;
}

DM02A::DM02A(uint8_t pinSIG, uint8_t pinCH)
{
  pinMode(pinSIG, OUTPUT);
  pinMode(pinCH, OUTPUT); 
  digitalWrite(pinCH,LOW);
  digitalWrite(pinSIG,HIGH);
  _EN = 0;
  _pinSIG = pinSIG;
  _pinCH = pinCH;
}

void DM02A::SendLevel(uint8_t _level, uint8_t _channel)
{
  if(_EN){
    digitalWrite(_pinEN,HIGH);
  }
  if(_channel >= 1){
    digitalWrite(_pinCH,HIGH);
  }else{
    digitalWrite(_pinCH,LOW);
  }
  pinMode(_pinSIG, OUTPUT);
  if(_level > 0){
    if(_level > 1023){
      _level = 1023;
    }
    digitalWrite(_pinSIG,LOW);
    _cont = 0;
    while(_cont < _level){
      delayMicroseconds(500);
      _cont = _cont + 1;
    }
        digitalWrite(_pinSIG,HIGH);
  }else{
    digitalWrite(_pinSIG,LOW);
        delayMicroseconds(250); //Enviando a metade do tempo máximo
        digitalWrite(_pinSIG,HIGH);
  }
  delayMicroseconds(100);
  if(_EN){
    digitalWrite(_pinEN,LOW);
  }
  delay(60);
}

uint8_t DM02A::Feedback(uint8_t _channel){
  if(_EN){
    digitalWrite(_pinEN,HIGH);
  }
  delayMicroseconds(100);
  if(_channel >= 1){
    digitalWrite(_pinCH,HIGH);
  }else{
    digitalWrite(_pinCH,LOW);
  }
  
  pinMode(_pinSIG, OUTPUT);
  digitalWrite(_pinSIG,LOW);
    delay(45);
    digitalWrite(_pinSIG,HIGH);
    delayMicroseconds(100);
          
    pinMode(_pinSIG,INPUT);
    delayMicroseconds(100);
          
    _pulse = pulseIn(_pinSIG, LOW, 36000);
        
    pinMode(_pinSIG,OUTPUT);
    digitalWrite(_pinSIG,HIGH);
    
  if(_EN){
    digitalWrite(_pinEN,LOW);
  }
  delay(60);
  _pulse = _pulse / 500;
  if(_pulse > 1023){
    _pulse = 1023;
  }
  return _pulse;
}
