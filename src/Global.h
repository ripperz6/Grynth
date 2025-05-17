#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include <Bounce.h>
#include <Audio.h>

// Envelope flags
extern bool env1on;

// VCO volumes
extern float vcoAgain;
extern float vcoBgain;
extern float vcoCgain;
extern float SubVol;
extern float crossMod;
extern float vcoVol;
extern float mainVol;

// VCO shape
extern int shapeA, shapeB, shapeC, shapeSub;
extern float volA_pot;
extern int freqA;

// Filter
extern int cutoff, filtSus;
extern float reso;
extern float octave;
extern float filtAtt, filtDec, filtRel;
extern float filtAmount;
extern int filterMode, filterEdit;

// Envelope
extern float envSus,envAtt, envDec, envRel;

// LFO A
extern float lfoAamplitude, lfoAfrequency;
extern int lfoAdelay, lfoAattack, lfoAdecay, lfoArelease, lfoAEdit;
extern float lfoAsustain;
extern int lfoAshape, lfoAdestination;
extern float ampMod;

// LFO B
extern float lfoBamplitude, lfoBfrequency;

// Delay
extern float outGain, dlyAmount;
extern float dlyTimeL, dlyTimeR;

// Reverb
extern float revMix, revSize;

// Control threshold
extern float tresh, tresh2;
extern int timer;
extern unsigned long prevTimer;

// UI control variables
extern int shapeA_btn, oldShapeA_btn;
extern int shapeB_btn, oldShapeB_btn;
extern int shapeC_btn, oldShapeC_btn;
extern int shapeSub_btn, oldShapeSub_btn;
extern int crossModulation_pot, oldCrossModulation_pot;
extern float volA_pot, oldVolA_pot;
extern int volB_pot, oldVolB_pot;
extern int volC_pot, oldVolC_pot;
extern int volSub_pot, oldVolSub_pot;
extern int attack_pot, oldAtttack_pot;
extern int decay_pot, oldDecay_pot;
extern float sustain_pot, oldSustain_pot;
extern int lfoAamplitude_pot, oldLfoAamplitude_pot;
extern int lfoFrequency_pot, oldLfoFrequency_pot;
extern int lfoAttack_ot, oldLfoAttack_pot;
extern int lfoDecay_pot, oldLfoDecay_pot;
extern int lfoSustain_pot, oldLfoSustain_pot;
extern int lfoShape_btn, oldLfoShape_btn;
extern int lfoDestination_btn, oldLfoDestination_btn;
extern int lfoBAmplitude_pot, oldLfoBAmplitude_pot;
extern int lfoBFrequency_pot, oldLfoBFrequency_pot;
extern int dlyAmount_pot, oldDlyAmount_pot;
extern int dlyTime_pot, oldDlyTime_pot;
extern int revMix_pot, oldRevMix_pot;
extern int revSize_pot, oldRevSize_pot;

struct NoteButton {
  int pin;
  const char* name;
  float frequency;
  Bounce button;
};

extern NoteButton noteButtons[6];


#endif
