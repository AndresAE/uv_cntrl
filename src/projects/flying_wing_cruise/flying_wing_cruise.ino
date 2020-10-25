/* 
author: Andres Sandoval
date: 7/29/2020

code to command uav using pilot control (transmitter + receiver) and feedback control
using an mpu6050. Requires IC2dev, MPU6050, Wire, and Servo libraries.
 */

#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>
#include <Servo.h>
# include <SD.h>
# include <SPI.h>

const float sas_on = 1;  // augmentation on [1 or 0]

// FCS gains
const float k_p = 0.5;  // [deg servo/deg]
const float k_q = 0.25;  // [deg servo/deg]
const float k_fcs_roll = 1;  // [deg servo/deg input]
const float k_fcs_pitch = -1;  // [deg servo/deg input]

// filter properties
const float hp_frequency_roll = 0.05;  // [rad/s]
const float hp_frequency_pitch = 0.05;  // [rad/s]
const float lp_frequency_pitch = 8;  // [rad/s]
float fcs_limits[] = {0, 180};  // [deg]

// sensor offsets
const float accel_x = -1329;
const float accel_y = 2498;
const float accel_z = 2094;
const float accel_correction = 16384;
const float gyro_correction = 131;
const float transmitter_min = 978;
const float transmitter_range = 1027;

Servo elevon_servo_1;
Servo elevon_servo_2;
File file;

// initialize variables
float alpha_hp_roll;
float alpha_hp_pitch, alpha_lp_pitch;

int ch2;
int ch3;

float t0, dt;

float a_x, d_roll, d_a_l,d_a_r;
float a_y, theta, d_pitch, d_e;
float a_z;
float d_elevon_1, d_elevon_2;

double phi[] = {0, 0};
double p[] = {0, 0};
double phi_filtered[] = {0, 0};
double q[] = {0, 0};
double q_filtered[] = {0, 0};
double r[] = {0, 0};
double r_filtered[] = {0, 0};
double d_elevon_1_filtered[] = {0, 0};
double d_elevon_2_filtered[] = {0, 0};
const int n = 1;

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

#define OUTPUT_READABLE_ACCELGYRO

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);

  Serial.println("initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initializing SD card failed...");
    return;
  }
  Serial.println("initializing SD success!...");

  Serial.println("creating file...");
  file = SD.open("testlog.txt", FILE_WRITE);
  file.close();
  Serial.println("File Created!...");

  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif 
  accelgyro.initialize();
  accelgyro.setXAccelOffset(accel_x);
  accelgyro.setYAccelOffset(accel_y);
  accelgyro.setZAccelOffset(accel_z);

  elevon_servo_1.attach(2);
  elevon_servo_2.attach(3);
}
void loop() {
  t0 = millis();

  // read receiver
  ch2 = pulseIn(4, HIGH, 35000);
  ch3 = pulseIn(5, HIGH, 35000);
  d_roll = (float(ch2) - transmitter_min - transmitter_range / 2) / transmitter_range * 180 * k_fcs_roll;
  d_pitch = (float(ch3) - transmitter_min - transmitter_range / 2) / transmitter_range * 180 * k_fcs_pitch;

  // read raw accel/gyro measurements from device
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // dynamics
  a_x = float(ax) / accel_correction;
  a_y = float(ay) / accel_correction;
  a_z = float(az) / accel_correction;
  p[1] = float(gx) / gyro_correction;
  q[1] = float(gy) / gyro_correction;
  r[1] = float(gz) / gyro_correction;
  phi[1] = (atan(a_y / sqrt(pow(a_x, 2) + pow(a_z, 2))) * 180 / PI);
  theta = (atan(-1 * a_x / sqrt(pow(a_x, 2) + pow(a_z, 2))) * 180 / PI);

  // data filters
  dt = (millis() - t0) / 1000;
  // roll high pass
  alpha_hp_roll = (1 / hp_frequency_roll) / ((1 / hp_frequency_roll) + dt);
  phi_filtered[n] = alpha_hp_roll * (phi_filtered[n - 1] + phi[n] - phi[n - 1]);
  phi[n - 1] = phi[n];
  phi_filtered[n - 1] = phi_filtered[n];

  // pitch high pass
  alpha_hp_pitch = (1 / hp_frequency_pitch) / ((1 / hp_frequency_pitch) + dt);
  q_filtered[n] = alpha_hp_pitch * (q_filtered[n - 1] + q[n] - q[n - 1]);
  q[n - 1] = q[n];
  q_filtered[n - 1] = q_filtered[n];

  // sum commands
  d_a_l = 0 + sas_on*(k_p * phi_filtered[n]);
  d_a_r = 0 + sas_on*(k_p * phi_filtered[n]); // anti-symmetric
  d_e = sas_on*(k_q * q_filtered[n]);
  d_elevon_1 = d_a_l + d_e + 90;
  d_elevon_2 = d_a_r - d_e + 90;

  // command filters
  dt = (millis() - t0) / 1000;

  // low pass
  alpha_lp_pitch = dt / ((1 / lp_frequency_pitch) + dt);
  d_elevon_1_filtered[n] = alpha_lp_pitch * d_elevon_1 + (1 - alpha_lp_pitch) * d_elevon_1_filtered[n-1];
  d_elevon_1_filtered[n-1] = d_elevon_1_filtered[n];
  d_elevon_2_filtered[n] = alpha_lp_pitch * d_elevon_2 + (1 - alpha_lp_pitch) * d_elevon_2_filtered[n-1];
  d_elevon_2_filtered[n-1] = d_elevon_2_filtered[n];

  // limits
  if (d_elevon_1_filtered[n]<fcs_limits[0]) {d_elevon_1_filtered[n]=fcs_limits[0];}
  if (d_elevon_2_filtered[n]<fcs_limits[0]) {d_elevon_2_filtered[n]=fcs_limits[0];}
  if (d_elevon_1_filtered[n]>fcs_limits[1]) {d_elevon_1_filtered[n]=fcs_limits[1];}
  if (d_elevon_2_filtered[n]>fcs_limits[1]) {d_elevon_2_filtered[n]=fcs_limits[1];}

  // command servos
  Serial.print(p[1]);
  Serial.print(" ,");
  Serial.println(q[1]);
  elevon_servo_1.write(d_elevon_1_filtered[n]);
  elevon_servo_2.write(d_elevon_2_filtered[n]);

  // report
  File file = SD.open("testlog.txt", FILE_WRITE);
  t0 = millis();
  file.print("time, ");
  file.print(t0 / 1000);
  file.print(", pitch_cmd, ");
  file.print(d_pitch, 6);
  file.print(", roll_cmd, ");
  file.print(d_roll, 6);
  file.print(", theta, ");
  file.print(theta, 6);
  file.print(", phi, ");
  file.print(phi[1], 6);
  file.print(", p, ");
  file.print(p[1], 6);
  file.print(", q, ");
  file.print(q[1], 6);
  file.print(", r, ");
  file.println(r[1], 6);
  file.close();
}
