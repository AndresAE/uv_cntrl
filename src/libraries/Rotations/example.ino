#include "Rotations.h"
Rotations rot;

float a = 5 / 57.3; 
float b = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float s = rot.b2w(a, b);
}
