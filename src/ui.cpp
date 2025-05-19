//ui.cpp
#include "ui.h"
#include "Bounce.h"
#include "Global.h"
#include "audcon.h"
#include "midih.h"
#include "ui.h"

// Define the global variable declared in ui.h
ControlMode currentMode = VOLUME_MODE;

// Function to deactivate all knobs when mode changes
void deactivateAllKnobs() {
  for (int i = 0; i < 5; i++) {
    knobs[i].active = false;
    // Read current physical position but don't apply
    analogReadAveraging(200);
    knobs[i].lastKnobValue = analogRead(knobs[i].pin) / 1023.0f;
  }
}

// Global parameters structure
SynthParameters params;



Knob knobs[5] = {
  {A1, 0.0, 0.0, false},
  {A0, 0.0, 0.0, false},
  {A12, 0.0, 0.0, false},
  {A16, 0.0, 0.0, false},
  {A17, 0.0, 0.0, false}
};

Bounce button0 = Bounce(1, 15);
Bounce button1 = Bounce(2, 15);
Bounce button2 = Bounce(9, 15);



int button0_count = 0;

void setupUI() {
  // Initialize pins
  for (int i = 0; i < 5; i++) {
    pinMode(knobs[i].pin, INPUT);
    analogReadAveraging(200);
    knobs[i].KnobValue = analogRead(knobs[i].pin) / 1023.0f;
    knobs[i].lastKnobValue = knobs[i].KnobValue;
    knobs[i].active = true;  // Knobs are active during initial setup
  }

  // Initialize default parameter values
  // Volume mode defaults
  params.volume.mainVol = 0.5f;
  params.volume.vcoAgain = 0.5f;
  params.volume.vcoBgain = 0.5f;
  params.volume.vcoCgain = 0.5f;
  params.volume.SubVol = 0.5f;

  // Filter mode defaults
  params.filter.cutoff = 5000.0f;
  params.filter.reso = 0.7f;
  params.filter.octave = 3.5f;
  params.filter.filtAtt = 100.0f;
  params.filter.filtDec = 200.0f;
  params.filter.filtRel = 500.0f;
  params.filter.filtSus = 0.5f;
  params.filter.filterMode = 0;
  params.filter.filterEdit = false;

  // Envelope Default
  params.env.envAtk = 3.5f;
  params.env.envDec = 200.0f;
  params.env.envRel = 300.0f;
  params.env.envSus = 0.5f;

  // Waveform mode defaults
  params.waveform.shapeA_btn = 0;
  params.waveform.shapeB_btn = 0;
  params.waveform.shapeC_btn = 0;

  // Apply initial values to audio components
  updateMainVolume();
  updateFilterParam();
  updateFilterMode();
  WaveformUpdate();
  EnvelopeUpdate();
  updateLFO();
}

void updateKnobs() {
  // Track which knob was changed this update
  int changedKnob = -1;
  bool knobChanged = false;
  
  for (int i = 0; i < 5; i++) {
    float raw = analogRead(knobs[i].pin);
    float newValue = raw / 1023.0f;

    // Check if knob has moved enough from its last position
    if (fabs(newValue - knobs[i].lastKnobValue) > 0.015f) {
      // Update the last known position regardless of active state
      knobs[i].lastKnobValue = newValue;
      
      // Only if knob is active or the movement is significant enough to activate it
      if (knobs[i].active || fabs(newValue - knobs[i].KnobValue) > 0.015f) {
        knobs[i].active = true; // Knob is now active
        knobs[i].KnobValue = newValue; // Update the value used for parameters
        
        //Serial.print("Knob ");
        //Serial.print(i);
        //Serial.print(" Value: ");
        //Serial.print(newValue, 2);
        //Serial.println(" (Active)");
        
        changedKnob = i;
        knobChanged = true;
      } else {
        //Serial.print("Knob ");
        //Serial.print(i);
        //Serial.print(" moved to ");
        //Serial.print(newValue, 2);
        //Serial.println(" (Inactive - waiting for take-over)");
      }
    }
  }
// Initialize currentMode

// Initialize params
SynthParameters params;
  // Only update parameters if a knob actually changed
  if (knobChanged) {
    // We only update based on the specific knob that changed
    switch(currentMode) {
      case VOLUME_MODE: 
        updateVolumeParams();
        updateMainVolume();
        break;
      case FILTER_MODE: 
        updateFilterParams();
        updateFilterParam();
        break;
      case WAVEFORM_MODE:
        updateWaveformParams();
        WaveformUpdate();
        break;
      case LFO_MODE:
        updateLFOParams();
        updateLFO();
        break;
      case ENVELOPE_MODE: 
        updateEnvelopeParams();
        EnvelopeUpdate();
        break;
      case EFFECTS_MODE:
       // updateEffectsParams();
        break;
      case SAMPLING_MODE:
       // updateSamplingParams();
        break;
    }
  }
}

