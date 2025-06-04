#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include <Bounce.h>
#include <Audio.h>

//────────────────────────────────────────────────────────────────────────────
// 1) Granular memory size
//    A compile-time constant for buffer sizing.
#define GRANULAR_MEMORY_SIZE 32768

// 2) Declare the buffer that the granular engine will use.
extern int16_t granularMemory[GRANULAR_MEMORY_SIZE];


//────────────────────────────────────────────────────────────────────────────
// Synth / Audio flags and parameters

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
extern int   shapeA;
extern int   shapeB;
extern int   shapeC;
extern int   shapeSub;
extern float volA_pot;
extern int   freqA;

// Filter
extern int   cutoff;
extern int   filtSus;
extern float reso;
extern float octave;
extern float filtAtt;
extern float filtDec;
extern float filtRel;
extern float filtAmount;
extern int   filterMode;
extern int   filterEdit;

// Envelope
extern float envSus;
extern float envAtt;
extern float envDec;
extern float envRel;

// LFO A
extern float lfoAamplitude;
extern float lfoAfrequency;
extern int   lfoAdelay;
extern int   lfoAattack;
extern int   lfoAdecay;
extern int   lfoArelease;
extern int   lfoAEdit;
extern float lfoAsustain;
extern int   lfoAshape;
extern int   lfoAdestination;
extern float ampMod;

// LFO B
extern float lfoBamplitude;
extern float lfoBfrequency;

// Delay
extern float outGain;
extern float dlyAmount;
extern float dlyTimeL;
extern float dlyTimeR;

// Reverb
extern float revMix;
extern float revSize;

// Control threshold (for button debouncing, etc.)
extern float tresh;
extern float tresh2;
extern int   timer;
extern unsigned long prevTimer;

//────────────────────────────────────────────────────────────────────────────
// UI control variables (button pins, potentiometer readings, old values)

extern int shapeA_btn;
extern int oldShapeA_btn;

extern int shapeB_btn;
extern int oldShapeB_btn;

extern int shapeC_btn;
extern int oldShapeC_btn;

extern int shapeSub_btn;
extern int oldShapeSub_btn;

extern int crossModulation_pot;
extern int oldCrossModulation_pot;

extern int volB_pot;
extern int oldVolB_pot;

extern int volC_pot;
extern int oldVolC_pot;

extern int volSub_pot;
extern int oldVolSub_pot;

// “volA_pot” is declared above under VCO shape; here we only declare its old value:
extern float oldVolA_pot;

extern int attack_pot;
extern int oldAttack_pot;

extern int decay_pot;
extern int oldDecay_pot;

extern float sustain_pot;
extern float oldSustain_pot;

extern int lfoAamplitude_pot;
extern int oldLfoAamplitude_pot;

extern int lfoFrequency_pot;
extern int oldLfoFrequency_pot;

extern int lfoAttack_pot;
extern int oldLfoAttack_pot;

extern int lfoDecay_pot;
extern int oldLfoDecay_pot;

extern int lfoSustain_pot;
extern int oldLfoSustain_pot;

extern int lfoShape_btn;
extern int oldLfoShape_btn;

extern int lfoDestination_btn;
extern int oldLfoDestination_btn;

extern int lfoBAmplitude_pot;
extern int oldLfoBAmplitude_pot;

extern int lfoBFrequency_pot;
extern int oldLfoBFrequency_pot;

extern int dlyAmount_pot;
extern int oldDlyAmount_pot;

extern int dlyTime_pot;
extern int oldDlyTime_pot;

extern int revMix_pot;
extern int oldRevMix_pot;

extern int revSize_pot;
extern int oldRevSize_pot;

//────────────────────────────────────────────────────────────────────────────
// Granular playback parameters

extern float FreezeT;
extern float PitchShift;
extern float Ratio;

// Sample-bank buffer (for loading an external sample into memory)
extern int16_t sampleBank[GRANULAR_MEMORY_SIZE];

// Linkable constant (in case you need to pass buffer size by reference)
extern const int kGranularMemorySize;

// Flag that indicates whether `sampleBank` has been loaded
extern bool granularSampleLoaded;

//────────────────────────────────────────────────────────────────────────────
// NoteButton struct definition

struct NoteButton {
    int pin;
    const char* name;
    float frequency;
    Bounce button;
};

// Declare an array of 6 NoteButtons (definition in Global.cpp)
extern NoteButton noteButtons[6];

// Function prototypes for note on/off
void triggerNoteOn(float freq);
void triggerNoteOff();

#endif // GLOBAL_H
