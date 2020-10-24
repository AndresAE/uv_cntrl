/*
  Filters.h - Filter Library for Control Systems - description
  Copyright (c) 2020 Andres Sandoval.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Filters_h
#define Filters_h

// include types & constants of Wiring core API
#include "WConstants.h"

// library interface description
class Filters
{
    // user-accessible "public" interface
public:
    Filters(int);
    void high_pass(void);
    void high_pass(void);
    void complementary(void);

    // library-accessible "private" interface
private:
    int value;
    void doSomethingSecret(void);
};

#endif

