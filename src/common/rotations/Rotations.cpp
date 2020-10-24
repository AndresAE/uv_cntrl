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

void Rotations::high_pass(void)
{
	// eventhough this function is public, it can access
	// and modify this library's private variables
	Serial.print("value is ");
	Serial.println(value);

}

void Rotations::low_pass(void)
{
	// eventhough this function is public, it can access
	// and modify this library's private variables
	Serial.print("value is ");
	Serial.println(value);

}

void Rotations::complementary(void)
{
	// eventhough this function is public, it can access
	// and modify this library's private variables
	Serial.print("value is ");
	Serial.println(value);

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