void updateButtons() {
  button0.update();
  button1.update();
  button2.update();

  if (button0.fallingEdge()) {
    button0_count = (button0_count + 1) % 7;
    currentMode = static_cast<ControlMode>(button0_count);
    
    // Deactivate all knobs when mode changes
    deactivateAllKnobs();
    
    //Serial.print("Mode changed to: ");
    switch(currentMode) {
      case VOLUME_MODE: Serial.println("Volume"); break;
      case FILTER_MODE: Serial.println("Filter"); break;
      case WAVEFORM_MODE: Serial.println("Waveform"); break;
      case LFO_MODE: Serial.println("LFO"); break;
      case ENVELOPE_MODE: Serial.println("ENV"); break;
      case EFFECTS_MODE: Serial.println("Effects"); break;
      case SAMPLING_MODE: Serial.println("Sampling"); break;
      default: 
        //Serial.println("Unknown");
        currentMode = VOLUME_MODE;
        break;
    }
  }

  // Button 1 toggles filter mode
  if (button1.fallingEdge() && currentMode == FILTER_MODE) {
    params.filter.filterMode = (params.filter.filterMode + 1) % 3;
    updateFilterMode();
  }

  // Button 2 toggles filter edit mode
  if (button2.fallingEdge() && currentMode == FILTER_MODE) {
    params.filter.filterEdit = !params.filter.filterEdit;
    //Serial.print("Filter edit mode: ");
    //Serial.println(params.filter.filterEdit ? "Envelope" : "Cutoff/Res");
  }
  
// Button 1 toggles lfo mode
  if (button1.fallingEdge() && currentMode == LFO_MODE) {
    params.lfo.lfoAEdit = !params.lfo.lfoAEdit;
  }
  
}
//update parameters based on knob values
void updateVolumeParams() {
  // Only update parameters for active knobs
  if (knobs[0].active) params.volume.mainVol = knobs[0].KnobValue;
  if (knobs[1].active) params.volume.vcoAgain = knobs[1].KnobValue;
  if (knobs[2].active) params.volume.vcoBgain = knobs[2].KnobValue;
  if (knobs[3].active) params.volume.vcoCgain = knobs[3].KnobValue;
  if (knobs[4].active) params.volume.SubVol = knobs[4].KnobValue;
}

void updateFilterParams() {
  if (!params.filter.filterEdit) {
    // Cutoff/Resonance mode
    if (knobs[1].active) params.filter.cutoff = knobs[1].KnobValue * 20000;
    if (knobs[2].active) params.filter.reso = 0.7 + (knobs[2].KnobValue * 4.3);
    if (knobs[3].active) params.filter.octave = knobs[3].KnobValue * 7;
  } else {
    // Envelope mode
    if (knobs[1].active) params.filter.filtAtt = 10.5 + (knobs[1].KnobValue * 11869.5);
    if (knobs[2].active) params.filter.filtDec = 35 + (knobs[2].KnobValue * 11845);
    if (knobs[3].active) params.filter.filtRel = 300 + (knobs[3].KnobValue * 11580);
    if (knobs[4].active) params.filter.filtSus = knobs[4].KnobValue;
  }
}

