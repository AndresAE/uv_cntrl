/*
  Pitot.h - Pitot Library - description
  Copyright (c) 2020 Andres Sandoval.  All rights reserved.
*/

// ensure this library description is only included once
#ifndef Pitot_h
#define Pitot_h

// include types & constants of Wiring core API
#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <math.h>

// library interface description
class Pitot
{
    // user-accessible "public" interface
public:
    // constructor
    Pitot( int pin, float rho_sl, float p_sl, float a_sl);

    // methods
    float equivalent_airspeed(float veloc, float p);
    float indicated_airspeed( int offset );
    float offset( void );
    float true_airspeed( float veloc_e, float rho );
    
private:
    int _pin;
    int _rho_sl;
    int _p_sl;
    int _a_sl;
};

#endif
