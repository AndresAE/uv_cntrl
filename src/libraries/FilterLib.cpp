/*
  FilterLib.cpp - Filter Library for Control Systems - implementation
  Copyright (c) 2021 Andres Sandoval.  All right reserved.
*/

// include this library's description file
#include "FilterLib.h"

// Public Methods //////////////////////////////////////////////////////////////

float FilterLib::low_pass_filter(float y_0, float y_1, float d_t, float w_c) {
	// pass signals below w_c (rad/s) first order

	float alpha = d_t / ((1 / w_c) + d_t);
	float y = y_0 + alpha * (y_1 - y_0);
	return y;

}

float FilterLib::high_pass_filter(float y_0, float x_0, float x_1, float d_t, float w_c) {
	// pass signals above w_c (rad/s) first order

	float alpha = (1 / w_c) / ((1 / w_c) + d_t);
	float y = alpha * (y_0 + x_1 - x_0);
	return y;

}

float FilterLib::position_saturation(float y, float y_min, float y_max) {
	// limit signals between y_min and y_max

	float y_out = y;
	if (y > y_max) {
		y_out = y_max;
	}
	else if (y < y_min) {
		y_out = y_min;
	}
	return y_out;

}

float FilterLib::rate_saturation(float y_0, float y_1, float d_t, float y_dt_min, float y_dt_max) {
	// limit signal of time derivative between y_dt_min and y_dt_max

	float y_dt = (y_1 - y_0) / d_t;
	float y_dt_out = y_dt;
	if (y_dt > y_dt_max) {
		y_dt_out = y_dt_max;
	}
	else if (y_dt < y_dt_min) {
		y_dt_out = y_dt_min;
	}

	return y_0 + y_dt_out * d_t;

}