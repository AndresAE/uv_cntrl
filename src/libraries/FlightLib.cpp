/*
  FlightLib.h - Flight Library for Control Systems - implementation
  Copyright (c) 2020 Andres Sandoval.  All right reserved.
*/

// include this library's description file
#include "FlightLib.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

FlightLib::FlightLib( float g, float rho )
{
	_g = g;
	_rho = rho;
}

// Public Methods //////////////////////////////////////////////////////////////
float FlightLib::alpha_est( float n_z, float v, float w, float s, float c_l_a=2*M_PI )
{
	float alpha = 2 * w * n_z / (_rho * pow(v, 2) * s * c_l_a) * 180 / M_PI;
	return alpha;
}

float FlightLib::ax2nx( float a_x )
{
	float n_x = a_x / _g;
	return n_x;
}

float FlightLib::ay2ny( float a_y )
{
	float n_y = a_y / _g;
	return n_y;
}

float FlightLib::az2nz( float a_z )
{
	float n_z = a_z / _g + 1;
	return n_z;
}

float FlightLib::nx2ax( float n_x )
{
	float a_x = _g * n_x;
	return a_x;
}

float FlightLib::ny2ay( float n_y )
{
	float a_y = _g * n_y;
	return a_y;
}

float FlightLib::nz2az( float n_z )
{
	float a_z = _g * (n_z - 1);
	return a_z;
}

float FlightLib::nz2phi( float n_z )
{
	float phi = acos(1 / n_z) * 180 / M_PI;
	return phi;
}

float FlightLib::phi2nz( float phi )
{
	float n_z = 1 / cos (phi * M_PI / 180);
	return n_z;
}

float FlightLib::v_gamma( float w, float n, float s, float ar, float c_d_0=0.05 )
{
	float v = sqrt(2 * w * n / (_rho * s * sqrt(c_d_0 * M_PI * ar * 0.75)));
	return v;
}

float FlightLib::v_s(float w, float n, float s, float c_l_max)
{
	float v = sqrt(2 * w * n / (_rho * s * c_l_max));
	return v;
}

float FlightLib::v_vy( float w, float n, float s, float ar, float c_d_0=0.05 )
{
	float v = sqrt(2 * w * n / (_rho * s * sqrt(c_d_0 * M_PI * ar * 0.75 / 3)));
	return v;
}
