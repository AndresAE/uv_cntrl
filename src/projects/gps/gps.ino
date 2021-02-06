//Connect with pin 18 and 19
#include <TinyGPS.h>
//long   lat,lon; // create variable for latitude and longitude object
float lat, lon, v, hdg, h;
TinyGPS gps; // create gps object
# include <SD.h>
# include <SPI.h>

File file;
float t0;

void setup() {
  Serial.begin(9600); // connect serial
  Serial.println("The GPS Received Signal:");

  /*Serial.println("initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initializing SD card failed...");
    return;
  }
  Serial.println("initializing SD success!...");

  Serial.println("creating file...");
  file = SD.open("testlog.txt", FILE_WRITE);
  file.close();
  Serial.println("File Created!...");*/

}

void loop() {
  while (Serial.available()) { // check for gps data
    if (gps.encode(Serial.read())) // encode gps data
    {
      gps.f_get_position(&lat, &lon); // get latitude and longitude
      v = gps.f_speed_knots();  // knots
      hdg = gps.f_course();  // degree
      h = gps.f_altitude();  // meters

      Serial.print("Latitude: ");
      Serial.print(lat, 6);
      Serial.print(", Longitude: ");
      Serial.print(lon, 6);
      Serial.print(", speed: ");
      Serial.print(v, 6);
      Serial.print(", course: ");
      Serial.print(hdg, 6);
      Serial.print(", alt: ");
      Serial.println(h, 6);

      /*File file = SD.open("testlog.txt", FILE_WRITE);
      t0 = millis();
      file.print("time, ");
      file.print(t0 / 1000);
      file.print(", longitude, ");
      file.print(float(lon), 6);
      file.print(", latitude, ");
      file.print(float(lat), 6);
      file.print(", speed, ");
      file.print(float(v), 6);
      file.print(", course, ");
      file.print(float(hdg), 6);
      file.print(", alt, ");
      file.println(float(h), 6);
      file.close();*/
    }
  }
}
