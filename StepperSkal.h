
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
    StepperSkal(int pinEnable, int pinDirection, int pinSteps, int pinM0, int pinM1, int pinM2);
    void enable();
    void disable();
    void microstep(String divider);
    void direction(String direction);
    String getDirection();
    void stepsDelay(long stepsDelay);
    void steps(int steps);
    void move(int steps);
    void laps(int laps);
    void stepsLap(int stepsLap);
    void reset();
  private:
    int _pinEnable;
    int _pinDirection;
    int _pinSteps;
    int _pinM0;
    int _pinM1;
    int _pinM2;
    int _motorEnable;
    int _motorDivider; // FULL, HALF, 1/4, 1/8, 1/16, 1/32
    int _motorDirection;
    int _motorStepsOffset; // Pasos de diferencia con la posición inicial
    long _motorStepsDelay; // Tiempo entre paso y paso (ms)
    int _motorStepsLap;
    int _motorSteps; // Guardamos aqui los pasos que tenemos que hacer (Una vez hechos lo ponemos a 0)
};

#endif