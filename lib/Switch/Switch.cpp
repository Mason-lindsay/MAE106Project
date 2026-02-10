#include "Switch.h"
#include <Arduino.h>

Switch switchDevice;

void SwitchSetup() {
    switchDevice.attach(SWITCH_IN); // Attach the switch to the defined pin
}

void SwitchLoop() {
    bool switchState = switchDevice.read(); // Read the switch state
    Serial.print("Switch State: ");
    Serial.println(switchState ? "ON" : "OFF");
}