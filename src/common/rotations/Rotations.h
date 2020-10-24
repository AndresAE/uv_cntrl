/*
  Rotations.h - Rotations Library for Control Systems - description
  Copyright (c) 2020 Andres Sandoval.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Rotations_h
#define Rotations_h

// include types & constants of Wiring core API
#include "WConstants.h"

// library interface description
class Rotations
{
    // user-accessible "public" interface
public:
    Rotations(int);
    void high_pass(void);
    void high_pass(void);
    void complementary(void);

    // library-accessible "private" interface
private:
    int value;
    void doSomethingSecret(void);
};

#endif

