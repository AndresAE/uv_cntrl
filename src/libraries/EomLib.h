/*
  EomLib.h - Equations of Motion Library for Control Systems - description
  Copyright (c) 2021 Andres Sandoval.  All right reserved.
*/

// ensure this library description is only included once
#ifndef EomLib_h
#define EomLib_h

#include <math.h>

// library interface description
class EomLib
{
    // user-accessible "public" interface
public:
    float alpha_est(float n_z, float v, float w, float s, float c_l_a);

};

#endif