#ifndef UI_H
#define UI_H
#pragma once
#include <Bounce.h>
#include <Arduino.h>
#include "global.h"

// Struct to hold knob state
struct Knob {
  uint8_t pin;
  float KnobValue;
  float lastKnobValue;
  bool active;
};

extern Bounce button0;
extern Bounce button1;
extern Bounce button2;

// Struct to store all mode-specific parameters to ensure values are preserved

  // Volume mode parameters
struct SynthParameters {
  struct {
    float mainVol;
    float vcoAgain;
    float vcoBgain;
    float vcoCgain;
    float SubVol;
  } volume;

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

  struct {
    float envAtk;
    float envDec;
    float envRel;
    float envSus;
  } env;

  struct {
    int shapeA_btn;
    int shapeB_btn;
    int shapeC_btn;
  } waveform;

  struct {
    float lfoAatk;
    float lfoAdec;
    float lfoArel;
    float lfoAsus;
    float lfoAfreq;
    float lfoAamp;
    bool lfoAEdit;
  } lfo;

  struct {
    float dlyMix;
    float dlyTime;
  } dly;

  struct {
    float size;
    float damping;
    float reverbMix;
  } reverb;

  struct {
    float param1;
  } sampling;

  struct {
    float freeze_time;
    float pitch_shift;
    float ratio;
    bool freeze_start;
    bool pitch_shift_on;
  } granular;
};
extern SynthParameters params;
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
void GranularParamUpdate();
void GranularUpdate();
enum ControlMode {
  VOLUME_MODE,
  FILTER_MODE,
  WAVEFORM_MODE,
  LFO_MODE,
  ENVELOPE_MODE,
  EFFECTS_MODE,
  SAMPLING_MODE,
  GRAN_MODE
};

extern ControlMode currentMode;

#endif

