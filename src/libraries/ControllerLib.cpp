/*
  ControllerLib.h - Controller Library for Control Systems - implementation
  Copyright (c) 2021 Andres Sandoval.  All right reserved.
*/

// include this library's description file
#include "ControllerLib.h"

// Public Methods //////////////////////////////////////////////////////////////
float ControllerLib::pid(float setpoint, float process_variable, float d_t, float k_p, float k_i, float k_d)
{

	float error = setpoint - process_variable;
	float d_error_dt = error / d_t;
	float int_error = error * d_t;
	float proportional = k_p * error;
	float integral = k_i * d_error_dt;
	float derivative = k_d * int_error;
	return proportional + integral + derivative;

}

float ControllerLib::pi(float setpoint, float process_variable, float d_t, float k_p, float k_i)
{
	float error = setpoint - process_variable;
	float int_error = error * d_t;
	float proportional = k_p * error;
	float integral = k_i * d_error_dt;
	return proportional + integral;
}

float ControllerLib::pd(float setpoint, float process_variable, float d_t, float k_p, float k_d)
{
	float error = setpoint - process_variable;
	float d_error_dt = error / d_t;
	float proportional = k_p * error;
	float derivative = k_d * int_error;
	return proportional + derivative;
}