#ifndef Switch_H
#define Switch_H

#include <Arduino.h>

#define SWITCH_IN 7 // Replace with the actual pin number

class Switch {
public:
    void attach(int pin);
    bool read();
private:
    int pin_;
};

void SwitchSetup();
void SwitchLoop();
#endif