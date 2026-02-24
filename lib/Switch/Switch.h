#ifndef Switch_H
#define Switch_H

#include <Arduino.h>

#define SWITCH_IN 5 // Replace with the actual pin number

class Switch {
public:
    void attach(int pin);
    bool read();
    double distanceTraveled();
    bool switchState();
    
private:
    int pin_;
    bool lastStableState_ = false;
    bool lastReading_ = false;
    unsigned long lastDebounceTime_ = 0;
    const unsigned long debounceDelay_ = 20; // 20 ms
    double distance_ = 0; //(m)
    double wheelDiameter_ = 0.07; // (m)
};

#endif