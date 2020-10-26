/*
  Rotations.h - Rotations Library for Control Systems - implementation
  Copyright (c) 2020 Andres Sandoval.  All right reserved.
*/

// include core Wiring API
#include "WProgram.h"

// include this library's description file
#include "Rotations.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Rotations::Rotations(int givenValue)
{
	// initialize this instance's variables
	value = givenValue;

	// do whatever is required to initialize the library
	pinMode(13, OUTPUT);
	Serial.begin(9600);
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

void Rotations::b2w(void)
{
	// eventhough this function is public, it can access
	// and modify this library's private variables
	float s[3][3] = {{cos(a)*cos(b),sin(b),s(a)*cos(b)}, {-c(a)*s(b),c(b),-s(a)*s(b)}, {-sin(a),0,cos(a)}};

}

void Rotations::eci2ned(void)
{
	// eventhough this function is public, it can access
	// and modify this library's private variables
	float b[3][3] = {{cos(mu),-sin(mu)*sin(l),sin(mu)*cos(l)}, {0,cos(l),sin(l)}, {-sin(mu),-cos(mu)*sin(l),cos(mu)*cos(l)}};

}

void Rotations::ned2abc(void)
{
	// eventhough this function is public, it can access
	// and modify this library's private variables
	float b[3][3] = {{cos(the)*cos(psi),cos(the)*sin(psi),-sin(the)}, 
			 {-cos(phi)*sin(psi)+sin(phi)*sin(the)*cos(psi),cos(phi)*cos(psi)+sin(phi)*sin(the)*sin(psi),sin(phi)*cos(the)}, 
			 {sin(phi)*sin(psi)+cos(phi)*sin(the)*cos(phi),-sin(phi)*cos(psi)+cos(phi)*sin(the)*sin(psi),cos(phi)*cos(the)}};

}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

void Rotations::doSomethingSecret(void)
{
	digitalWrite(13, HIGH);
	delay(200);
	digitalWrite(13, LOW);
	delay(200);
}

