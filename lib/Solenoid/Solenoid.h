#ifndef SOLENOID_H
#define SOLENOID_H

#include <Arduino.h>

#define SOL_PIN 2   // Output pin controlling solenoid

class Solenoid {
public:
    void attach(int pin);
    void on();
    void off();
    void toggle();
    bool isOn();

private:
    int pin_;
    bool state_ = false;
};

void SolenoidSetup();
void SolenoidLoop();

#endif