#include "midih.h"
#include "audcon.h"    // renamed from core.h
#include "Global.h"
#include <deque>
#include "ui.h"
std::vector<byte> heldNotes;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
byte currentMidiNote = 0; // currently held note
int pitchBendValue = 8192; // center by default
float pitchBendSemitones = 2.0f; // ±2 semitones

void handleNoteOn(byte channel, byte pitch, byte velocity) {
    // Treat a Note On with velocity 0 as a Note Off
    if (velocity == 0) {
        handleNoteOff(channel, pitch, velocity);
        return;
    }

    // Add to heldNotes if this pitch isn't already held
    if (std::find(heldNotes.begin(), heldNotes.end(), pitch) == heldNotes.end()) {
        heldNotes.push_back(pitch);
    }

    // Always update the “currentMidiNote” to be the most recently held note
    currentMidiNote = heldNotes.back();
    updateFrequency();

    // If we're in granular mode, trigger the granular freeze
    if (currentMode == GRAN_MODE) {
        // Trigger the envelope for the granular “voice”
        env1.noteOn();

        // Once the sample is loaded, start the freeze
        if (granularSampleLoaded) {
            granular1.beginFreeze(FreezeT);  // e.g., 150.0 ms
        }
    }
    else {
        // Normal synth behavior: trigger both envelopes/LFOs
        env1.noteOn();
        lfoAenv1.noteOn();
    }

    // Debugging output (prints the MIDI note and velocity)
    Serial.print("MIDI Note On: ");
    Serial.print(currentMidiNote);
    Serial.print("  Velocity: ");
    Serial.println(velocity);
}




void handleNoteOff(byte channel, byte pitch, byte velocity) {
  // Remove note
  heldNotes.erase(std::remove(heldNotes.begin(), heldNotes.end(), pitch), heldNotes.end());

  if (!heldNotes.empty()) {
    currentMidiNote = heldNotes.back();
    updateFrequency(); // Retune to the remaining note
    // Optional: skip noteOn if you want legato behavior
  } else {
    env1.noteOff();
    lfoAenv1.noteOff();
    Serial.print("All notes released\n");
  }

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

void handlePitchBend(byte channel, int bend) {
  pitchBendValue = bend;  // update global bend value
  updateFrequency();      // call to a helper function to set pitch with bend
}

void updateFrequency() {
  float pitchWithBend = currentMidiNote + getPitchBendOffset();
   float freq = 440.0f * pow(2.0f, (pitchWithBend - 69.0f) / 12.0f);
  vcoA1.frequency(freq);
  vcoB1.frequency(freq);
  vcoC1.frequency(freq);
}


float getPitchBendOffset() {
  return ((pitchBendValue - 8192) / 8192.0f) * pitchBendSemitones;
}


void setupMIDI() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleControlChange(handleControlChange);
  MIDI.setHandlePitchBend(handlePitchBend);
  MIDI.turnThruOff();
}