void updateWaveformParams() {
  if (knobs[1].active) params.waveform.shapeA_btn = constrain((int)(knobs[1].KnobValue * 4), 0, 3);
  if (knobs[2].active) params.waveform.shapeB_btn = constrain((int)(knobs[2].KnobValue * 4), 0, 3);
  if (knobs[3].active) params.waveform.shapeC_btn = constrain((int)(knobs[3].KnobValue * 4), 0, 3);
}

void updateLFOParams() {
  if (!params.lfo.lfoAEdit) {
    if (knobs[1].active) params.lfo.lfoAatk = 10.5 + (knobs[1].KnobValue*11869.5);
    if (knobs[2].active) params.lfo.lfoAdec = 35 + (knobs[2].KnobValue*11845);     
    if (knobs[3].active) params.lfo.lfoArel = 300 + (knobs[3].KnobValue*11580); 
    if (knobs[4].active) params.lfo.lfoAsus = knobs[4].KnobValue;     
  } else {
    if (knobs[1].active) params.lfo.lfoAfreq = knobs[1].KnobValue * 20; // 0-20 Hz
    if (knobs[2].active) params.lfo.lfoAamp = knobs[2].KnobValue;     // 0-1 depth
  }
}

void updateLFO(){
  lfoAEdit = params.lfo.lfoAEdit ? 1 : 0;

  if (lfoAEdit == 0){
    lfoAamplitude = params.lfo.lfoAamp;
    lfoAfrequency = params.lfo.lfoAfreq;

    lfoA1.amplitude(lfoAamplitude);
    lfoA1.frequency(lfoAfrequency);
    //Serial.print("LFO Amp: "); Serial.println(lfoAamplitude);
    //Serial.print("LFO Freq: "); Serial.println(lfoAfrequency);
  } else {
    lfoAattack = params.lfo.lfoAatk;
    lfoAdecay = params.lfo.lfoAdec;
    lfoArelease = params.lfo.lfoArel;
    lfoAsustain = params.lfo.lfoAsus;

    lfoAenv1.attack(lfoAattack);
    lfoAenv1.decay(lfoAdecay);
    lfoAenv1.release(lfoArelease);
    lfoAenv1.sustain(lfoAsustain);
  }

}

void updateEnvelopeParams(){
  if (knobs[1].active) params.env.envAtk = 10.5 + (knobs[1].KnobValue*11869.5);
  if (knobs[2].active) params.env.envDec = 35 + (knobs[2].KnobValue*11845);  
  if (knobs[3].active) params.env.envRel = 300 + (knobs[3].KnobValue*11580);
  if (knobs[4].active) params.env.envSus = knobs[4].KnobValue;    
} 

void updateEffectsParams() {
  if (knobs[0].active) params.dly.dlyMix = knobs[0].KnobValue;
  if (knobs[1].active) params.dly.dlyTime = knobs[1].KnobValue*10000;
  if (knobs[2].active) params.reverb.size = knobs[2].KnobValue;
  if (knobs[3].active) params.reverb.damping = knobs[3].KnobValue;
  if (knobs[4].active) params.reverb.reverbMix = knobs[4].KnobValue;

  dlyL.delay(0,params.dly.dlyTime);
  dlyR.delay(0,params.dly.dlyTime);
  reverb.roomsize(params.reverb.size);                                 //Reverb Size Def
  reverb.damping(params.reverb.damping);                                  //Reveb Damp Def
  reverb.damping(params.reverb.reverbMix);

  fxL.gain(1, params.reverb.reverbMix);                       //Reverb Mix L
  fxR.gain(1, params.reverb.reverbMix);                       //Reverb Mix R
  fxL.gain(2, params.dly.dlyMix);                       //Reverb Mix L
  fxR.gain(2, params.dly.dlyMix);                       //Reverb Mix R
}

void updateSamplingParams() {
  if (knobs[1].active) params.sampling.param1 = knobs[1].KnobValue;   //Mic Gain
  
  // TODO: Implement actual sampling parameter update
  //Serial.println("Sampling parameters updated");
}

