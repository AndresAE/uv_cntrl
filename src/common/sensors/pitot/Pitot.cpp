/*
  Pitot.cpp - Pitot Library - implementation
  Copyright (c) 2020 Andres Sandoval.  All rights reserved.
*/

// include this library's description file
#include "Pitot.h"

// Constructor /////////////////////////////////////////////////////////////////
Pitot::Pitot(int pin)
{
  _pin = pin;
}

// Public Methods //////////////////////////////////////////////////////////////
float Pitot::indicated_airspeed( int offset )
{
  float adc_avg = 0; float veloc = 0.0;
  float V_0 = 5.0; // supply voltage to the pressure sensor
  float rho = 1.204; // density of air 

  // parameters for averaging and offset
  int veloc_mean_size = 20;
  int zero_span = 2;
  // average a few ADC readings for stability
  for (int ii=0;ii<veloc_mean_size;ii++){
    adc_avg+= analogRead(_pin)-offset;
  }
  adc_avg/=veloc_mean_size;
  // make sure if the ADC reads below 512, then we equate it to a negative velocity
  if (adc_avg>512-zero_span and adc_avg<512+zero_span){
  } else{
    if (adc_avg<512){
      veloc = -sqrt((-10000.0*((adc_avg/1023.0)-0.5))/rho);
    } else{
      veloc = sqrt((10000.0*((adc_avg/1023.0)-0.5))/rho);
    }
  }
  return veloc;

}
float Pitot::offset( void )
{
  int offset = 0;
  int offset_size = 10;
  for (int ii=0;ii<offset_size;ii++){
    offset += analogRead(_pin)-(1023/2);
  }
  offset /= offset_size;
  return offset;
}
