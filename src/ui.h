#ifndef UI_H
#define UI_H

#include <Arduino.h>

// Struct to hold knob state
struct Knob {
  uint8_t pin;
  float KnobValue;
  float lastKnobValue;
};

// Declare the knobs
extern Knob knobs[5];
// Setup knob pins
void setupUI();

// Read all knobs and update values
void updateKnobs();

void updateMainVolume();

void updateVoiceMixGain();
#endif