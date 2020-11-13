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
    FlightLib( float g, float rho );
    float alpha_est( float n_z, float v, float w, float s, float c_l_a );
    float ax2nx( float a_x );
    float ay2ny( float a_y );
    float az2nz( float a_z );
    float nx2ax(float n_x);
    float ny2ay(float n_y);
    float nz2az( float n_z );
    float nz2phi( float n_z );
    float phi2nz( float phi );
    float v_gamma( float w, float n, float s, float ar, float c_d_0 );
    float v_s( float alpha, float gamma, float w, float n, float s, float c_l_a );
    float v_vy( float w, float n, float s, float ar, float c_d_0 );

    // library-accessible "private" interface
private:
    float _g;
    float _rho;
};

#endif
