#include "midih.h"
#include "audcon.h"    // renamed from core.h
#include "global.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

void handleNoteOn(byte channel, byte pitch, byte velocity) {
  float freq = 440.0 * pow(2.0, (pitch - 69) / 12.0);
  vcoA1.frequency(freq);
  vcoB1.frequency(freq);
  vcoC1.frequency(freq);
  sub1.frequency(freq);
  lfoAenv1.noteOn();
  env1.noteOn();

  Serial.print("MIDI Note On: ");
  Serial.print(pitch);
  Serial.print(" Velocity: ");
  Serial.println(velocity);
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
  lfoAenv1.noteOff();
  env1.noteOff();

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
