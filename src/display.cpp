// display.cpp
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "Arduino.h"
#include "global.h"
#include "display.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire2, OLED_RESET);

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
  display.print("SH1106 OK");
  display.display();
}

void drawVolumeBar(float volume) {
  if (millis() - lastDisplayUpdate < displayRefreshInterval) return;
  lastDisplayUpdate = millis();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print("Volume:");
  display.setCursor(60, 0);
  display.print((int)(volume * 100));
  display.print("%");

  display.drawRect(0, 20, 120, 10, SH110X_WHITE);
  int barLength = (int)(volume * 118);
  display.fillRect(1, 21, barLength, 8, SH110X_WHITE);

  display.display();
}

void displayErrorMessage(const char* message) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.print("ERROR:");
  display.setCursor(0, 10);
  display.print(message);
  display.display();
}
