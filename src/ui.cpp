#include "ui.h"
#include "Bounce.h"
#include "Global.h"
#include "audcon.h"


Knob knobs[5] = {
  {A1, 0.0, 0.0},
  {A0, 0.0, 0.0},
  {A12, 0.0, 0.0},
  {A17, 0.0, 0.0},
  {A16, 0.0, 0.0}
};

Bounce button0 = Bounce(1, 15);
Bounce button1 = Bounce(2, 15);
Bounce button2 = Bounce(9, 15);

enum ControlMode {
  VOLUME_MODE,
  FILTER_MODE,
  WAVEFORM_MODE,
  LFO_MODE,
  EFFECTS_MODE
};

ControlMode currentMode = VOLUME_MODE;
int button0_count = 0;

void setupUI() {
  for (int i = 0; i < 5; i++) {
    pinMode(knobs[i].pin, INPUT);
    knobs[i].KnobValue = analogRead(knobs[i].pin) / 1023.0f;
    knobs[i].lastKnobValue = knobs[i].KnobValue;
  }
}

void updateKnobs() {
  for (int i = 0; i < 5; i++) {
    float raw = analogRead(knobs[i].pin);
    float newValue = raw / 1023.0f;

    if (fabs(newValue - knobs[i].lastKnobValue) > 0.1f) {
      knobs[i].KnobValue = newValue;
      knobs[i].lastKnobValue = newValue;

      Serial.print("Knob ");
      Serial.print(i);
      Serial.print(" KnobValue: ");
      Serial.println(knobs[i].KnobValue, 2);
      knobs[i].lastKnobValue = knobs[i].KnobValue;

      switch(currentMode) {
        case VOLUME_MODE: updateMainVolume(); 
        updateVoiceMixGain();
        break;
        case FILTER_MODE: updateFilterParam(); break;
        case WAVEFORM_MODE: WaveformUpdate(); break;
        //case LFO_MODE: updateLFOParams(); break;
        //case EFFECTS_MODE: updateEffects(); break;
      }
    }
  }
}

void updateButtons() {
  button0.update();
  button1.update();
  button2.update();

  if (button0.fallingEdge()) {
    button0_count = (button0_count + 1) % 5;
    currentMode = static_cast<ControlMode>(button0_count);
    
    Serial.print("Mode changed to: ");
    switch(currentMode) {
      case VOLUME_MODE: //Serial.println("Volume"); 
      break;
      case FILTER_MODE: //Serial.println("Filter"); 
      break;
      case WAVEFORM_MODE: //Serial.println("Waveform"); 
      break;
      case LFO_MODE: //Serial.println("LFO"); 
      break;
      case EFFECTS_MODE: //Serial.println("Effects"); 
      break;
      default: //Serial.println("Unkown");
      currentMode = VOLUME_MODE;
      break;
    } 
}

// Button 1 toggles filter mode
  if (button1.fallingEdge() && currentMode == FILTER_MODE) {
    filterMode = (filterMode + 1) % 3;
    updateFilterMode();
  }

 // Button 2 toggles filter edit mode
  if (button2.fallingEdge() && currentMode == FILTER_MODE) {
    filterEdit = !filterEdit;
    //Serial.print("Filter edit mode: ");
    //Serial.println(filterEdit ? "Envelope" : "Cutoff/Res");
  }
}  

//volume
void updateMainVolume(){
    mainVol = knobs[0].KnobValue;
    finalMix.gain(0, mainVol);
    //Serial.print("Main volume: ");
    //Serial.println(mainVol*10, 2);
}

//Filter
void updateFilterMode(){
  filterMode = constrain(filterMode, 0, 2);
  
  filterMode1.gain(0, filterMode == 1 ? 1 : 0); // Bandpass
  filterMode1.gain(1, filterMode == 0 ? 1 : 0); // Lowpass
  filterMode1.gain(2, filterMode == 2 ? 1 : 0); // Highpass
  
  //Serial.print("Filter mode: ");
  //Serial.println(filterMode);
}

