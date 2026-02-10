#ifndef Compass_H
#define Compass_H

#include <Arduino.h>

#define COMPASS_IN A0 // Replace with the actual pin number

class Compass {
public:
    void attach(int pin);
    int read();
private:
    int pin_;
};

void CompassSetup();
void CompassLoop();
#endif