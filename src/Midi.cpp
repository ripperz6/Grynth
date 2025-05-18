#include "midih.h"
#include "audcon.h"    // renamed from core.h
#include "global.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

void handleNoteOn(byte channel, byte pitch, byte velocity) {
  if (velocity == 0) {
    handleNoteOff(channel, pitch, velocity);
    return;
  }

  float freq = 440.0f * pow(2.0f, (pitch - 69) / 12.0f);
  triggerNoteOn(freq);

  Serial.print("MIDI Note On: ");
  Serial.print(pitch);
  Serial.print(" Velocity: ");
  Serial.println(velocity);
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
  triggerNoteOff();

  Serial.print("MIDI Note Off: ");
  Serial.println(pitch);
}

void handleControlChange(byte channel, byte control, byte value) {
  if (control == 1) {
    float modAmount = value / 127.0f;
    lfoA1.amplitude(modAmount);
    Serial.print("MIDI CC1 Mod Amount: ");
    Serial.println(modAmount);
  }
}

void setupMIDI() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleControlChange(handleControlChange);
}
