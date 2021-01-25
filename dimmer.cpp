#include <DM02A.h>
#include "dimmer.h"

void Dimmer::Setup()
{
  _dimmer.EnviaNivel(0,0);
  _dimmer.EnviaNivel(0,1);
}

void Dimmer::SetMax()
{
  _level = _maxValue;
  updateLevels();
}

void Dimmer::SetMin()
{
  _level = _minValue;
  updateLevels();
}

void Dimmer::TurnOff()
{
  _level = 0;
  updateLevels();
}

void Dimmer::LevelUp()
{
  _level = _level++;
  if (_level > _maxValue)
    _level = _maxValue;
  updateLevels();
}
void Dimmer::LevelDown()
{
  _level = _level--;
  if (_level < 0)
    _level = 0;
  updateLevels();
}
void Dimmer::SetLevel(char level)
{
  _level = level;
  if (_level < 0)
    _level = 0;
  if (_level > _maxValue)
    _level = _maxValue;
  updateLevels();
}

void Dimmer::updateLevels()
{
  if (_level == 0)
  {
   _dimmer.EnviaNivel(0,0);
   _dimmer.EnviaNivel(0,1);
  }
  else if (_level == 1)
  {
   _dimmer.EnviaNivel(30,0);
   _dimmer.EnviaNivel(0,1);
  }
  else if (_level == 2)
  {
   _dimmer.EnviaNivel(43,0);
   _dimmer.EnviaNivel(0,1);
  }
  else if (_level == 3)
  {
   _dimmer.EnviaNivel(57,0);
   _dimmer.EnviaNivel(0,1);
  }
  else if (_level == 4)
  {
   _dimmer.EnviaNivel(70,0);
   _dimmer.EnviaNivel(0,1);
  }
  else if (_level == 5)
  {
   _dimmer.EnviaNivel(70,0);
   _dimmer.EnviaNivel(30,1);
  }
  else if (_level == 6)
  {
   _dimmer.EnviaNivel(70,0);
   _dimmer.EnviaNivel(43,1);
  }
  else if (_level == 7)
  {
   _dimmer.EnviaNivel(70,0);
   _dimmer.EnviaNivel(57,1);
  }
  else if (_level == 8)
  {
   _dimmer.EnviaNivel(70,0);
   _dimmer.EnviaNivel(70,1);
  }
}
