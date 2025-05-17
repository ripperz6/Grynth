#ifndef UI_H
#define UI_H

#include <Arduino.h>

// Struct to hold knob state
struct Knob {
  uint8_t pin;
  float KnobValue;
  float lastKnobValue;
  bool active;
};

// Struct to store all mode-specific parameters to ensure values are preserved
typedef struct {
  // Volume mode parameters
  struct {
    float mainVol;
    float vcoAgain;
    float vcoBgain;
    float vcoCgain;
    float SubVol;
  } volume;

  // Filter mode parameters
  struct {
    float cutoff;
    float reso;
    float octave;
    float filtAtt;
    float filtDec;
    float filtRel;
    float filtSus;
    int filterMode;
    bool filterEdit;
  } filter;

  // Waveform mode parameters
  struct {
    int shapeA_btn;
    int shapeB_btn;
    int shapeC_btn;
    int shapeSub_btn;
    float volSub_pot;
  } waveform;

  // LFO mode parameters
  struct {
    float lfoAamp;
    float lfoAfreq;
    float lfoAatk;
    float lfoAdec;
    float lfoArel;
    float lfoAsus;
    int lfoAshape;
    bool lfoAEdit;

    float lfoBamp;
    float lfoBfreq;
  } lfo;

  // Effects mode parameters
  struct {
    float size;
    float damping;
    float reverbMix;
  } reverb;

   // Effects mode parameters
  struct {
    float dlyTime;
    float dlyMix;
  } dly;

  // Sampling mode parameters
  struct {
    float envAtk;
    float envDec;
    float envRel;
    float envSus;
  } env;

    struct {
    float param1;
    float param2;
    float param3;
    float param4;
    float param5;
  } sampling;
} SynthParameters;

// Declare the knobs
extern Knob knobs[5];
// Setup knob pins
void setupUI();

// Read all knobs and update values
void updateKnobs();

void updateMainVolume();
void updateVolumeParams();
void updateFilterParams();
void updateFilterMode();
void updateWaveformParams();
void updateFilterParam();
void updateLFOParams();
void updateLFO();
void WaveformUpdate();
void updateEnvelopeParams();
void EnvelopeUpdate();
void updateButtons();
void updateEffectsParams();
#endif