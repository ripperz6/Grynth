// main.cpp
#include <Arduino.h>
#include "audcon.h"
#include "global.h"
#include "midih.h"
#include <MIDI.h>
#include "ui.h"
#include "display.h"

void setup() {
  Serial.begin(9600);
  setupOLED();


  AudioMemory(400);
  setupMIDI();
  sgtl5000_1.enable();                                  //Audio Shield Ena
  sgtl5000_1.volume(0.8);                               //Audio Shield Vol

  vcoA1.begin(vcoVol, 150, WAVEFORM_SAWTOOTH);          //Wave A def
  vcoB1.begin(vcoVol, 150, WAVEFORM_SQUARE);            //Wave B def
  vcoC1.begin(vcoVol * 1.5, 150, WAVEFORM_ARBITRARY);   //Wave C def
  sub1.begin(vcoVol * 1.5, 150, WAVEFORM_TRIANGLE);     //Wave Sub def

  filter1.octaveControl(7);                             //Filter Control 7 Octave
  filterEnv1.sustain(0);         
  filterMode1.gain(0, 0);               //Low pass filter signal path
  filterMode1.gain(1, 1);               //Band pass filter signal path
  filterMode1.gain(2, 0);               //High pass filter 0 = off 1 = on signal path

  granular1.setSpeed(0);
  granular1.beginFreeze(0);
  granular1.beginPitchShift(5);

  GranularMode1.gain(0,1);                              //Granular Off
  GranularMode1.gain(0,0);                              //Granular On

  lfoA1.begin(0.5, 2, WAVEFORM_SINE);                   //LFO A def shape
  lfoB1.begin(0.5, 1, WAVEFORM_TRIANGLE);               //LFO B def gain freq shape

  env1.attack(10.5);
  env1.delay(0);
  env1.decay(35);
  env1.sustain(0.3);
  env1.release(300);

  mix1.gain(0,1);
  finalMix.gain(0,1);

  dlyFiltL.frequency(4000);
  dlyFiltR.frequency(3000);

  dlyMixL.gain(0, 1);                                   //Dry Voice Mix
  dlyMixL.gain(1, 0);                                   //Delay Feedback Mix
  dlyMixR.gain(0, 1);                                   
  dlyMixR.gain(1, 0);                                   

  for (int i = 1; i < 8; ++i) {                         //Disable Delay
    dlyL.disable(i);
    dlyR.disable(i);
  }

  reverb.roomsize(0.9);                                 //Reverb Size Def
  reverb.damping(0.8);                                  //Reveb Damp Def

  dlyL.delay(0, 500);                                   //Delay L Channel out 0, freq
  dlyR.delay(0, 333);                                   //Delay R Channel out 0, freq

  patchCord2.disconnect();                              //LFOA Pitch connect Wave A
  patchCord3.disconnect();                              //LFOA Pitch connect Wave B                           
  patchCord4.disconnect();                              //LFOA Pitch connect Wave C
  patchCord5.disconnect();                              //LFOA Pitch connect Wave Sub
  patchCord6.disconnect();                              //LFOA Amplitude
  patchCord7.disconnect();                              //LFOA Filter

  for (int i = 0; i < 6; ++i) {
    pinMode(27 + i, INPUT_PULLUP);
  }
}

void loop() {
  MIDI.read();
  updateKnobs();
  updateButtons();
  updateMainVolume();
  WaveformUpdate();
  updateFilterMode();
  updateFilterParam();
  updateVoiceMixGain();
  drawVolumeBar(mainVol);  // Assuming mainVol is 0.0–1.0

  
  lfoA1.begin(1, 1, WAVEFORM_SINE);     //LFOA Amplitude, Freq, Shape
  lfoB1.begin(0.8, 2, WAVEFORM_SINE);   //LFOB Amplitude, Freq, Shape


  modMix1.gain(0, 1);                   //vcoB mod Mix
  modMix1.gain(1, 1);                   //LFO mod Mix Wave B

  dc1.amplitude(0.1);                   //DC control signal to filter



  filterMix1.gain(0, 0);                //LFO merge with Filter Envelope
  filterMix1.gain(1, 0);              //Filter Envelope Control



  env1.attack(10.5);
  env1.delay(0);
  env1.decay(35);
  env1.sustain(0.2);
  env1.release(200);


  mix1.gain(0, 1);                      //Allow note 0 to pass to Final Mix

  reverb.roomsize(0.3);                 //Reverb Size
  reverb.damping(0);                  //Reverb Damp

  dlyMixL.gain(0, 1);                   //Dry Sound of Delay L
  dlyMixL.gain(1, 1);                   //Delay Feedback

  dlyMixR.gain(0, 1);                   //Dry Sound of Delay R
  dlyMixR.gain(1, 1);                   //Delay Feedback

  fxL.gain(0, 1);                       //Dry Sound L
  fxL.gain(1, 0);                       //Reverb Mix L
  fxL.gain(2, 0);                       //Reveb Mix L

  fxR.gain(0, 1);                       //Dry Sound R
  fxR.gain(1, 0);                       //Reverb Mix R
  fxR.gain(2, 0);                       //Reverb Mix R

for (int i = 0; i < 6; ++i) {           //Note Play
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