#include "Switch.h"
#include <Arduino.h>

//Class Methods
void Switch::attach(int pin) {
    pin_ = pin;
    pinMode(pin_, INPUT);
}

/// @brief reads current state of the switch (ON/OFF)
/// @return true if the switch is ON, false if the switch is OFF
bool Switch::read() {
    // Read the digital value from the switch pin
    int value = digitalRead(pin_);
    return value == HIGH; // Return true if the switch is ON (HIGH), false otherwise
}


bool Switch::switchState() {
    bool reading = read();

    // If reading changed, reset debounce timer
    if (reading != lastReading_) {
        lastDebounceTime_ = millis();
    }

    // If stable longer than debounce delay
    if ((millis() - lastDebounceTime_) > debounceDelay_) {

        if (reading != lastStableState_) {
            lastStableState_ = reading;
            lastReading_ = reading;
            return true;  // Valid state change
        }
    }

    lastReading_ = reading;
    return false;
}


/// @brief Calculates the distance traveled based on when the switch is ON or OFF.
/// @return Distance traveled in meters
double Switch::distanceTraveled(){
    if (switchState()) {
        distance_ += (wheelDiameter_ * 3.14159) / 2; // Assuming the switch is triggered every half rotation of the wheel
    }
    return distance_;
}