// Existing functions now use stored parameters rather than direct knob values
void updateMainVolume() {
  mainVol = params.volume.mainVol*0.8;
  vcoAgain = params.volume.vcoAgain;
  vcoBgain = params.volume.vcoBgain;
  vcoCgain = params.volume.vcoCgain;
  
  finalMix.gain(0, mainVol);
  voiceMix1.gain(0, vcoAgain);  // Wave A 
  voiceMix1.gain(1, vcoBgain);  // Wave B
  voiceMix1.gain(2, vcoCgain);  // Wave C
  
  //Serial.print("Main volume: ");
  //Serial.println(mainVol, 2);
}

void updateFilterMode() {
  filterMode = params.filter.filterMode;
  filterMode = constrain(filterMode, 0, 2);
  
  filterMode1.gain(0, filterMode == 1 ? 1 : 0); // Bandpass
  filterMode1.gain(1, filterMode == 0 ? 1 : 0); // Lowpass
  filterMode1.gain(2, filterMode == 2 ? 1 : 0); // Highpass
  
  //Serial.print("Filter mode: ");
  //Serial.println(filterMode);
}

void updateFilterParam() {
  filterEdit = params.filter.filterEdit ? 1 : 0;
  
  if (filterEdit == 0) {
    cutoff = params.filter.cutoff;
    reso = params.filter.reso;
    octave = params.filter.octave;
    
    filter1.frequency(cutoff);
    filter1.resonance(reso);
    filter1.octaveControl(octave);
    
    //Serial.print("Filter Freq: ");
    //Serial.print(cutoff, 2);
    //Serial.print(", Res: ");
    //Serial.print(reso, 2);
    //Serial.print(", Oct: ");
    //Serial.println(octave, 2);
  } else {
    filtAtt = params.filter.filtAtt;
    filtDec = params.filter.filtDec;
    filtRel = params.filter.filtRel;
    filtSus = params.filter.filtSus;
    
    filterEnv1.attack(filtAtt);
    filterEnv1.decay(filtDec);
    filterEnv1.release(filtRel);
    filterEnv1.sustain(filtSus);
    
    //Serial.print("Filter Env - A: ");
    //Serial.print(filtAtt, 2);
    //Serial.print(", D: ");
    //Serial.print(filtDec, 2);
    //Serial.print(", S: ");
    //Serial.print(filtSus, 2);
    //Serial.print(", R: ");
    //Serial.println(filtRel, 2);
  }
}

void WaveformUpdate() {

  // VCO A waveform
  shapeA_btn = params.waveform.shapeA_btn;
  switch(shapeA_btn) {
    case 0: vcoA1.begin(WAVEFORM_SINE); break;
    case 1: vcoA1.begin(WAVEFORM_SAWTOOTH); break;
    case 2: vcoA1.begin(WAVEFORM_TRIANGLE); break;
    case 3: vcoA1.begin(WAVEFORM_SQUARE); break;
  }

  //Serial.print("VCO A Wave: ");
  //Serial.println(shapeA_btn);
  
  // VCO B waveform
  shapeB_btn = params.waveform.shapeB_btn;
  switch(shapeB_btn) {
    case 0: vcoB1.begin(WAVEFORM_SINE); break;
    case 1: vcoB1.begin(WAVEFORM_SAWTOOTH); break;
    case 2: vcoB1.begin(WAVEFORM_TRIANGLE); break;
    case 3: vcoB1.begin(WAVEFORM_SQUARE); break;
  }
 
  //Serial.print("VCO B Wave: ");
  //Serial.println(shapeB_btn);
  
  // VCO C waveform
  shapeC_btn = params.waveform.shapeC_btn;
  switch(shapeC_btn) {
    case 0: vcoC1.begin(WAVEFORM_SINE); break;
    case 1: vcoC1.begin(WAVEFORM_SAWTOOTH); break;
    case 2: vcoC1.begin(WAVEFORM_TRIANGLE); break;
    case 3: vcoC1.begin(WAVEFORM_SQUARE); break;
  }

  //Serial.print("VCO C Wave: ");
  //Serial.println(shapeC_btn);
  
  }

  void EnvelopeUpdate(){
    envAtt = params.env.envAtk;
    envDec = params.env.envDec;
    envRel = params.env.envRel;
    envSus = params.env.envSus; 
    env1.attack(envAtt);
    env1.decay(envDec);
    env1.sustain(envSus);
    env1.release(envRel);
  }