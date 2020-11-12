/*
  FlightLib.h - Flight Library for Control Systems - implementation
  Copyright (c) 2020 Andres Sandoval.  All right reserved.
*/

// include this library's description file
#include "FlightLib.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

FlightLib::FlightLib( float g=32.172 )
{
	_g = g;
}

// Public Methods //////////////////////////////////////////////////////////////
float FlightLib::alpha_est(float n_z, float v, float w, float s, float rho=0.00238, float c_l_a=2*M_PI )
{
	float alpha = 2 * w * n_z / (rho * pow(v, 2) * s * c_l_a) * 180 / M_PI;
}

float FlightLib::az2nz(float a_z)
{
	float n_z = a_z / _g + 1;
}

float FlightLib::nz2az(float n_z)
{
	float a_z = _g * (n_z - 1);
}

float FlightLib::nz2phi(float n_z)
{
	float phi = acos(1 / n_z) * 180 / M_PI;
}

float FlightLib::phi2nz( float phi )
{
	float n_z = 1 / cos (phi * M_PI / 180);
}
