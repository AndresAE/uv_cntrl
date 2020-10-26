/*
 RC PulseIn Serial Read out
 By: Nick Poole
 SparkFun Electronics
 Date: 5
 License: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute. Let me know if you make hugely, awesome, great changes.
 */
int ch3;
#include <Servo.h>
Servo myservo;
float pos;

void setup() {
  pinMode(7, INPUT);
  Serial.begin(9600); // Pour a bowl of Serial
  myservo.attach(9);
}

void loop() {
  ch3 = pulseIn(7, HIGH, 25000);

  Serial.print(ch3);
  Serial.print("Channel 3:");
  Serial.println((float(ch3)-1078-827/2)/(827/2)*90+90); // center at 0
  pos = (float(ch3) - 978 - 1027 / 2) / 1027 * 180 + 90;
  myservo.write(pos); 
  delay(10); // I put this here just to make the terminal 
              // window happier
}
