/*
  SourceLib.cpp - Source Library for Control Systems - implementation
  Copyright (c) 2021 Andres Sandoval.  All right reserved.
*/

// include this library's description file
#include "SourceLib.h"

// Public Methods //////////////////////////////////////////////////////////////

float SourceLib::chirp(float t, float amp, float f_0, float f_1, float t_sweep) {
	// output signals at frequencies f_0 through f_1 (rad/s) over t_sweep (sec)

	float c = (f_1 - f_0) / t_sweep;
	float x = amp *sin(2 * M_PI * ((c * pow(t, 2) / 2) + f_0 * t));
	return x;

}

float SourceLib::cos_wave(float t, float w, float amp) {
	// output cos wave at frequency w (rad/s) amplitude amp

	float y = amp * cos(w * t);
	return y;

}

float SourceLib::doublet(float t, float t_start, float width, float delta_y, float y_init) {
	// output doublet signal starting at t_start with width width from y_init to delta_y

	float y;
	if (t < t_start) {
		y = y_init;
	} else if (t > t_start & t < t_start + width) {
		y = y_init + delta_y;
	} else if (t > t_start + width & t < t_start + 2 * width) {
		y = y_init - delta_y;
	} else {
		y = y_init;
	}
	return y;

}

float SourceLib::ramp(float t, float dydt, float y_init) {
	// output ramp signal starting at y_init with slope dydt

	float y = y_init + dydt * t;
	return y;

}

float SourceLib::sin_wave(float t, float w, float amp) {
	// output sin wave at frequency w (rad/s) amplitude amp

	float y = amp * sin(w * t);
	return y;

}

float SourceLib::step(float t, float t_step, float y_final, float y_init) {
	// output signal starting at y_init and stepping to y_final at t_step 

	float y;
	if (t < t_step) {
		y = y_init;
	} else {
		y = y_final;
	}
	return y;

}