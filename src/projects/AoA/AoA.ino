/*
  Pitot.ino - Pitot Example - example with a pitot tube and MPXV7002DP pressure differential sensor
  Copyright (c) 2020 Andres Sandoval.  All rights reserved.
*/

float out;
int pin = A1;

// setup and calculate offset
void setup() {
  Serial.begin(9600);
}

void loop() {
  out = analogRead(pin);
  Serial.println(out); // print velocity
  delay(10); // delay for stability
}
