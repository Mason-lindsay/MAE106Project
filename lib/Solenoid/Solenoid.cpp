#include "Solenoid.h"

void Solenoid::attach(int pin) {
    pin_ = pin;
    pinMode(pin_, OUTPUT);
    off();  // start OFF for safety
}

void Solenoid::on() {
    digitalWrite(pin_, HIGH);
    state_ = true;
}

void Solenoid::off() {
    digitalWrite(pin_, LOW);
    state_ = false;
}

void Solenoid::toggle() {
    if (state_ && (millis() - previousMillis >= 700)) { // If currently on and 700 ms have passed
        off();
        previousMillis = millis(); // Reset the timer after toggling
    } else if (!state_ && (millis() - previousMillis >= 900)) { // If currently off and 900 ms have passed
        on();
        previousMillis = millis(); // Reset the timer after toggling
    }
}

bool Solenoid::isOn() {
    return state_;
}
