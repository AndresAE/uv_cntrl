/*
  SourceLib.h - Source Library for Control Systems - description
  Copyright (c) 2021 Andres Sandoval.  All right reserved.
*/

// ensure this library description is only included once
#ifndef SourceLib_h
#define SourceLib_h
#include <cmath>

// library interface description
class SourceLib {

    // user-accessible "public" interface
public:
    float chirp(float t, float amp, float f_0, float f_1, float t_sweep);
    float cos_wave(float t, float w, float amp);
    float doublet(float t, float t_start, float width, float delta_y, float y_init);
    float ramp(float t, float dydt, float y_init);
    float step(float t, float t_step, float y_final, float y_init);
    float sin_wave(float t, float w, float amp);

};

#endif