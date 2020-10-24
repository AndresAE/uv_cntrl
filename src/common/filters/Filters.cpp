/*
  Filters.h - Filter Library for Control Systems - implementation
  Copyright (c) 2020 Andres Sandoval.  All right reserved.
*/

// include core Wiring API
#include "WProgram.h"

// include this library's description file
#include "Filters.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Filters::Filters(int givenValue)
{
	// initialize this instance's variables
	value = givenValue;

	// do whatever is required to initialize the library
	pinMode(13, OUTPUT);
	Serial.begin(9600);
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

void Filters::high_pass(void)
{
	// eventhough this function is public, it can access
	// and modify this library's private variables
	Serial.print("value is ");
	Serial.println(value);

}

void Filters::low_pass(void)
{
	// eventhough this function is public, it can access
	// and modify this library's private variables
	Serial.print("value is ");
	Serial.println(value);

}

void Filters::complementary(void)
{
	// eventhough this function is public, it can access
	// and modify this library's private variables
	Serial.print("value is ");
	Serial.println(value);

}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

void Filters::doSomethingSecret(void)
{
	digitalWrite(13, HIGH);
	delay(200);
	digitalWrite(13, LOW);
	delay(200);
}

