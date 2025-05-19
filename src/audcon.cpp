#include "audcon.h"
#include "global.h"
// Define all Audio objects
AudioSynthWaveform                  lfoA1;
AudioEffectEnvelope                 lfoAenv1;
AudioSynthWaveform                  lfoB1;
AudioMixer4                         modMix1;
AudioAnalyzeRMS                     lfoAread1;
AudioSynthWaveformModulated         vcoC1;
AudioSynthWaveformModulated         vcoB1;
AudioSynthWaveformModulated         vcoA1;
AudioSynthWaveformDc                dc1;
AudioSynthWaveformModulated         sub1;
AudioEffectEnvelope                 filterEnv1;
AudioMixer4                         voiceMix1;
AudioMixer4                         filterMix1;
AudioFilterStateVariable            filter1;
AudioMixer4                         filterMode1;
AudioEffectEnvelope                 env1;
AudioMixer4                         mix1;
AudioMixer4                         finalMix;
AudioFilterStateVariable            dlyFiltL;
AudioFilterStateVariable            dlyFiltR;
AudioEffectDelay                    dlyR;
AudioEffectDelay                    dlyL;
AudioMixer4                         dlyMixR;
AudioEffectFreeverb                 reverb;
AudioMixer4                         dlyMixL;
AudioMixer4                         fxL;
AudioMixer4                         fxR;
AudioOutputI2S                      i2s1;
AudioControlSGTL5000                sgtl5000_1;

AudioEffectGranular                 granular1;
AudioMixer4                         GranularMode1;

AudioPlaySdRaw                      playSdRaw;
AudioInputI2S                       i2s2;
AudioRecordQueue                    queue1;
AudioAnalyzePeak                    peak1;

// Define all patchCords
AudioConnection patchCord1(lfoA1, lfoAenv1);
AudioConnection patchCord2(lfoAenv1, 0, modMix1, 1);
AudioConnection patchCord3(lfoAenv1, 0, vcoB1, 0);
AudioConnection patchCord4(lfoAenv1, 0, vcoC1, 0);
AudioConnection patchCord5(lfoAenv1, 0, sub1, 0);
AudioConnection patchCord6(lfoAenv1, lfoAread1);
AudioConnection patchCord7(lfoAenv1, 0, filterMix1, 0);
AudioConnection patchCord8(lfoB1, 0, vcoA1, 1);
AudioConnection patchCord9(lfoB1, 0, vcoB1, 1);
AudioConnection patchCord10(modMix1, 0, vcoA1, 0);
AudioConnection patchCord11(vcoC1, 0, voiceMix1, 2);
AudioConnection patchCord12(vcoB1, 0, voiceMix1, 1);
AudioConnection patchCord13(vcoB1, 0, modMix1, 0);
AudioConnection patchCord14(vcoA1, 0, voiceMix1, 0);
AudioConnection patchCord15(dc1, filterEnv1);

AudioConnection patchCord17(filterEnv1, 0, filterMix1, 1);
AudioConnection patchCord18(voiceMix1, 0, filter1, 0);
AudioConnection patchCord19(filterMix1, 0, filter1, 1);
AudioConnection patchCord20(filter1, 0, filterMode1, 0);
AudioConnection patchCord21(filter1, 1, filterMode1, 1);
AudioConnection patchCord22(filterMode1, env1);
AudioConnection patchCord23(env1, 0, mix1, 0);
//AudioConnection patchCord24(mix1, 0, finalMix, 0);
AudioConnection patchCord25(finalMix, 0, fxL, 0);
AudioConnection patchCord26(finalMix, reverb);
AudioConnection patchCord27(finalMix, 0, fxR, 0);
AudioConnection patchCord28(finalMix, 0, dlyMixL, 0);
AudioConnection patchCord29(finalMix, 0, dlyMixR, 0);
AudioConnection patchCord30(dlyFiltL, 0, dlyMixL, 1);
AudioConnection patchCord31(dlyFiltR, 0, dlyMixR, 1);
AudioConnection patchCord32(dlyR, 0, dlyFiltR, 0);
AudioConnection patchCord33(dlyL, 0, dlyFiltL, 0);
AudioConnection patchCord34(dlyMixR, 0, fxR, 2);
AudioConnection patchCord35(dlyMixR, dlyR);
AudioConnection patchCord36(reverb, 0, fxL, 1);
AudioConnection patchCord37(reverb, 0, fxR, 1);
AudioConnection patchCord38(dlyMixL, 0, fxL, 2);
AudioConnection patchCord39(dlyMixL, dlyL);
AudioConnection patchCord40(fxL, 0, i2s1, 0);
AudioConnection patchCord41(fxR, 0, i2s1, 1);
AudioConnection patchCordX(GranularMode1, 0, finalMix, 0);


AudioConnection patchCord42(voiceMix1, 0, granular1, 0);
AudioConnection patchCord43(mix1, 0, GranularMode1, 0);
AudioConnection patchCord44(granular1, 0, GranularMode1, 1);
AudioConnection patchCord45(filter1, 2, filterMode1, 2);
