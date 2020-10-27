/*
  Filters.h - Filter Library for Control Systems - implementation
  Copyright (c) 2020 Andres Sandoval.  All right reserved.
*/

// include this library's description file
#include "Filters.h"
int n = 1;

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Filters::Filters()
{
	// initialize this instance's variables
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

float Filters::derivative(double y, float dt)
{
	// eventhough this function is public, it can access
	// and modify this library's private variables
	float dydt = (y[n] - y[n - 1]) / dt;
	return dydt;

}

float Filters::high_pass(double x, double y, float hp_frequency, float dt)
{
	// eventhough this function is public, it can access
	float alpha = (1 / hp_frequency) / ((1 / hp_frequency) + dt);
	float y_filtered = alpha * (y[n - 1] + x[n] - x[n - 1]);
	return y_filtered;

}

float Filters::integral(double y, float dt, float c)
{
	// eventhough this function is public, it can access
	// and modify this library's private variables
	float inty = (y[n] - y[n - 1]) * dt / 2 + c;
	return inty;

}

float Filters::limit(float y, float limits)
{
	// eventhough this function is public, it can access
	// and modify this library's private variables
	if (y < limits[n - 1]) { y = limits[n - 1]; }
	if (y > limits[n]) { y = limits[n]; }
	return y;

}

float Filters::low_pass(float x, double y, float hp_frequency, float dt)
{
	// eventhough this function is public, it can access
	// and modify this library's private variables
	float alpha = dt / ((1 / lp_frequency) + dt);
	float y_filtered = alpha * x + (1 - alpha) * y[n - 1];
	return y_filtered;

}