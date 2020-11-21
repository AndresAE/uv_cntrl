/* 
author: Andres Sandoval
date: 7/29/2020

code to command uav using pilot control (transmitter + receiver) and feedback control
using an mpu6050. Requires IC2dev, MPU6050, Wire, and Servo libraries.
 */

#include <MPU6050.h>

// sensor offsets
float accel_x, gyro_x;
float accel_y, gyro_y;
float accel_z, gyro_z;
const float accel_correction = 16384;
const float gyro_correction = 131;
float phi, theta, p, q, r, a_x, a_y, a_z;

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

#define OUTPUT_READABLE_ACCELGYRO

void setup() {
  Serial.begin(9600);
  accelgyro.initialize();
  accelgyro.CalibrateGyro();
  accelgyro.CalibrateAccel();
  accel_x = accelgyro.getXAccelOffset();
  accel_y = accelgyro.getYAccelOffset();
  accel_z = accelgyro.getZAccelOffset();
  gyro_x = accelgyro.getXGyroOffset();
  gyro_y = accelgyro.getYGyroOffset();
  gyro_z = accelgyro.getZGyroOffset();
  accelgyro.setXAccelOffset(accel_x);
  accelgyro.setYAccelOffset(accel_y);
  accelgyro.setZAccelOffset(accel_z);
  accelgyro.setXGyroOffset(gyro_x);
  accelgyro.setYGyroOffset(gyro_y);
  accelgyro.setZGyroOffset(gyro_z);
}
void loop() {

  // read raw accel/gyro measurements from device
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // dynamics
  a_x = float(ax) / accel_correction;
  a_y = float(ay) / accel_correction;
  a_z = float(az) / accel_correction;
  p = float(gx) / gyro_correction;
  q = float(gy) / gyro_correction;
  r = float(gz) / gyro_correction;
  phi = (atan(a_y / sqrt(pow(a_x, 2) + pow(a_z, 2))) * 180 / PI);
  theta = (atan(-1 * a_x / sqrt(pow(a_x, 2) + pow(a_z, 2))) * 180 / PI);

  // command servos
  Serial.println(phi);
}
