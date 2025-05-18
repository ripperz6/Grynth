#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "Arduino.h"
#include "global.h"
#include "display.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire2, OLED_RESET);

// Corrected type
MenuState selectedMenu = MENU_VOLUME;

const char* menuLabels[MENU_COUNT] = {
  "Volume",
  "Filter",
  "Osc Mix",
  "Waveform"
};

const unsigned char logo128x32[] = {
  0x00, 0x00, 0x00, 0x00  // placeholder
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

void drawMenuScreen() {
  if (millis() - lastDisplayUpdate < displayRefreshInterval) return;
  lastDisplayUpdate = millis();

  display.clearDisplay();

  display.drawBitmap(100, 0, logo128x32, 28, 28, SH110X_WHITE);

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);

  for (int i = 0; i < MENU_COUNT; i++) {
    int y = i * 10;
    if (i == selectedMenu) {
      display.fillRect(0, y, 100, 10, SH110X_WHITE);
      display.setTextColor(SH110X_BLACK);
    } else {
      display.setTextColor(SH110X_WHITE);
    }
    display.setCursor(2, y);
    display.print(menuLabels[i]);
  }

  display.display();
}

void nextMenu() {
  selectedMenu = static_cast<MenuState>((selectedMenu + 1) % MENU_COUNT);
}

void prevMenu() {
  selectedMenu = static_cast<MenuState>((selectedMenu - 1 + MENU_COUNT) % MENU_COUNT);
}
