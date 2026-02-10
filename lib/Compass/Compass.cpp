#include "Compass.h"

Compass compass;

void CompassSetup() {
    compass.attach(COMPASS_IN); // Attach the compass to the defined pin
}

void CompassLoop() {
    int compassValue = compass.read(); // Read the compass value
    Serial.print("Heading: ");
    Serial.println(compassValue);
}