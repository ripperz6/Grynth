#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "Global.h"
#include "ui.h"
// Access to menu state already available via global.h
enum MenuState {
  MENU_VOLUME,
  MENU_FILTER,
  MENU_OSC_MIX,
  MENU_WAVEFORM,
  MENU_COUNT
};

void setupOLED();
void drawMenuScreen();
void nextMenu();
void prevMenu();

#endif
