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

const float sas_on = 1;  // augmentation on [1 or 0]

// FCS gains
const float k_p = 0.5;  // [deg servo/deg]
const float k_q = 0.25;  // [deg servo/deg]
const float k_r = 0.25;  // [deg servo/deg]

// filter properties
const float hp_frequency_roll = 0.05;  // [rad/s]
const float lp_frequency_roll = 60;  // [rad/s]
const float hp_frequency_pitch = 0.05;  // [rad/s]
const float lp_frequency_pitch = 60;  // [rad/s]
const float hp_frequency_yaw = 0.05;  // [rad/s]
const float lp_frequency_yaw = 60;  // [rad/s]
float roll_limits[] = {0, 180};  // [deg]
float pitch_limits[] = {0, 180};  // [deg]
float yaw_limits[] = {0, 180};  // [deg]

// sensor offsets
const float accel_x = -1329;
const float accel_y = 2498;
const float accel_z = 2094;
const float accel_correction = 16384;
const float gyro_correction = 131;
const float transmitter_min = 978;
const float transmitter_range = 1027;

Servo roll_servo_1;
Servo roll_servo_2;
Servo pitch_servo;
Servo yaw_servo;

// initialize variables
float alpha_hp_roll, alpha_lp_roll;
float alpha_hp_pitch, alpha_lp_pitch;
float alpha_hp_yaw, alpha_lp_yaw;

float t0, dt;

float d_a, d_a_l, d_a_r, a_x;
float d_e, a_y, theta;
float d_r, a_z;
float d_f;

double phi[] = {0, 0};
double p[] = {0, 0};
double phi_filtered[] = {0, 0};
double q[] = {0, 0};
double q_filtered[] = {0, 0};
double r[] = {0, 0};
double r_filtered[] = {0, 0};
double dal_filtered[] = {0, 0};
double dar_filtered[] = {0, 0};
double de_filtered[] = {0, 0};
double dr_filtered[] = {0, 0};
const int n = 1;

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

#define OUTPUT_READABLE_ACCELGYRO

void setup() {
  Serial.begin(9600);

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

  roll_servo_1.attach(2);
  roll_servo_2.attach(3);
  pitch_servo.attach(4);
  yaw_servo.attach(5);
}
void loop() {
  t0 = millis();

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

  // yaw high pass
  alpha_hp_yaw = (1 / hp_frequency_yaw) / ((1 / hp_frequency_yaw) + dt);
  r_filtered[n] = alpha_hp_yaw * (r_filtered[n - 1] + r[n] - r[n - 1]);
  r[n - 1] = r[n];
  r_filtered[n - 1] = r_filtered[n];

  // sum commands
  d_a_l = sas_on*(k_p * phi_filtered[n])+90;
  d_a_r = sas_on*(k_p * phi_filtered[n]); // anti-symmetric
  d_e = sas_on*(k_q * q_filtered[n]);
  d_r = sas_on*(k_r * r_filtered[n]);
  

  // command filters
  dt = (millis() - t0) / 1000;
  // roll low pass
  alpha_lp_roll = dt / ((1 / lp_frequency_roll) + dt);
  dal_filtered[n] = alpha_lp_roll * d_a_l + (1 - alpha_lp_roll) * dal_filtered[n-1];
  dal_filtered[n-1] = dal_filtered[n];
  dar_filtered[n] = alpha_lp_roll * d_a_r + (1 - alpha_lp_roll) * dar_filtered[n-1];
  dar_filtered[n-1] = dar_filtered[n];

  // pitch high pass
  alpha_lp_pitch = dt / ((1 / lp_frequency_pitch) + dt);
  de_filtered[n] = alpha_lp_pitch * d_e + (1 - alpha_lp_pitch) * de_filtered[n-1];
  de_filtered[n-1] = de_filtered[n];

  // yaw high pass
  alpha_lp_yaw = dt / ((1 / lp_frequency_yaw) + dt);
  dr_filtered[n] = alpha_lp_yaw * d_r + (1 - alpha_lp_yaw) * dr_filtered[n-1];
  dr_filtered[n-1] = dr_filtered[n];

  // limits
  if (dal_filtered[n]<roll_limits[0]) {dal_filtered[n]=roll_limits[0];}
  if (dar_filtered[n]<roll_limits[0]) {dar_filtered[n]=roll_limits[0];}
  if (de_filtered[n]<pitch_limits[0]) {de_filtered[n]=pitch_limits[0];}
  if (dr_filtered[n]<yaw_limits[0]) {dr_filtered[n]=yaw_limits[0];}
  if (dal_filtered[n]>roll_limits[1]) {dal_filtered[n]=roll_limits[1];}
  if (dar_filtered[n]>roll_limits[1]) {dar_filtered[n]=roll_limits[1];}
  if (de_filtered[n]>pitch_limits[1]) {de_filtered[n]=pitch_limits[1];}
  if (dr_filtered[n]>yaw_limits[1]) {dr_filtered[n]=yaw_limits[1];}

  // command servos
  Serial.println(dal_filtered[n]);
  roll_servo_1.write(dal_filtered[n]);
  roll_servo_2.write(dar_filtered[n]);
  pitch_servo.write(de_filtered[n]);
  yaw_servo.write(dr_filtered[n]);
}
