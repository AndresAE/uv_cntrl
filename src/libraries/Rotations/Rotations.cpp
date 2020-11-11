/*
  Rotations.h - Rotations Library for Control Systems - implementation
  Copyright (c) 2020 Andres Sandoval.  All right reserved.
*/

// include this library's description file
#include "Rotations.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Rotations::Rotations()
{}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

float Rotations::b2w(float a, float b)
{
	// eventhough this function is public, it can access
	// and modify this library's private variables
	float s[3][3] = {{cos (a) * cos (b), sin (b), sin (a) * cos (b)}, {-cos (a) * sin (b), cos (b),-sin (a) * sin (b)}, {-sin (a), 0, cos (a)}};

}

float Rotations::eci2ned(float mu, float l)
{
	// eventhough this function is public, it can access
	// and modify this library's private variables
	float b[3][3] = {{cos (mu), -sin (mu) * sin (l), sin (mu) * cos (l)}, 
		{0, cos (l), sin (l)}, 
		{-sin (mu), -cos (mu) * sin (l), cos (mu) * cos (l)}};

}

float Rotations::ned2abc(float phi, float the, float psi)
{
	// eventhough this function is public, it can access
	// and modify this library's private variables
	float b[3][3] = {{cos (the) * cos (psi), cos (the) * sin (psi), -sin (the)}, 
			 {-cos (phi) * sin (psi) + sin (phi) * sin (the) * cos (psi), cos (phi) * cos (psi) + sin (phi) * sin (the) * sin (psi), sin (phi) * cos (the)}, 
			 {sin (phi) * sin (psi) + cos (phi) * sin (the) * cos (phi), -sin (phi) * cos (psi) + cos (phi) * sin (the) * sin (psi), cos (phi) * cos (the)}};

}
