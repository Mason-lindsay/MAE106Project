#ifndef Solenoid_H
#define Solenoid_H

#include <Arduino.h>

#define SOL_IN 8 // Replace with the actual pin number

class Solenoid {
public:
    void attach(int pin);
    void write(int value);
    
private:
    int pin_;
};

void SolenoidSetup();
void SolenoidLoop();
#endif