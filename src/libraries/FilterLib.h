/*
  FilterLib.h - Filter Library for Control Systems - description
  Copyright (c) 2021 Andres Sandoval.  All right reserved.
*/

// ensure this library description is only included once
#ifndef FilterLib_h
#define FilterLib_h

// library interface description
class FilterLib {

// user-accessible "public" interface
public:
    float low_pass_filter(float y_0, float y_1, float d_t, float w_c);
    float high_pass_filter(float y_0, float x_0, float x_1, float d_t, float w_c);
    float position_saturation(float y, float y_min, float y_max);
    float rate_saturation(float y_0, float y_1, float dt, float y_dt_min, float y_dt_max);

};

#endif