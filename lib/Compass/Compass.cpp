#include "Compass.h"

//global instance
Compass compass;

//Class Methods 
void Compass::attach(int pin) {
    pin_ = pin;
    pinMode(pin_, INPUT);
}

int Compass::read() {
    // Read the analog value from the compass pin
    int value = analogRead(pin_);
    return value;
}

// Helper Functions
void CompassSetup() {
    compass.attach(COMPASS_IN); 
}

void CompassLoop() {
    int compassValue = compass.read(); 
    Serial.print("Heading: ");
    Serial.println(compassValue);
}