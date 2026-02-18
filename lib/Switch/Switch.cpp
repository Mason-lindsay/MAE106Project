#include "Switch.h"
#include <Arduino.h>

//global instance
Switch switchDevice;

// variables that keep track of the time the switch has been ON
int previousMillis = 0;
int currentMillis = 0;
double distance = 0;
double wheelDiameter = 0.2; // Replace with actual wheel diameter (m)

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


/// @brief  Calculates the duration the switch has been continuously ON  
/// @return Time ON in milliseconds
int Switch::timeOn() {
    bool isCurrentlyOn = switchDevice.read();

    if (isCurrentlyOn) {
        if (wasOff_) {
            startTime_ = millis();
            wasOff_ = false;
        }
        return (int)(millis() - startTime_);
    } else {
        // Switch is OFF, reset state
        wasOff_ = true;
        startTime_ = 0;
        return 0;
    }
}


/// @brief Calculates the time the switch has been OFF
/// @return Time OFF in milliseconds
int Switch::timeOff() {
    bool isCurrentlyOff = !switchDevice.read();

    if (isCurrentlyOff) {
        if(!wasOff_) {
            endTime_ = millis();
            wasOff_ = true;
        }
        return (int)(millis() - endTime_);
    } else {
        // Switch is ON, reset state
        wasOff_ = false;
        endTime_ = 0;
        return 0;
    }
}


/// @brief Calculates the distance traveled based on the time the switch is ON
/// @return Distance traveled in meters
double Switch::distanceTraveled(){
    bool isCurrentlyOn = switchDevice.read();

    if(isCurrentlyOn) {
        distance += (timeOn() / 1000.0) * (wheelDiameter * 3.14159); // distance = speed * time, where speed is the circumference of the wheel
    }
    else {
        distance += (timeOff() / 1000.0) * (wheelDiameter * 3.14159); // distance = speed * time, where speed is the circumference of the wheel
    }
    return distance;
}


//Helper Functions
void SwitchSetup() {
    switchDevice.attach(SWITCH_IN); // Attach the switch to the defined pin
}

void SwitchLoop() {
    bool switchState = switchDevice.read(); // Read the switch state
    Serial.print("Switch State: ");
    Serial.println(switchState ? "ON" : "OFF");
}