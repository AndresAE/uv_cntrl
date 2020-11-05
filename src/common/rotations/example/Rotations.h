/*
  Rotations.h - Rotations Library for Control Systems - description
  Copyright (c) 2020 Andres Sandoval.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Rotations_h
#define Rotations_h

// include types & constants of Wiring core API
#if (ARDUINO >=100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <math.h>

// library interface description
class Rotations
{
    // user-accessible "public" interface
public:
    Rotations();
    float b2w(float a, float b);
    float eci2ned(float mu, float l);
    float ned2abc(float phi, float the, float psi);

    // library-accessible "private" interface
private:
};

#endif
