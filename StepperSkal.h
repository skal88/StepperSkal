
/*
  StepperSkal.h - Library for control a stepper motor with driver (in my case DRV8825)
  Created by Albert Mulà Conesa, April 17, 2015.
  http://github.com/skal88/StepperSkal
*/
#ifndef StepperSkal_h
#define StepperSkal_h

#include "Arduino.h"

class StepperSkal
{
  public:
    StepperSkal(int pinEnable, int pinDirection, int pinSteps);
    void enable();
    void disable();
    void direction(String direction);
    void stepsDelay( int stepsDelay );
    void steps(int steps);
    void laps(int laps);
    void stepsLap(int stepsLap);
    void reset();
  private:
    int _pinEnable;
    int _pinDirection;
    int _pinSteps;
    int _motorEnable;
    int _motorDirection;
    int _motorStepsOffset; // Pasos de diferencia con la posición inicial
    int _motorStepsDelay; // Tiempo entre paso y paso (ms)
    int _motorStepsLap;
};

#endif