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

    if (abs(newValue - knobs[i].lastKnobValue) > 0.05f) {
      knobs[i].KnobValue = newValue;
      knobs[i].lastKnobValue = newValue;
      Serial.print("Knob ");
      Serial.print(i);
      Serial.print(" KnobValue: ");
      Serial.println(knobs[i].KnobValue, 2);
      knobs[i].lastKnobValue = knobs[i].KnobValue;
    }
  }
}

Bounce button0 = Bounce(1, 15);
Bounce button1 = Bounce(2, 15);
Bounce button2 = Bounce(9, 15);

int button0_count = 0;
//volume
void updateMainVolume(){
    mainVol = knobs[0].KnobValue;
    finalMix.gain(0, mainVol);
    Serial.print("Main volume set to: ");
    Serial.println(mainVol*10, 2);
}

//Filter
void updateFilterMode(){
    if (filterMode < 0){
        filterMode = 0;
    }
    else if (filterMode > 2){
        filterMode = 2;
    }
    
    if (filterMode == 0) {
        filterMode1.gain(0,0);
        filterMode1.gain(1,1); //Lowpass
        filterMode1.gain(2,0);
        Serial.print("Filter : Lowpass");
    }
    else if (filterMode == 1){
        filterMode1.gain(0,1);
        filterMode1.gain(1,0); //Bandpass
        filterMode1.gain(2,0);
        Serial.print("Filter : Bandpass");
    }
    else{
        filterMode1.gain(0,0);
        filterMode1.gain(1,0); //Highpass
        filterMode1.gain(2,1);
        Serial.print("Filter : Highpass");
    }
}
void updateFilterParam(){
    if (filterEdit < 0){
        filterEdit = 0;
    }
    else{
        filterEdit = 1;
    }
    
    if (filterEdit == 0){
        cutoff = knobs[1].KnobValue;
        reso = knobs[2].KnobValue;
        octave = knobs[3].KnobValue * 7;
        filter1.frequency(cutoff);
        filter1.resonance(reso);
        filter1.octaveControl(octave);
        Serial.print('FFreq: ');
        Serial.println(cutoff, 2);

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
        Serial.print('FEnv: ');
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
    //For VCOA
    static int lastShapeA = -1;
    shapeA_btn = constrain((int)(knobs[0].KnobValue * 4), 0, 3);

    if(shapeA_btn != lastShapeA) {
         switch(shapeA_btn) {
            case 0: vcoA1.begin(WAVEFORM_SINE);
            case 1: vcoA1.begin(WAVEFORM_SAWTOOTH);
            case 2: vcoA1.begin(WAVEFORM_TRIANGLE);
            case 3: vcoA1.begin(WAVEFORM_SQUARE);
        }
        lastShapeA = shapeA_btn;
        Serial.print("VCO A Wave: ");
        Serial.println(shapeA_btn);
    }

    volA_pot = knobs[1].KnobValue;
    vcoA1.amplitude(volA_pot);
    //For VCOB
    //For VCOC
    //For Sub
}
//lfo

//effect
