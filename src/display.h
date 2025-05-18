#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "Global.h"
// Access to menu state already available via global.h


void setupOLED();
void drawMenuScreen();
void nextMenu();
void prevMenu();

#endif
