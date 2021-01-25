#include "DM02A.h"
#include "ports.h"

class Dimmer {
  public:
    Dimmer();
    void Setup();
    void SetMax();
    void SetMin();
    void TurnOff();
    void LevelUp();
    void LevelDown();
    void SetLevel(char level);
  private:
    const char _minValue = 1;
    const char _maxValue = 8;
    boolean _channel;
    char _level;
    DM02A _dimmer = DM02A(P_SIG, P_CH, P_EN);
    void updateLevels();
};
