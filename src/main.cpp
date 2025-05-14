#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <LiquidCrystal.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735

// GUItool: begin automatically generated code
AudioSynthWaveform       lfoA1;          //xy=55,2132.777841567993
AudioEffectEnvelope      lfoAenv1;       //xy=189.55557250976562,2130.0002479553223
AudioSynthWaveform       lfoB1;          //xy=375.55550384521484,2077.333067893982
AudioMixer4              modMix1;        //xy=388.1111297607422,1972.4443321228027
AudioAnalyzeRMS          lfoAread1;      //xy=436.44443130493164,2376.2222328186035
AudioSynthWaveformModulated vcoC1;          //xy=556.333324432373,2227.4444789886475
AudioSynthWaveformModulated vcoB1;          //xy=567.4444618225098,2144.7779445648193
AudioSynthWaveformModulated vcoA1;          //xy=595.2222061157227,2035.4444980621338
AudioSynthWaveformDc     dc1;            //xy=603.2222671508789,2385.111255645752
AudioSynthWaveformModulated sub1;           //xy=605.3333511352539,2322.889009475708
AudioEffectEnvelope      filterEnv1;     //xy=820.5555419921875,2265.7780570983887
AudioMixer4              voiceMix1;      //xy=822.8888397216797,2157.1110076904297
AudioMixer4              filterMix1;     //xy=1028.1112060546875,2243.3334770202637
AudioFilterStateVariable filter1;        //xy=1172.444423675537,2215.333366394043
AudioMixer4              filterMode1;    //xy=1350.0000114440918,2212.5555896759033
AudioEffectEnvelope      env1;           //xy=1480,2237
AudioMixer4              mix1;           //xy=1685.333194732666,2210.999931335449
AudioMixer4              finalMix;       //xy=1838.6665344238281,2214.999605178833
AudioFilterStateVariable dlyFiltL;       //xy=1990.3331718444824,2387.9998874664307
AudioFilterStateVariable dlyFiltR;       //xy=1989.999912261963,2605.3332347869873
AudioEffectDelay         dlyR;           //xy=2113.999912261963,2698.3332347869873
AudioEffectDelay         dlyL;           //xy=2114.999912261963,2464.3332347869873
AudioMixer4              dlyMixR;        //xy=2114.999912261963,2598.3332347869873
AudioEffectFreeverb      reverb;         //xy=2117.6667518615723,1989.3334941864014
AudioMixer4              dlyMixL;        //xy=2125.999912261963,2360.3332347869873
AudioMixer4              fxL;            //xy=2369.333263397217,2197.6665115356445
AudioMixer4              fxR;            //xy=2370.999988555908,2319.666566848755
AudioOutputI2S           i2s1;           //xy=2546.0001487731934,2257.3333168029785
AudioConnection          patchCord1(lfoA1, lfoAenv1);
AudioConnection          patchCord2(lfoAenv1, 0, modMix1, 1);
AudioConnection          patchCord3(lfoAenv1, 0, vcoB1, 0);
AudioConnection          patchCord4(lfoAenv1, 0, vcoC1, 0);
AudioConnection          patchCord5(lfoAenv1, 0, sub1, 0);
AudioConnection          patchCord6(lfoAenv1, lfoAread1);
AudioConnection          patchCord7(lfoAenv1, 0, filterMix1, 0);
AudioConnection          patchCord8(lfoB1, 0, vcoA1, 1);
AudioConnection          patchCord9(lfoB1, 0, vcoB1, 1);
AudioConnection          patchCord10(modMix1, 0, vcoA1, 0);
AudioConnection          patchCord11(vcoC1, 0, voiceMix1, 2);
AudioConnection          patchCord12(vcoB1, 0, voiceMix1, 1);
AudioConnection          patchCord13(vcoB1, 0, modMix1, 0);
AudioConnection          patchCord14(vcoA1, 0, voiceMix1, 0);
AudioConnection          patchCord15(dc1, filterEnv1);
AudioConnection          patchCord16(sub1, 0, voiceMix1, 3);
AudioConnection          patchCord17(filterEnv1, 0, filterMix1, 1);
AudioConnection          patchCord18(voiceMix1, 0, filter1, 0);
AudioConnection          patchCord19(filterMix1, 0, filter1, 1);
AudioConnection          patchCord20(filter1, 0, filterMode1, 0);
AudioConnection          patchCord21(filter1, 1, filterMode1, 1);
AudioConnection          patchCord22(filterMode1, env1);
AudioConnection          patchCord23(env1, 0, mix1, 0);
AudioConnection          patchCord24(mix1, 0, finalMix, 0);
AudioConnection          patchCord25(finalMix, 0, fxL, 0);
AudioConnection          patchCord26(finalMix, reverb);
AudioConnection          patchCord27(finalMix, 0, fxR, 0);
AudioConnection          patchCord28(finalMix, 0, dlyMixL, 0);
AudioConnection          patchCord29(finalMix, 0, dlyMixR, 0);
AudioConnection          patchCord30(dlyFiltL, 0, dlyMixL, 1);
AudioConnection          patchCord31(dlyFiltR, 0, dlyMixR, 1);
AudioConnection          patchCord32(dlyR, 0, dlyFiltR, 0);
AudioConnection          patchCord33(dlyL, 0, dlyFiltL, 0);
AudioConnection          patchCord34(dlyMixR, 0, fxR, 2);
AudioConnection          patchCord35(dlyMixR, dlyR);
AudioConnection          patchCord36(reverb, 0, fxL, 1);
AudioConnection          patchCord37(reverb, 0, fxR, 1);
AudioConnection          patchCord38(dlyMixL, 0, fxL, 2);
AudioConnection          patchCord39(dlyMixL, dlyL);
AudioConnection          patchCord40(fxL, 0, i2s1, 0);
AudioConnection          patchCord41(fxR, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;

//node
///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool env1on = false;

//vco ini vol
//////////////////////////////////////////////////////////////////////////////////////////////////////////
float vcoAVol = 0.4;
float vcoBVol = 0.4;
float vcoCVol = 0.4;
float SubVol = 0.4;
float crossMod;

float vcoVol = 0.07;
float mainVol;

//vco shape
//////////////////////////////////////////////////////////////////////////////////////////////////////////
int shapeA;
int shapeB;
int shapeC = 1;

//filter
///////////////////////////////////////////////////////////////////////////////////////////////////////////
int cutoff =2000;
float reso = 1;
int filtAtt;
int filtDec;
float filtAmount;

int filterMode;

//envelope
///////////////////////////////////////////////////////////////////////////////////////////////////////////
int envAtt;
int envDec;
int envRel;
float envSus;

//lfo A
///////////////////////////////////////////////////////////////////////////////////////////////////////////
float lfoAamplitude;
float lfoAfrequency;
int lfoAdelay;
int lfoAattack;
int lfoAdecay;
int lfoArelease;
float lfoAsustain;

int lfoAshape;
int lfoAdestination;

float ampMod;
//lfo B
///////////////////////////////////////////////////////////////////////////////////////////////////////////
float lfoBamplitude;
float lfoBfrequency;


//delay
///////////////////////////////////////////////////////////////////////////////////////////////////////////
float outGain = 0.8;
float dlyAmount;

float dlyTimeL;
float dlyTimeR;

//reverb
///////////////////////////////////////////////////////////////////////////////////////////////////////////
float revMix;
float revSize;

//Control
///////////////////////////////////////////////////////////////////////////////////////////////////////////
float tresh = 10;
float tresh2 = 20;

int timer = 6;
unsigned long prevTimer;

int shapeA_btn;   ////A Shape
int oldShapeA_btn;
int shapeB_btn;   ////B Shape
int oldShapeB_btn;

int crossModulation_pot;  /////Modulation AxB amount
int oldCrossModulation_pot;

int volA_pot;   ////A Vol
int oldVolA_pot;
int volB_pot;  ////B Vol
int oldVolB_pot;
int volC_pot; ////C Vol
int oldVolC_pot;
int volSub_pot; ////Sub Vol
int oldVolSub_pot;

int attack_pot; ////Attack
int oldAtttack_pot;
int decay_pot; ////Decay
int oldDecay_pot;
float sustain_pot; ////Sustain
float oldSustain_pot;

int lfoAamplitude_pot; ////LFOA Amp
int oldLfoAamplitude_pot;
int lfoFrequency_pot; ////LFOA Freq
int oldLfoFrequency_pot;
int lfoAttack_ot; ////LFOA Atk
int oldLfoAttack_pot;
int lfoDecay_pot; ////LFOA Dcay
int oldLfoDecay_pot;
int lfoSustain_pot; ////LFOA Sustain
int oldLfoSustain_pot;

int lfoShape_btn; ////LFO Shape
int oldLfoShape_btn;
int lfoDestination_btn; ////LFO Position
int oldLfoDestination_btn;

int lfoBAmplitude_pot; ////LFOB Amp
int oldLfoBAmplitude_pot;
int lfoBFrequency_pot; ////LFOB Freq
int oldLfoBFrequency_pot;

int dlyAmount_pot;   ////Delay Amount
int oldDlyAmount_pot;
int dlyTime_pot; ////Delay Time
int oldDlyTime_pot;

int revMix_pot;  ////Reverb Mix
int oldRevMix_pot;
int revSize_pot; ////Reverb Size
int oldRevSize_pot;

//Example Waveform//////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
const int16_t wave1[257] = {
  652,  3250,  5203,  6105,  7141,  8326,  9440, 11564, 14886,
  17802, 20629, 24021, 27018, 27807, 27521, 26708, 25875, 25093, 25204,
  24485, 23202, 21859, 21177, 19946, 19560, 19924, 19937, 18705, 18559,
  20329, 22262, 23031, 22418, 22199, 22275, 24425, 25748, 28291, 27969,
  32767, 15117, -4838, -1354, -2955, -2067, -3567, -4453, -5371, -5142,
  -5939, -6755, -6863, -6361, -5851, -5767, -6034, -6776, -6129, -4368,
  -2801, -3522, -4762, -5516, -5567, -6764, -8322, -9493, -9451, -9420,
  -9843, -10963, -11722, -11960, -12028, -12463, -13045, -13706, -14132, -13916,
  -13653, -14082, -14822, -15241, -15832, -16372, -16585, -16913, -17330, -16569,
  -15381, -15375, -16046, -16141, -16239, -16459, -16157, -16025, -16902, -17597,
  -17334, -17166, -17723, -18196, -18008, -17711, -18036, -18484, -18017, -17146,
  -16864, -16384, -15035, -13779, -12319, -9474, -6602, -5713, -6134, -6873,
  -7828, -8053, -7607, -8256, -9490, -9439, -9436, -11113, -12538, -12173,
  -11091, -9975, -9288, -9955, -10825, -10065, -9003, -9316, -9709, -9378,
  -9581, -10292, -9921, -8130, -6072, -4910, -4697, -4146, -2413,  -431,
  1051,  2551,  4064,  4908,  4981,  4472,  3519,  2515,  1365,  -485,
  -2536, -3776, -4432, -5097, -5307, -4527, -3212, -2048,  -919,   649,
  2463,  3855,  4771,  5420,  5507,  5240,  5691,  7020,  8160,  8578,
  8429,  7917,  7797,  8645,  9542,  9522,  8959,  8282,  7527,  7242,
  7555,  7372,  5904,  3569,  1235,  -158,  -359,  -315,  -763, -1393,
  -1763, -1438,    58,  2217,  4180,  6305,  8738, 10244, 10505, 10608,
  10676, 10239,  9630,  8563,  6041,  2920,  1049,   279,  -545, -1321,
  -1454, -1291, -1304, -1273,  -880,  -532,  -776, -1046,  -476,   259,
  -4,  -482,   118,  1260,  1857,  2342,  3432,  4835,  5832,  6223,
  6537,  7194,  7684,  7428,  7021,  6818,  6010,  4264,  2839,  2358,
  2090,   944,  -652, -1491, -1085,  -722,  -594,   652
};

const int16_t wave2[257] = {
  662,  2669,  4281,  4921,  4187,  3449,  4710,  9132, 17294,
  26171, 31128, 32341, 32178, 31735, 31851, 32367, 32748, 32448, 30507,
  27918, 26072, 24015, 21743, 20690, 21355, 22669, 22394, 20138, 17846,
  16480, 16263, 17049, 18006, 19323, 20616, 20524, 19675, 19029, 18127,
  16903, 15662, 14580, 13172, 10730,  8462,  7971,  8026,  6549,  3863,
  780, -4488, -12022, -17487, -19968, -21990, -22479, -21344, -21612, -22846,
  -23047, -22191, -20345, -18266, -17108, -16643, -16064, -15056, -14538, -14962,
  -15050, -14996, -15798, -16960, -18773, -21230, -22798, -23219, -22673, -20947,
  -19125, -17427, -14949, -12087, -9281, -6624, -4618, -3220, -1960,  -106,
  2737,  5322,  7077,  9324, 12367, 15251, 17430, 18516, 18649, 18420,
  18041, 17370, 15711, 12915, 11096, 11329, 11361, 10521, 10484, 10828,
  10324,  9524,  9136,  9431, 10596, 12322, 14434, 16083, 16226, 15572,
  14578, 12540, 10388,  9158,  7546,  4240,  -221, -4000, -6795, -9440,
  -11612, -13149, -14975, -15930, -16550, -18901, -21543, -22512, -23125, -23153,
  -23103, -23998, -24430, -23938, -23642, -23181, -23469, -24454, -22910, -20135,
  -18893, -18270, -17102, -17043, -16576, -16003, -16012, -17273, -18374, -19757,
  -19710, -19541, -19124, -18689, -17719, -18112, -18043, -16751, -15111, -14190,
  -13266, -11476, -10702, -10577, -11887, -10374, -10311, -7235, -11508,  9886,
  28099, 21629, 22503, 19226, 18816, 17115, 17396, 16896, 17477, 17744,
  18146, 17412, 16409, 16383, 16428, 16083, 16746, 19439, 20771, 20995,
  20927, 21373, 20549, 18198, 14110, 10782,  6756,  1781, -2781, -6225,
  -9800, -12326, -14060, -15297, -16766, -18734, -19252, -17344, -15451, -14317,
  -12730, -10852, -8458, -6080, -4767, -3921, -2501, -1618, -1565, -1624,
  -1663, -2361, -2757, -1855,  -665,  -969, -2398, -3529, -4402, -5782,
  -6814, -6688, -6398, -6460, -6282, -5582, -4781, -4533, -4700, -4359,
  -3432, -2290, -1190,  -492,  -362,  -709,  -685,   662
};
//LCD TFT
///////////////////////////////////////////////////////////////////////////////////////////////////////////


#define TFT_CS        5
#define TFT_RST        3 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         4

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// color definitions
const uint16_t  Display_Color_Black        = 0x0000;
const uint16_t  Display_Color_Blue         = 0x001F;
const uint16_t  Display_Color_Red          = 0xF800;
const uint16_t  Display_Color_Green        = 0x07E0;
const uint16_t  Display_Color_Cyan         = 0x07FF;
const uint16_t  Display_Color_Magenta      = 0xF81F;
const uint16_t  Display_Color_Yellow       = 0xFFE0;
const uint16_t  Display_Color_White        = 0xFFFF;

uint16_t        Display_Text_Color         = Display_Color_Black;
uint16_t        Display_Backround_Color    = Display_Color_Green;

// declare size of working string buffers. ("1234567890") = 10
const size_t    MaxString               = 16;

char oldTimeString[MaxString]           = { 0 };

bool            isDisplayVisible        = false;

//LCD
//////////////////////////////////////////////////////////////////////////////////////////////////////////

LiquidCrystal lcd(11, 10, 24, 25, 26, 27);

//Waveform Text
/////////////////////////////////////////////////////////////////////////////////////////////////////////

struct WaveformOption {
  int type;
  const char* name;
};

WaveformOption waveforms[] = {
  {WAVEFORM_SAWTOOTH, "Sawtooth"},
  {WAVEFORM_SINE, "Sine"},
  {WAVEFORM_SQUARE, "Square"},
  {WAVEFORM_TRIANGLE, "Triangle"},
  {WAVEFORM_PULSE, "Pulse"}
};

int waveformIndex = 0;
const int waveformCount = sizeof(waveforms) / sizeof(waveforms[0]);

String currentWaveform = "Sawtooth"; // initial default

//Mixer Text
//////////////////////////////////////////////////////////////////////////////////////////////////////////

struct MixerOption {
  const char* label;
  float gains[4];  // mixer1 gain settings for inputs 0–3
};

MixerOption mixerOptions[] = {
  {"Control Osc",     {0.75, 0.0,  0.0,  0.0}},  // waveform1
  {"FM Oscillator",   {0.0,  0.75, 0.0,  0.0}},  // sine_fm1
  {"Sine Wave",       {0.0,  0.0,  0.75, 0.0}},  // sine1
  {"Pink Noise",      {0.0,  0.0,  0.0,  0.75}}  // pink1
};

int mixer1Index = 0;
const int mixer1Count = sizeof(mixerOptions) / sizeof(mixerOptions[0]);

//Button&Knob Setup
//////////////////////////////////////////////////////////////////////////////////////////////////////////

struct NoteButton {
  int pin;
  const char* name;
  float frequency;
  Bounce button;
};

Bounce button0 = Bounce(0, 15);
Bounce button1 = Bounce(1, 15);  
Bounce button2 = Bounce(2, 15);

int button0index = 0;
int button1index = 0;
int button2index = 0;

float knob1 = (float)analogRead(A1) / 1023.0;  //////////////Potentio Meter/////////////
float knob2 = (float)analogRead(A2) / 1023.0;
float knob3 = (float)analogRead(A3) / 1023.0;  

NoteButton noteButtons[] = {
  {38, "C", 261.63, Bounce(38, 15)},
  {37, "D", 293.66, Bounce(37, 15)},
  {36, "E", 329.63, Bounce(36, 15)},
  {35, "F", 349.23, Bounce(35, 15)},
  {34, "G", 392.00, Bounce(34, 15)},
  {33, "A", 440.00, Bounce(33, 15)}
};

// GUItool: end automatically generated code
void setup() {
  Serial.begin(9600);
  
  //tft display setup
  tft.initR(INITR_BLACKTAB); 
  tft.setRotation(1);
  tft.setFont();
  tft.fillScreen(Display_Backround_Color);
  tft.setTextColor(Display_Text_Color);
  tft.setTextSize(1);


  //lcd display setup
  lcd.begin(16, 2);


  //audio setup
  AudioMemory(400);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);
 

  //vco
  vcoA1.begin(vcoVol, 150, WAVEFORM_SAWTOOTH);
  vcoB1.begin(vcoVol, 150, WAVEFORM_SQUARE);
  vcoC1.begin(vcoVol, 150, WAVEFORM_ARBITRARY);
  sub1.begin(vcoVol , 150, WAVEFORM_TRIANGLE);


  //filter
  filter1.octaveControl(7);
  filterEnv1.sustain(0);


  //lfoA
  lfoA1.begin(WAVEFORM_SINE);
 



  //lfoB
 lfoB1.begin(0.5, 1, WAVEFORM_TRIANGLE);


  //delay
  dlyFiltL.frequency(4000);
  dlyFiltR.frequency(3000);

  dlyMixL.gain(0, 0.7);
  dlyMixL.gain(1, 0.7);
  
  dlyMixR.gain(0, 0.7);
  dlyMixR.gain(1, 0.7);


  dlyL.disable(1);
  dlyL.disable(2);
  dlyL.disable(3);
  dlyL.disable(4);
  dlyL.disable(5);
  dlyL.disable(6);
  dlyL.disable(7);

  dlyR.disable(1);
  dlyR.disable(2);
  dlyR.disable(3);
  dlyR.disable(4);
  dlyR.disable(5);
  dlyR.disable(6);
  dlyR.disable(7);

 
  //reverb
  reverb.roomsize(0.9);
  reverb.damping(0.8);
  

 //Disable LFO Connection
  patchCord2.disconnect();  //vcoA1
  patchCord3.disconnect();  //vcoB1 ///
  patchCord4.disconnect();  //vcoC1 /// PITCH LFO
  patchCord5.disconnect();  //sub

  patchCord6.disconnect();  //amplitude lfo
  patchCord7.disconnect(); //filter lfo

  for (int i = 0; i < 6; i++) {
  pinMode(noteButtons[i].pin, INPUT_PULLUP);
}
}


