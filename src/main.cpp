// main.cpp
#include <Arduino.h>
#include "synth.h"
#include "global.h"
#include "midih.h"
#include <MIDI.h>


void setup() {
  Serial.begin(9600);
  AudioMemory(400);
  setupMIDI();
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  vcoA1.begin(vcoVol, 150, WAVEFORM_SAWTOOTH);
  vcoB1.begin(vcoVol, 150, WAVEFORM_SQUARE);
  vcoC1.begin(vcoVol * 1.5, 150, WAVEFORM_ARBITRARY);
  sub1.begin(vcoVol * 1.5, 150, WAVEFORM_TRIANGLE);

  filter1.octaveControl(7);
  filterEnv1.sustain(0);

  lfoA1.begin(WAVEFORM_SINE);
  lfoB1.begin(0.5, 1, WAVEFORM_TRIANGLE);

  dlyFiltL.frequency(4000);
  dlyFiltR.frequency(3000);

  dlyMixL.gain(0, 0);
  dlyMixL.gain(1, 0);
  dlyMixR.gain(0, 0);
  dlyMixR.gain(1, 0);

  for (int i = 1; i < 8; ++i) {
    dlyL.disable(i);
    dlyR.disable(i);
  }

  reverb.roomsize(0.9);
  reverb.damping(0.8);

  dlyL.delay(0, 500);
  dlyR.delay(0, 333);

  patchCord2.disconnect();
  patchCord3.disconnect();
  patchCord4.disconnect();
  patchCord5.disconnect();
  patchCord6.disconnect();
  patchCord7.disconnect();

  for (int i = 0; i < 6; ++i) {
    pinMode(33 + i, INPUT_PULLUP);
  }
}

void loop() {
  MIDI.read();
  patchCord2.connect();
  patchCord3.connect();
  patchCord4.connect();
  patchCord5.connect();

  patchCord6.disconnect();
  patchCord7.disconnect();

  lfoA1.amplitude(1);
  lfoA1.frequency(1);
  lfoB1.begin(0.8, 2, WAVEFORM_SINE);

  vcoA1.begin(WAVEFORM_SINE);
  vcoB1.begin(WAVEFORM_SAWTOOTH);
  vcoC1.begin(WAVEFORM_SINE);
  sub1.begin(WAVEFORM_SINE);

  modMix1.gain(0, 1);
  modMix1.gain(1, 0);

  dc1.amplitude(0.1);

  voiceMix1.gain(0, 1);
  voiceMix1.gain(1, 0);
  voiceMix1.gain(2, 0);
  voiceMix1.gain(3, 0);

  filterEnv1.attack(10.5);
  filterEnv1.decay(35);
  filterEnv1.delay(0);
  filterEnv1.sustain(0.6);
  filterEnv1.release(300);

  filterMix1.gain(0, 0);
  filterMix1.gain(1, 0.5);

  filter1.frequency(2000);
  filter1.resonance(1);

  filterMode1.gain(0, 0);
  filterMode1.gain(1, 1);
  filterMode1.gain(2, 0);

  mix1.gain(0, 1);
  finalMix.gain(0, 1);

  reverb.roomsize(0.3);
  reverb.damping(0.2);

  dlyMixL.gain(0, 1);
  dlyMixL.gain(1, 1);

  dlyMixR.gain(0, 1);
  dlyMixR.gain(1, 1);

  fxL.gain(0, 1);
  fxL.gain(1, 0.8);
  fxL.gain(2, 0.7);

  fxR.gain(0, 1);
  fxR.gain(1, 0.8);
  fxR.gain(2, 0.7);

for (int i = 0; i < 6; ++i) {
  noteButtons[i].button.update();
  if (noteButtons[i].button.fallingEdge()) {
    float freq = noteButtons[i].frequency;
    vcoA1.frequency(freq);
    vcoB1.frequency(freq);
    vcoC1.frequency(freq);
    sub1.frequency(freq);
    lfoAenv1.noteOn();
    env1.noteOn();

    Serial.print("Note: ");
    Serial.println(noteButtons[i].name);
  }

  if (noteButtons[i].button.risingEdge()) {
    lfoAenv1.noteOff();
    env1.noteOff();
  }
}

}