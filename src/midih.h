#ifndef MIDIH_H
#define MIDIH_H

#include <MIDI.h>
//midi pitch
extern byte currentMidiNote;
extern float pitchBendSemitones;
extern int pitchBendValue;
// Correct external declaration for Teensy MIDI library
extern midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> MIDI;


void setupMIDI();
void handleNoteOn(byte channel, byte pitch, byte velocity) ;
void handleNoteOff(byte channel, byte pitch, byte velocity) ;\
float getPitchBendOffset();
void handleControlChange(byte channel, byte control, byte value);
void updateFrequency();

#endif
