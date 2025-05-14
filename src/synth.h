#ifndef SYNTH_H
#define SYNTH_H

#include <Audio.h>

// Define Audio objects
extern AudioSynthWaveform vcoA1, vcoB1, vcoC1, sub1;
extern AudioMixer4 modMix1, voiceMix1;
extern AudioEffectEnvelope env1, filterEnv1;
extern AudioFilterStateVariable filter1;
extern AudioEffectDelay dlyL, dlyR;
extern AudioEffectFreeverb reverb;

// Initialization function
void initSynth();

// Update function for synthesis
void updateSynth();

#endif
