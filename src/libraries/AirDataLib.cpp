/*
  AirDataLib.h - Air Data Library for Control Systems - implementation
  Copyright (c) 2021 Andres Sandoval.  All right reserved.
*/

// include this library's description file
#include "AirDataLib.h"

// Public Methods //////////////////////////////////////////////////////////////
float AirDataLib::pid(float setpoint, float process_variable, float d_t, float k_p, float k_i, float k_d)
{

	float error = setpoint - process_variable;
	float d_error_dt = error / d_t;
	float int_error = error * d_t;
	float proportional = k_p * error;
	float integral = k_i * d_error_dt;
	float derivative = k_d * int_error;
	return proportional + integral + derivative;

}