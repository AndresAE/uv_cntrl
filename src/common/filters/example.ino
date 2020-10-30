#include "Filters.h"
#include <math.h>
Filters Filters;

float y [] = {0, 0}; float y_filtered = 0;
float x = 0;
float lp_frequency = 0.5;
float t0 = millis();
float t, t1 = 0, t2, dt;
float pi = 3.14;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  t2 = millis();
  t = t2 - t0;
  dt = t2 - t1;
  y[1] = sin (t * 3 * pi / 1000);
  y_filtered = Filters.low_pass(x, y, lp_frequency, dt / 1000);
  Serial.println(y[1]);
  Serial.println(y_filtered);
  y[0] = y[1];
  t1 = t2;
}