void loop() {
  lfoA1.amplitude(1);
  lfoA1.frequency(1);
  lfoB1.begin(0.8, 2, WAVEFORM_SINE);  

  vcoA1.begin(WAVEFORM_SINE);
  vcoB1.begin(WAVEFORM_SAWTOOTH);
  vcoC1.begin(WAVEFORM_SINE);
  sub1.begin(WAVEFORM_SINE);

  modMix1.gain(0,1);
  modMix1.gain(1,0);

  dc1.amplitude(0.1);

  voiceMix1.gain(0,1);
  voiceMix1.gain(1,0);
  voiceMix1.gain(2,0);
  voiceMix1.gain(3,0);

  filterEnv1.attack(10.5);
  filterEnv1.decay(35);
  filterEnv1.delay(0);
  filterEnv1.sustain(0.6);
  filterEnv1.release(300);

  filterMix1.gain(0,0);
  filterMix1.gain(1,0.5);

  filter1.frequency(2000);
  filter1.resonance(1);

  filterMode1.gain(0,0);
  filterMode1.gain(1,1);
  filterMode1.gain(2,0);

  mix1.gain(0,1);

  finalMix.gain(0,1);

  reverb.roomsize(0.2);
  reverb.damping(0.5);

  env1.attack(10.5);
  env1.delay(0);
  env1.decay(500);
  env1.sustain(0.1);

  dlyMixL.gain(0,1);
  dlyMixL.gain(1,0);

  dlyMixR.gain(0,1);
  dlyMixR.gain(1,0);

  fxL.gain(0,1);
  fxL.gain(1,0.8);
  fxL.gain(2,0.7);

  fxR.gain(0,1);
  fxR.gain(1,0.8);
  fxR.gain(2,0.7);

for (int i = 0; i < 6; i++) {
  noteButtons[i].button.update();
  if (noteButtons[i].button.fallingEdge()) {
    vcoA1.frequency(noteButtons[i].frequency);
    vcoB1.frequency(noteButtons[i].frequency);
    vcoC1.frequency(noteButtons[i].frequency);
    sub1.frequency(noteButtons[i].frequency);
    lfoAenv1.noteOn();
    env1.noteOn();

    Serial.print("Note: ");
    Serial.println(noteButtons[i].name);

  }
   if (noteButtons[i].button.risingEdge()) {
    lfoAenv1.noteOff();
    env1.noteOff();
   }
}
}