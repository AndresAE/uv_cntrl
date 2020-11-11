/*
  Receiver.cpp - Receiver Library - implementation
  Copyright (c) 2020 Andres Sandoval.  All rights reserved.
*/

// include this library's description file
#include "Receiver.h"

// Constructor /////////////////////////////////////////////////////////////////
Receiver::Receiver( int transmitter_min, int transmitter_range )
{
  _transmitter_min = transmitter_min;
  _transmitter_range = transmitter_range;
}

// Public Methods //////////////////////////////////////////////////////////////
float Receiver::linear_control(int ch, float k, float offset, int pwm)
{
  float out, command;
  out = pulseIn(ch, HIGH, pwm);
  command = (out - _transmitter_min - _transmitter_range / 2) / _transmitter_range * k + offset;
  return command;

}
