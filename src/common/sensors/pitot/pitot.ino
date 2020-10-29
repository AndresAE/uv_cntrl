/*
  Pitot.ino - Pitot Example - example with a pitot tube and MPXV7002DP pressure differential sensor
  Copyright (c) 2020 Andres Sandoval.  All rights reserved.
*/

#include "Pitot.h"

float veloc = 0.0;
int offset = 0;
int pin = A1;

Pitot pitot( pin );

// setup and calculate offset
void setup() {
  Serial.begin(9600);
  offset = pitot.offset();
}

void loop() {
  veloc = pitot.indicated_airspeed( offset );
  Serial.println(veloc); // print velocity
  delay(10); // delay for stability
}
