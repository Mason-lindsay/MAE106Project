#include "Solonoid.h"
#include <Arduino.h>

Solonoid solonoid;

void SolonoidSetup() {
    solonoid.attach(SOL_IN); // Attach the solenoid to the defined pin
    solonoid.write(0); // Set initial position to 0 (off)
}

void SolonoidLoop() {
    // Example loop to activate the solenoid for 1 second and then deactivate it
    solonoid.write(1); // Activate the solenoid
    delay(900); // Keep it activated for .9 seconds
    solonoid.write(0); // Deactivate the solenoid
    delay(700); // Wait for .7 seconds before the next activation
}