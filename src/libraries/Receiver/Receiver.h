/*
  Receiver.h - Receiver Library - description
  Copyright (c) 2020 Andres Sandoval.  All rights reserved.
*/

// ensure this library description is only included once
#ifndef Receiver_h
#define Receiver_h

// include types & constants of Wiring core API
#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

// library interface description
class Receiver
{
    // user-accessible "public" interface
public:
    // constructor
    Receiver( int transmitter_min=978, int transmitter_range=1027 );

    // methods
    float linear_control(int ch, float k, float offset=90, int pwm=35000);
    
private:
    float _transmitter_min;
    float _transmitter_range;
};

#endif
