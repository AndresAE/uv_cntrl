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
    float derivative(double y, float dt);
    float high_pass(double x, double y, float hp_frequency, float dt);
    float integral(double y, float dt, float c = 0);
    float limit(float y, float limits);
    float low_pass(double x, double y, float hp_frequency, float dt);

private:
};

#endif
