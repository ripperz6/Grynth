// display.cpp
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>  // Use this for SH1106 driver
#include "Arduino.h"
#include "global.h"
#include "display.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1

// SH1106 uses a different class from Adafruit_SH110X
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire2, OLED_RESET); // Using Wire2 for I2C on Teensy 24/25

void setupOLED() {
  Wire2.begin();
    Wire2.setClock(400000);  // Optional: boost I2C speed for stability
  if (!display.begin(0x3C, true)) {  // 0x3C is typical I2C address for SH1106
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
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print("Volume:");
  display.setCursor(60, 0);
  display.print((int)(volume * 100));
  display.print("%");

  // Draw volume bar background
  display.drawRect(0, 20, 120, 10, SH110X_WHITE);

  // Fill based on volume
  int barLength = (int)(volume * 118);
  display.fillRect(1, 21, barLength, 8, SH110X_WHITE);

  display.display();
  
}
