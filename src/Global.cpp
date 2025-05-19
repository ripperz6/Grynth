// globals.cpp
#include "Global.h"
#include "audcon.h"

bool env1on = false;

float vcoAgain = 0.4;
float vcoBgain = 0.4;
float vcoCgain = 0.4;
float SubVol = 0.4;
float crossMod;
float vcoVol = 0.07;

float mainVol;
float mainVolPot;
float oldmainVolPot;

int shapeA;
int shapeB;
int shapeC = 1;

int cutoff = 2000;
float reso = 1;
float octave = 1;
int filterEdit;
float filtAtt;
float filtDec;
float filtRel;
int filtSus;
float filtAmount;
int filterMode;

float envAtt;
float envDec;
float envRel;
float envSus;

float lfoAamplitude;
float lfoAfrequency;
int lfoAdelay;
int lfoAattack;
int lfoAdecay;
int lfoArelease;
int lfoAEdit;
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
float volA_pot;
float oldVolA_pot;
int freqA; 

int shapeB_btn;
int oldShapeB_btn;
int volB_pot;
int oldVolB_pot;

int shapeC_btn;
int oldShapeC_btn;
int volC_pot;
int oldVolC_pot;

int shapeSub_btn;
int oldShapeSub_btn;
int volSub_pot;
int oldVolSub_pot;

int crossModulation_pot;
int oldCrossModulation_pot;


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

//Granular 
int16_t granularMemory[GRANULAR_MEMORY_SIZE];



NoteButton noteButtons[] = {
  {27, "C", 261.63, Bounce(27, 15)},
  {28, "D", 293.66, Bounce(28, 15)},
  {29, "E", 329.63, Bounce(29, 15)},
  {30,"F", 349.23, Bounce(30, 15)},
  {31, "G", 392.00, Bounce(31, 15)},
  {32, "A", 440.00, Bounce(32, 15)}
};

void triggerNoteOn(float freq) {
  vcoA1.frequency(freq);
  vcoB1.frequency(freq);
  vcoC1.frequency(freq);
  lfoAenv1.noteOn();
  env1.noteOn();

  granular1.begin(granularMemory, GRANULAR_MEMORY_SIZE);
  // Freeze a grain once
  int grain_size = random(10000, GRANULAR_MEMORY_SIZE);
  granular1.beginFreeze(grain_size);
  
  // Optional: Add pitch shift or speed
  float grain_speed = random(15, 200) / 100.0f;
  granular1.setSpeed(1.334839854);
  GranularMode1.gain(0, 0.5);  // granular on
}


void triggerNoteOff() {
  lfoAenv1.noteOff();
  env1.noteOff();
  granular1.stop();
}




