/*
  FlightLib.h - Flight Library for Control Systems - implementation
  Copyright (c) 2020 Andres Sandoval.  All right reserved.
*/

// include this library's description file
#include "FlightLib.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

FlightLib::FlightLib( float g=32.172, float rho=0.00238 )
{
	_g = g;
	_rho = rho;
}

// Public Methods //////////////////////////////////////////////////////////////
float FlightLib::alpha_est( float n_z, float v, float w, float s, float c_l_a=2*M_PI )
{
	float alpha = 2 * w * n_z / (_rho * pow(v, 2) * s * c_l_a) * 180 / M_PI;
}

float FlightLib::ax2nx( float a_x )
{
	float n_x = a_x / _g;
}

float FlightLib::ay2ny( float a_y )
{
	float n_y = a_y / _g;
}

float FlightLib::az2nz( float a_z )
{
	float n_z = a_z / _g + 1;
}

float FlightLib::nx2ax( float n_x )
{
	float a_x = _g * n_x;
}

float FlightLib::ny2ay( float n_y )
{
	float a_z = _g * n_y;
}

float FlightLib::nz2az( float n_z )
{
	float a_z = _g * (n_z - 1);
}

float FlightLib::nz2phi( float n_z )
{
	float phi = acos(1 / n_z) * 180 / M_PI;
}

float FlightLib::phi2nz( float phi )
{
	float n_z = 1 / cos (phi * M_PI / 180);
}

float FlightLib::v_gamma( float w, float n, float s, float ar, float c_d_0=0.05 )
{
	float v = sqrt(2 * w * n / (_rho * s * sqrt(c_d_0 * M_PI * ar)));
}

float FlightLib::v_s( float alpha, float gamma, float w, float n, float s, float c_l_a=2*M_PI )
{
	float v = sqrt(2 * w * n / (_rho * s * c_l_a * (alpha - gamma)));
}

float FlightLib::v_vy( float w, float n, float s, float ar, float c_d_0=0.05 )
{
	float v = sqrt(2 * w * n / (_rho * s * sqrt(3 * c_d_0 * M_PI * ar)));
}
