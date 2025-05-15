#ifndef MIDIH_H
#define MIDIH_H

#include <MIDI.h>

// Correct external declaration for Teensy MIDI library
extern midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> MIDI;

void setupMIDI();

#endif
