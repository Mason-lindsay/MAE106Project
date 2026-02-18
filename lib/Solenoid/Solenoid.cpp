#include "Solenoid.h"
#include <Arduino.h>

Solenoid solenoid;

void SolenoidSetup() {
    solenoid.attach(SOL_IN); // Attach the solenoid to the defined pin
    solenoid.write(0); // Set initial position to 0 (off)
}

void SolenoidLoop() {
    // loop to activate the solenoid for .9 seconds and then deactivate it for .7 seconds, repeatedly
    solenoid.write(1); // Activate the solenoid
    delay(900); // Keep it activated for .9 seconds
    solenoid.write(0); // Deactivate the solenoid
    delay(700); // Wait for .7 seconds before the next activation
}