void updateFilterParam(){
    if (filterEdit < 0){
        filterEdit = 0;
    }
    else{
        filterEdit = 1;
    }
    
    if (filterEdit == 0){
        cutoff = knobs[1].KnobValue*20000;
        reso = 0.7+(knobs[2].KnobValue * 4.3);
        octave = knobs[3].KnobValue * 7;
        filter1.frequency(cutoff);
        filter1.resonance(reso);
        filter1.octaveControl(octave);
        //Serial.print('FFreq: ');
        //Serial.println(cutoff, 2);

    }
    else{
        filtAtt = 10.5 + (knobs[1].KnobValue * 11869.5);
        filtDec = 35 + (knobs[2].KnobValue * 11845);
        filtRel = 300 + (knobs[3].KnobValue * 11580);
        filtSus = knobs[4].KnobValue;
        filterEnv1.attack(filtAtt);
        filterEnv1.decay(filtDec);
        filterEnv1.release(filtRel);
        filterEnv1.sustain(filtSus);
        //Serial.print('FEnv: ');
    }
}


//Each Wave Gain
void updateVoiceMixGain(){
    vcoAgain = knobs[1].KnobValue;
    vcoBgain = knobs[2].KnobValue;
    vcoCgain = knobs[3].KnobValue;
    SubVol   = knobs[4].KnobValue;

    voiceMix1.gain(0, vcoAgain);                 //Wave A 
    voiceMix1.gain(1, vcoBgain);                 //Wave B
    voiceMix1.gain(2, vcoCgain);                 //Wave C
    voiceMix1.gain(3, SubVol);                 //Wave modulate lfo

}

void WaveformUpdate(){
  //VCOA
  static int lastShapeA = -1;
  shapeA_btn = constrain((int)(knobs[1].KnobValue * 4), 0, 3);
  
  if (shapeA_btn != lastShapeA) {
    switch(shapeA_btn) {
      case 0: vcoA1.begin(WAVEFORM_SINE); break;
      case 1: vcoA1.begin(WAVEFORM_SAWTOOTH); break;
      case 2: vcoA1.begin(WAVEFORM_TRIANGLE); break;
      case 3: vcoA1.begin(WAVEFORM_SQUARE); break;
    }
    lastShapeA = shapeA_btn;
    volA_pot = knobs[1].KnobValue;
    vcoA1.amplitude(volA_pot);
    //Serial.print("VCO A Wave: ");
    //Serial.println(shapeA_btn);
    
  }
  //VCOB
  static int lastShapeB = -1;
  shapeB_btn = constrain((int)(knobs[2].KnobValue * 4), 0, 3);  
  if (shapeB_btn != lastShapeB) {
    switch(shapeB_btn) {
      case 0: vcoB1.begin(WAVEFORM_SINE); break;
      case 1: vcoB1.begin(WAVEFORM_SAWTOOTH); break;
      case 2: vcoB1.begin(WAVEFORM_TRIANGLE); break;
      case 3: vcoB1.begin(WAVEFORM_SQUARE); break;
    }
    lastShapeB = shapeB_btn;
    volB_pot = knobs[2].KnobValue;
    vcoB1.amplitude(volB_pot);
    //Serial.print("VCO B Wave: ");
    //Serial.println(shapeB_btn);
    
  }
  //VCOC  
  static int lastShapeC = -1;
  shapeC_btn = constrain((int)(knobs[3].KnobValue * 4), 0, 3);  
  if (shapeC_btn != lastShapeC) {
    switch(shapeC_btn) {
      case 0: vcoC1.begin(WAVEFORM_SINE); break;
      case 1: vcoC1.begin(WAVEFORM_SAWTOOTH); break;
      case 2: vcoC1.begin(WAVEFORM_TRIANGLE); break;
      case 3: vcoC1.begin(WAVEFORM_SQUARE); break;
    }
    lastShapeC = shapeC_btn;
    volC_pot = knobs[1].KnobValue;
    vcoC1.amplitude(volA_pot);
    //Serial.print("VCO C Wave: ");
    //Serial.println(shapeC_btn);
    
  }
  //SUB
  static int lastShapeSub = -1;
  shapeSub_btn = constrain((int)(knobs[4].KnobValue * 4), 0, 3);    
  if (shapeSub_btn != lastShapeSub) {
    switch(shapeSub_btn) {
      case 0: sub1.begin(WAVEFORM_SINE); break;
      case 1: sub1.begin(WAVEFORM_SAWTOOTH); break;
      case 2: sub1.begin(WAVEFORM_TRIANGLE); break;
      case 3: sub1.begin(WAVEFORM_SQUARE); break;
    }
    lastShapeSub = shapeSub_btn;
    volSub_pot = knobs[4].KnobValue;
    sub1.amplitude(volSub_pot);
    //Serial.print("Sub Wave: ");
    //Serial.println(shapeSub_btn);
    
  }
}


    //For VCOB
    //For VCOC
    //For Sub
//lfo

//effect
