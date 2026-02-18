#ifndef Switch_H
#define Switch_H

#include <Arduino.h>

#define SWITCH_IN 7 // Replace with the actual pin number

class Switch {
public:
    void attach(int pin);
    bool read();
    double distanceTraveled();
    int timeOn();
    int timeOff();
private:
    int pin_;
    unsigned long startTime_;
    unsigned long endTime_;
    bool wasOff_ = true;
};

void SwitchSetup();
void SwitchLoop();
#endif