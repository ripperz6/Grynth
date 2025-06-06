// globals.cpp
#include "global.h"

bool env1on = false;

float vcoAVol = 0.4;
float vcoBVol = 0.4;
float vcoCVol = 0.4;
float SubVol = 0.4;
float crossMod;
float vcoVol = 0.07;
float mainVol;

int shapeA;
int shapeB;
int shapeC = 1;

int cutoff = 2000;
float reso = 1;
int filtAtt;
int filtDec;
float filtAmount;
int filterMode;

int envAtt;
int envDec;
int envRel;
float envSus;

float lfoAamplitude;
float lfoAfrequency;
int lfoAdelay;
int lfoAattack;
int lfoAdecay;
int lfoArelease;
float lfoAsustain;
int lfoAshape;
int lfoAdestination;
float ampMod;

float lfoBamplitude;
float lfoBfrequency;

float outGain = 0.8;
float dlyAmount;
float dlyTimeL;
float dlyTimeR;

float revMix;
float revSize;

float tresh = 10;
float tresh2 = 20;
int timer = 6;
unsigned long prevTimer;

int shapeA_btn;
int oldShapeA_btn;
int shapeB_btn;
int oldShapeB_btn;
int crossModulation_pot;
int oldCrossModulation_pot;
int volA_pot;
int oldVolA_pot;
int volB_pot;
int oldVolB_pot;
int volC_pot;
int oldVolC_pot;
int volSub_pot;
int oldVolSub_pot;
int attack_pot;
int oldAtttack_pot;
int decay_pot;
int oldDecay_pot;
float sustain_pot;
float oldSustain_pot;
int lfoAamplitude_pot;
int oldLfoAamplitude_pot;
int lfoFrequency_pot;
int oldLfoFrequency_pot;
int lfoAttack_ot;
int oldLfoAttack_pot;
int lfoDecay_pot;
int oldLfoDecay_pot;
int lfoSustain_pot;
int oldLfoSustain_pot;
int lfoShape_btn;
int oldLfoShape_btn;
int lfoDestination_btn;
int oldLfoDestination_btn;
int lfoBAmplitude_pot;
int oldLfoBAmplitude_pot;
int lfoBFrequency_pot;
int oldLfoBFrequency_pot;
int dlyAmount_pot;
int oldDlyAmount_pot;
int dlyTime_pot;
int oldDlyTime_pot;
int revMix_pot;
int oldRevMix_pot;
int revSize_pot;
int oldRevSize_pot;

NoteButton noteButtons[] = {
  {38, "C", 261.63, Bounce(38, 15)},
  {37, "D", 293.66, Bounce(37, 15)},
  {36, "E", 329.63, Bounce(36, 15)},
  {35, "F", 349.23, Bounce(35, 15)},
  {34, "G", 392.00, Bounce(34, 15)},
  {33, "A", 440.00, Bounce(33, 15)}
};
