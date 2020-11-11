/*
  Filters.h - Filter Library for Control Systems - description
  Copyright (c) 2020 Andres Sandoval.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Filters_h
#define Filters_h

// include types & constants of Wiring core API
#if (ARDUINO >=100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// library interface description
class Filters
{
    // user-accessible "public" interface
public:
    // constructor
    Filters();

    // methods
    float derivative(float y [], float dt);
    float high_pass(float x [], float y [], float hp_frequency, float dt);
    float integral(float y [], float dt, float c = 0);
    float limit(float y, float limits []);
    float low_pass(float x, float y [], float lp_frequency, float dt);

private:
};

#endif
