#include "Global.h"
#include "audcon.h"

//────────────────────────────────────────────────────────────────────────────
// 1) Initialize flags and default parameter values

bool env1on = false;

float vcoAgain       = 0.4f;
float vcoBgain       = 0.4f;
float vcoCgain       = 0.4f;
float SubVol         = 0.4f;
float crossMod       = 0.0f;
float vcoVol         = 0.07f;
float mainVol        = 1.0f;

int   shapeA         = 0;
int   shapeB         = 0;
int   shapeC         = 1;
int   shapeSub       = 0;
float volA_pot       = 0.0f;
int   freqA          = 440;

int   cutoff         = 2000;
int   filtSus        = 0;
float reso           = 1.0f;
float octave         = 1.0f;
float filtAtt        = 0.0f;
float filtDec        = 0.0f;
float filtRel        = 0.0f;
float filtAmount     = 0.0f;
int   filterMode     = 0;
int   filterEdit     = 0;

float envSus         = 0.0f;
float envAtt         = 0.0f;
float envDec         = 0.0f;
float envRel         = 0.0f;

float lfoAamplitude  = 0.0f;
float lfoAfrequency  = 0.0f;
int   lfoAdelay      = 0;
int   lfoAattack     = 0;
int   lfoAdecay      = 0;
int   lfoArelease    = 0;
int   lfoAEdit       = 0;
float lfoAsustain    = 0.0f;
int   lfoAshape      = 0;
int   lfoAdestination = 0;
float ampMod         = 0.0f;

float lfoBamplitude  = 0.0f;
float lfoBfrequency  = 0.0f;

float outGain        = 0.8f;
float dlyAmount      = 0.0f;
float dlyTimeL       = 0.0f;
float dlyTimeR       = 0.0f;

float revMix         = 0.0f;
float revSize        = 0.0f;

float tresh          = 10.0f;
float tresh2         = 20.0f;
int   timer          = 6;
unsigned long prevTimer = 0;

// UI control variables and their “old” values

int   shapeA_btn            = 0;
int   oldShapeA_btn         = 0;

int   shapeB_btn            = 0;
int   oldShapeB_btn         = 0;

int   shapeC_btn            = 0;
int   oldShapeC_btn         = 0;

int   shapeSub_btn          = 0;
int   oldShapeSub_btn       = 0;

int   crossModulation_pot   = 0;
int   oldCrossModulation_pot = 0;

int   volB_pot              = 0;
int   oldVolB_pot           = 0;

int   volC_pot              = 0;
int   oldVolC_pot           = 0;

int   volSub_pot            = 0;
int   oldVolSub_pot         = 0;

// “volA_pot” is declared in the header; define its “old” value here:
float oldVolA_pot            = 0.0f;

int   attack_pot            = 0;
int   oldAttack_pot         = 0;

int   decay_pot             = 0;
int   oldDecay_pot          = 0;

float sustain_pot           = 0.0f;
float oldSustain_pot        = 0.0f;

int   lfoAamplitude_pot     = 0;
int   oldLfoAamplitude_pot  = 0;

int   lfoFrequency_pot      = 0;
int   oldLfoFrequency_pot   = 0;

int   lfoAttack_pot         = 0;
int   oldLfoAttack_pot      = 0;

int   lfoDecay_pot          = 0;
int   oldLfoDecay_pot       = 0;

int   lfoSustain_pot        = 0;
int   oldLfoSustain_pot     = 0;

int   lfoShape_btn          = 0;
int   oldLfoShape_btn       = 0;

int   lfoDestination_btn    = 0;
int   oldLfoDestination_btn = 0;

int   lfoBAmplitude_pot     = 0;
int   oldLfoBAmplitude_pot  = 0;

int   lfoBFrequency_pot     = 0;
int   oldLfoBFrequency_pot  = 0;

int   dlyAmount_pot         = 0;
int   oldDlyAmount_pot      = 0;

int   dlyTime_pot           = 0;
int   oldDlyTime_pot        = 0;

int   revMix_pot            = 0;
int   oldRevMix_pot         = 0;

int   revSize_pot           = 0;
int   oldRevSize_pot        = 0;

// Granular playback parameters
float FreezeT              = 150.0f;
float PitchShift           = 1.0f;
float Ratio                = 1.0f;

// Sample-bank buffer for loading a sample into RAM
int16_t sampleBank[GRANULAR_MEMORY_SIZE] = { 0 };

// Linkable constant for buffer length
const int kGranularMemorySize = GRANULAR_MEMORY_SIZE;

// Flag for whether sampleBank has valid data
bool granularSampleLoaded = false;


//────────────────────────────────────────────────────────────────────────────
// 3) Define the actual RAM area that the granular engine will use
int16_t granularMemory[GRANULAR_MEMORY_SIZE] = { 0 };

//────────────────────────────────────────────────────────────────────────────
// 4) Initialize the six NoteButtons
NoteButton noteButtons[6] = {
    { 27, "C", 261.63f, Bounce(27, 15) },
    { 28, "D", 293.66f, Bounce(28, 15) },
    { 29, "E", 329.63f, Bounce(29, 15) },
    { 30, "F", 349.23f, Bounce(30, 15) },
    { 31, "G", 392.00f, Bounce(31, 15) },
    { 32, "A", 440.00f, Bounce(32, 15) }
};

//────────────────────────────────────────────────────────────────────────────
// 5) Note-on and Note-off helper functions

void triggerNoteOn(float freq) {
    // Set each VCO to the given frequency
    vcoA1.frequency(freq);
    vcoB1.frequency(freq);
    vcoC1.frequency(freq);

    // Trigger the LFO envelope and main envelope for a normal synth voice
    lfoAenv1.noteOn();
    env1.noteOn();

    // (Optional) Uncomment to start granular “freeze” if you want a random grain:
    // int grain_size = random(10000, GRANULAR_MEMORY_SIZE);
    // granular1.beginFreeze(grain_size);
    // float grain_speed = random(15, 200) / 100.0f;
    // granular1.setSpeed(grain_speed);
}

void triggerNoteOff() {
    // Release the LFO envelope and main envelope
    lfoAenv1.noteOff();
    env1.noteOff();

    // Stop any granular playback that might still be running
    granular1.stop();
}
