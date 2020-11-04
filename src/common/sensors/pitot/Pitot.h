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

// library interface description
class Pitot
{
    // user-accessible "public" interface
public:
    // constructor
    Pitot( int pin);

    // methods
    float indicated_airspeed( int offset );
    float offset( void );
    float true_airspeed( float veloc_e, float rho_0 );
    
private:
    int _pin;
};

#endif
