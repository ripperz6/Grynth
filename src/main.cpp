// main.cpp
#include <Arduino.h>
#include "audcon.h"
#include "Global.h"
#include "midih.h"
#include <MIDI.h>
#include "ui.h"
#include "display.h"

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11 
#define SDCARD_SCK_PIN   13 


void setup() {
  Serial.begin(9600);
  AudioMemory(900);
  setupMIDI();
  sgtl5000_1.enable();                                  //Audio Shield Ena
  sgtl5000_1.volume(0.8);     //Audio Shield Vol
  queue1.begin();
  
  setupOLED();

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  vcoA1.begin(vcoVol, 150, WAVEFORM_SAWTOOTH);          //Wave A def
  vcoB1.begin(vcoVol, 150, WAVEFORM_SQUARE);            //Wave B def
  vcoC1.begin(vcoVol * 1.5, 150, WAVEFORM_ARBITRARY);   //Wave C def

  filter1.octaveControl(7);                             //Filter Control 7 Octave
  filterEnv1.sustain(0);         
  filterMode1.gain(0, 0);               //Low pass filter signal path
  filterMode1.gain(1, 1);               //Band pass filter signal path
  filterMode1.gain(2, 0);               //High pass filter 0 = off 1 = on signal path

  MixerGran.gain(0, 1);
  MixerGran.gain(1, 1);

  GranularMode1.gain(0, 1); // dry
  GranularMode1.gain(1, 0.5); // Gran
                          
  granular1.begin(granularMemory, GRANULAR_MEMORY_SIZE);

  lfoA1.begin(0.5, 2, WAVEFORM_SINE);                   //LFO A def shape
  lfoB1.begin(0.5, 1, WAVEFORM_TRIANGLE);               //LFO B def gain freq shape



  env1.attack(10.5);
  env1.decay(35);
  env1.sustain(0.3);
  env1.release(50);

  mix1.gain(0,0.8);
  finalMix.gain(0,1);

  dlyFiltL.frequency(4000);
  dlyFiltR.frequency(3000);

  dlyMixL.gain(0, 0.8);                                   //Dry Voice Mix
  dlyMixL.gain(1, 0.5);                                   //Delay Feedback Mix
  dlyMixR.gain(0, 0.8);                                   
  dlyMixR.gain(1, 0.5);                                   

  for (int i = 1; i < 8; ++i) {                         //Disable Delay
    dlyL.disable(i);
    dlyR.disable(i);
  }

  reverb.roomsize(0.9);                                 //Reverb Size Def
  reverb.damping(0.8);                                  //Reveb Damp Def

  dlyL.delay(0, 500);                                   //Delay L Channel out 0, freq
  dlyR.delay(0, 333);                                   //Delay R Channel out 0, freq

  patchCord2.disconnect();                              //LFOA Pitch connect Wave A
  patchCord3.disconnect();                              //LFOA Pitch connect Wave B                           
  patchCord4.disconnect();                              //LFOA Pitch connect Wave C
  patchCord5.disconnect();                              //Amplitude LFo
  patchCord6.disconnect();                              //LFOA Filter
 

  for (int i = 0; i < 6; ++i) {
    pinMode(27 + i, INPUT_PULLUP);
  }
  pinMode(1,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  
}

void loop() {
  MIDI.read();
  updateKnobs();
  updateButtons();
  updateMainVolume();
  WaveformUpdate();
  updateFilterMode();
  updateLFO();
  //EnvelopeUpdate()
  drawMenuScreen();
  GranularUpdate();
   if (queue2.available() > 0) {
    // 1a) Read raw 16-bit PCM samples (128 samples per buffer by default):
    int16_t *rawPCM = queue2.readBuffer();
i
    // 1b) Example: copy into your sampleBank (or directly into granularMemory):
    //     – assume sampleBank[] is sized to hold at least GRANULAR_MEMORY_SIZE samples
    //     – and you want to append or process only the first 128 samples right now:
    memcpy(sampleBank, rawPCM, 128 * sizeof(int16_t));

    // 1c) Free the buffer so the AudioRecordQueue can reuse it:
    queue2.freeBuffer();

    // 1d) Now you can pass “sampleBank” to your granular processor:
    //     e.g. if you only needed to “beginFreeze” once you have enough samples:
    if (!granularSampleLoaded) {
        // (However you load a full sample—this is just a toy example:)
        for (int i = 0; i < 128; i++) {
            granularMemory[i] = sampleBank[i];
        }
        granularSampleLoaded = true;
    }

 static unsigned long lastDisplay = 0;
  if (millis() - lastDisplay > 100) {
    drawMenuScreen();
    lastDisplay = millis();
  }

  delay(1); 

  
  //lfoA1.begin(0.01, 2, WAVEFORM_SINE);     //LFOA Amplitude, Freq, Shape
  //lfoB1.begin(0.1, 2, WAVEFORM_SINE);   //LFOB Amplitude, Freq, Shape
  //patchCord2.connect();                              //LFOA Pitch connect Wave A
 //patchCord3.connect();                              //LFOA Pitch connect Wave B                           
 // patchCord4.connect();                              //LFOA Pitch connect Wave C
  

  modMix1.gain(0, 0.5);                   //vcoB mod Mix
  modMix1.gain(1, 0.5);                   //LFO mod Mix Wave B

  dc1.amplitude(1);                   //DC control signal to filter

  filterMix1.gain(0, 0);                //LFO merge with Filter Envelope
  filterMix1.gain(1, 0);              //Filter Envelope Control

  mix1.gain(0, 0.8);                      //Allow note 0 to pass to Final Mix

  reverb.roomsize(0.6);                 //Reverb Size
  reverb.damping(0.4);                  //Reverb Damp

  dlyMixL.gain(0, 0.5);                   //Dry Sound of Delay L
  dlyMixL.gain(1, 0.5);                   //Delay Feedback

  dlyMixR.gain(0, 0.5);                   //Dry Sound of Delay R
  dlyMixR.gain(1, 0.5);                   //Delay Feedback

  fxL.gain(0, 0.7);                       //Dry Sound L
  fxL.gain(1, 0.2);                       //Reverb Mix L
  fxL.gain(2, 0);                       //Reveb Mix L

  fxR.gain(0, 0.7);                       //Dry Sound R
  fxR.gain(1, 0.2);                       //Reverb Mix R
  fxR.gain(2, 0);                       //Reverb Mix R

 
 if (currentMode == GRAN_MODE) {
   if (playSdWav1.isPlaying() == false) {
    
    delay(5); // brief delay for the library read WAV info
   }
  if (button1.fallingEdge()) {
    granular1.beginFreeze(FreezeT);
  } else if (button1.risingEdge()) {
    granular1.stop();
  }

  if (button2.fallingEdge()) {
    granular1.beginPitchShift(PitchShift);
  } else if (button2.risingEdge()) {
    granular1.stop();
  }
}
  else if (currentMode != GRAN_MODE)
   playSdWav1.stop();

for (int i = 0; i < 6; ++i) {
  noteButtons[i].button.update();

  if (noteButtons[i].button.fallingEdge()) {
    float freq = noteButtons[i].frequency;
    triggerNoteOn(freq);

    Serial.print("Note: ");
    Serial.println(noteButtons[i].name);
  }

  if (noteButtons[i].button.risingEdge()) {
    triggerNoteOff();

 
}

}
//Serial.print("AudioMemory Usage: ");
//Serial.println(AudioMemoryUsageMax());
}
}