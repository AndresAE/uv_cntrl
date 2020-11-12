/*
  FlightLib.h - Flight Library for Control Systems - description
  Copyright (c) 2020 Andres Sandoval.  All right reserved.
*/

// ensure this library description is only included once
#ifndef FlightLib_h
#define FlightLib_h

// include types & constants of Wiring core API
#if (ARDUINO >=100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <math.h>

// library interface description
class FlightLib
{
    // user-accessible "public" interface
public:
    FlightLib( float g );
    float alpha_est(float n, float v, float w, float s, float rho, float c_l_a);
    float az2nz( float a_z );
    float nz2az( float n_z );
    float nz2phi( float n_z );
    float phi2nz( float phi );

    // library-accessible "private" interface
private:
    float _g;
};

#endif
