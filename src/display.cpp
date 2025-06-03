#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "Arduino.h"
#include "global.h"
#include "display.h"
#include "Global.h"
#include "ui.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire2, OLED_RESET);

// Sine wave icon


// Corrected type
MenuState selectedMenu = MENU_VOLUME;

const char* menuLabels[MENU_COUNT] = {
  "Volume",
  "Filter",
  "Osc Mix",
  "Waveform"
};



unsigned long lastDisplayUpdate = 0;
const unsigned long displayRefreshInterval = 100;  // in milliseconds

void setupOLED() {
  Wire2.begin();
  if (!display.begin(0x3C, true)) {
    Serial.println(F("SH1106 allocation failed"));
    return;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print("SH1106 Ready");
  display.display();
  delay(1000);
}

void drawWaveformIcon(uint8_t shape, int x, int y) {
   const unsigned char* icon = nullptr;

  switch (shape) {
    case 0: icon = sineIcon; break;
    case 1: icon = sawIcon; break;
    case 2: icon = triangleIcon; break;
    case 3: icon = squareIcon; break;
    default: return;
  }
  display.drawBitmap(x, y , icon, 32, 32, SH110X_WHITE);
}



void drawMenuScreen() {
  if (millis() - lastDisplayUpdate < displayRefreshInterval) return;
  lastDisplayUpdate = millis();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);

  switch (currentMode) {
    case VOLUME_MODE: {
      int barLength = (int)(params.volume.mainVol * 118);
      display.setCursor(0, 0);
      display.print("Volume: ");
      display.print(params.volume.mainVol*100, 0);
      display.fillRect(0, 10, barLength, 10, SH110X_WHITE);
      break;
    }
    case FILTER_MODE: {
      display.setCursor(0, 0);
      display.print("Filter ");
      if (!params.filter.filterEdit) {
        display.print("Cutoff: ");
        display.println(params.filter.cutoff, 0);
        display.print("Reso: ");
        display.println(params.filter.reso, 2);
        display.print("Oct: ");
        display.println(params.filter.octave, 1);
      } else {
        display.print("Env A: ");
        display.println(params.filter.filtAtt, 0);
        display.print("Env D: ");
        display.println(params.filter.filtDec, 0);
        display.print("Env S: ");
        display.println(params.filter.filtSus, 2);
        display.print("Env R: ");
        display.println(params.filter.filtRel, 0);
      }
      break;
    }
    case WAVEFORM_MODE: {
      display.setCursor(0, 0);
      display.print("Waveform");

      // Draw each waveform icon with label
      drawWaveformIcon(params.waveform.shapeA_btn, 0, 10);
      drawWaveformIcon(params.waveform.shapeB_btn, 48, 10);
      drawWaveformIcon(params.waveform.shapeC_btn, 96, 10);

      display.setCursor(8, 44);
      display.print("A");

      display.setCursor(56, 44);
      display.print("B");

      display.setCursor(104, 44);
      display.print("C");
      break;
      }

    case LFO_MODE: {
      display.setCursor(0, 0);
      if (params.lfo.lfoAEdit) {
        display.print("LFO A: Attack ");
        display.println(params.lfo.lfoAatk, 0);
        display.print("Decay ");
        display.println(params.lfo.lfoAdec, 0);
        display.print("Sustain ");
        display.println(params.lfo.lfoAsus, 2);
        display.print("Release ");
        display.println(params.lfo.lfoArel, 0);
      } else {
        display.print("Freq: ");
        display.println(params.lfo.lfoAfreq, 2);
        display.print("Amp: ");
        display.println(params.lfo.lfoAamp, 2);
      }
      break;
    }
    case ENVELOPE_MODE: {
      display.setCursor(0, 0);
      display.print("Env A: ");
      display.println(params.env.envAtk, 0);
      display.print("Env D: ");
      display.println(params.env.envDec, 0);
      display.print("Env S: ");
      display.println(params.env.envSus, 2);
      display.print("Env R: ");
      display.println(params.env.envRel, 0);
      break;
    }
    case EFFECTS_MODE: {
      display.setCursor(0, 0);
      display.print("Dly Amt: ");
      display.println(params.dly.dlyMix, 2);
      display.print("Dly Time: ");
      display.println(params.dly.dlyTime, 0);
      display.print("Rev Size: ");
      display.println(params.reverb.size, 2);
      display.print("Damp: ");
      display.println(params.reverb.damping, 2);
      break;
    }
    case SAMPLING_MODE: {
      display.setCursor(0, 0);
      display.print("Mic Level: ");
      display.println(params.sampling.param1, 2);
      break;
    }
  }

  display.display();
}


void nextMenu() {
  selectedMenu = static_cast<MenuState>((selectedMenu + 1) % MENU_COUNT);
}

void prevMenu() {
  selectedMenu = static_cast<MenuState>((selectedMenu - 1 + MENU_COUNT) % MENU_COUNT);
}
