#ifndef AUDCON_H
#define AUDCON_H

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include "global.h"

// Declare all Audio objects (copied exactly from your source)
extern AudioSynthWaveform lfoA1;
extern AudioEffectEnvelope lfoAenv1;
extern AudioSynthWaveform lfoB1;
extern AudioMixer4 modMix1;
extern AudioAnalyzeRMS lfoAread1;
extern AudioSynthWaveformModulated vcoC1;
extern AudioSynthWaveformModulated vcoB1;
extern AudioSynthWaveformModulated vcoA1;
extern AudioSynthWaveformDc dc1;
extern AudioSynthWaveformModulated sub1;
extern AudioEffectEnvelope filterEnv1;
extern AudioMixer4 voiceMix1;
extern AudioMixer4 filterMix1;
extern AudioFilterStateVariable filter1;
extern AudioMixer4 filterMode1;
extern AudioEffectEnvelope env1;
extern AudioMixer4 mix1;
extern AudioMixer4 finalMix;
extern AudioFilterStateVariable dlyFiltL;
extern AudioFilterStateVariable dlyFiltR;
extern AudioEffectDelay dlyR;
extern AudioEffectDelay dlyL;
extern AudioMixer4 dlyMixR;
extern AudioEffectFreeverb reverb;
extern AudioMixer4 dlyMixL;
extern AudioMixer4 fxL;
extern AudioMixer4 fxR;
extern AudioOutputI2S i2s1;
extern AudioControlSGTL5000 sgtl5000_1;

extern AudioEffectGranular granular1;
extern AudioMixer4 GranularMode1;

extern AudioConnection patchCord1;
extern AudioConnection patchCord2;
extern AudioConnection patchCord3;
extern AudioConnection patchCord4;
extern AudioConnection patchCord5;
extern AudioConnection patchCord6;
extern AudioConnection patchCord7;
extern AudioConnection patchCord8;
extern AudioConnection patchCord9;
extern AudioConnection patchCord10;
extern AudioConnection patchCord11;
extern AudioConnection patchCord12;
extern AudioConnection patchCord13;
extern AudioConnection patchCord14;
extern AudioConnection patchCord15;
extern AudioConnection patchCord16;
extern AudioConnection patchCord17;
extern AudioConnection patchCord18;
extern AudioConnection patchCord19;
extern AudioConnection patchCord20;
extern AudioConnection patchCord21;
extern AudioConnection patchCord22;
extern AudioConnection patchCord23;
extern AudioConnection patchCord24;
extern AudioConnection patchCord25;
extern AudioConnection patchCord26;
extern AudioConnection patchCord27;
extern AudioConnection patchCord28;
extern AudioConnection patchCord29;
extern AudioConnection patchCord30;
extern AudioConnection patchCord31;
extern AudioConnection patchCord32;
extern AudioConnection patchCord33;
extern AudioConnection patchCord34;
extern AudioConnection patchCord35;
extern AudioConnection patchCord36;
extern AudioConnection patchCord37;
extern AudioConnection patchCord38;
extern AudioConnection patchCord39;
extern AudioConnection patchCord40;
extern AudioConnection patchCord41;

extern AudioConnection patchCord42; //filtermode1 to gran
extern AudioConnection patchCord43; //gran to granmode
extern AudioConnection patchCord44; //granmode to env1
extern AudioConnection patchCord45; //granmode to env1
extern AudioConnection patchCordX;
#endif
