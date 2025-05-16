#include "ui.h"
#include "Bounce.h"

Knob knobs[5] = {
  {A3, 0.0, 0.0},
  {A2, 0.0, 0.0},
  {A1, 0.0, 0.0},
  {A17, 0.0, 0.0},
  {A16, 0.0, 0.0}
};

void setupUI() {
  for (int i = 0; i < 5; i++) {
    pinMode(knobs[i].pin, INPUT);
  }
}

void updateKnobs() {
  for (int i = 0; i < 5; i++) {
    int raw = analogRead(knobs[i].pin);
    knobs[i].value = raw / 1023.0f;

    if (abs(knobs[i].value - knobs[i].lastValue) > 0.05f) {
      Serial.print("Knob ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(knobs[i].value, 2);
      knobs[i].lastValue = knobs[i].value;
    }
  }
}

Bounce button0 = Bounce(1, 15);
Bounce button1 = Bounce(2, 15);
Bounce button2 = Bounce(9, 15);


//volume



//lfo

//effect
