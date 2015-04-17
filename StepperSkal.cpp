/*
  StepperSkal.cpp - Library for control a stepper motor with driver (in my case DRV8825)
  Created by Albert Mulà Conesa, April 17, 2015.
  http://github.com/skal88/StepperSkal
*/

#include "Arduino.h"
#include "StepperSkal.h"

StepperSkal::StepperSkal(int pinEnable, int pinDirection, int pinSteps, int pinM0, int pinM1, int pinM2)
{
  pinMode(pinEnable, OUTPUT);
  pinMode(pinDirection, OUTPUT);
  pinMode(pinSteps, OUTPUT);
  pinMode(pinM0, OUTPUT);
  pinMode(pinM1, OUTPUT);
  pinMode(pinM2, OUTPUT);
  _pinEnable = pinEnable;
  _motorDivider = 1;
  _pinDirection = pinDirection;
  _pinSteps = pinSteps;
  _pinM0 = pinM0;
  _pinM1 = pinM1;
  _pinM2 = pinM2;
  _motorStepsLap = 200;
  _motorEnable = HIGH; // Apagado (Logica inversa)
  _motorDirection = HIGH;
  _motorStepsOffset = 0;
  _motorStepsDelay = 10;
}

void StepperSkal::enable()
{
   _motorEnable = LOW;
   digitalWrite(_pinEnable, _motorEnable);
}

void StepperSkal::disable()
{
   _motorEnable = HIGH;
   digitalWrite(_pinEnable, _motorEnable);
}

void StepperSkal::microstep(String divider){
  if(divider == "FULL"){
    _motorDivider = 1;
    digitalWrite(_pinM0, LOW);
    digitalWrite(_pinM1, LOW);
    digitalWrite(_pinM2, LOW);
  } else if(divider == "HALF"){
    _motorDivider = 2;
    digitalWrite(_pinM0, HIGH);
    digitalWrite(_pinM1, LOW);
    digitalWrite(_pinM2, LOW);
  } else if(divider == "1/4"){
    _motorDivider = 4;
    digitalWrite(_pinM0, LOW);
    digitalWrite(_pinM1, HIGH);
    digitalWrite(_pinM2, LOW);
  } else if(divider == "1/8"){
    _motorDivider = 8;
    digitalWrite(_pinM0, HIGH);
    digitalWrite(_pinM1, HIGH);
    digitalWrite(_pinM2, LOW);
  } else if(divider == "1/16"){
    _motorDivider = 16;
    digitalWrite(_pinM0, LOW);
    digitalWrite(_pinM1, LOW);
    digitalWrite(_pinM2, HIGH);
  } else if(divider == "1/32"){
    _motorDivider = 32;
    digitalWrite(_pinM0, LOW);
    digitalWrite(_pinM1, HIGH);
    digitalWrite(_pinM2, HIGH);
  } else{
    _motorDivider = 1;
    digitalWrite(_pinM0, LOW);
    digitalWrite(_pinM1, LOW);
    digitalWrite(_pinM2, LOW);
  }
}

void StepperSkal::direction(String direction)
{
   if(direction == "FORWARD"){ _motorDirection = HIGH; }
   else if(direction == "BACKWARD"){ _motorDirection = LOW; }
   digitalWrite( _pinDirection, _motorDirection);
}

void StepperSkal::stepsDelay(long stepsDelay ){
  _motorStepsDelay = stepsDelay;
}

void StepperSkal::steps(int steps){
  if(_motorDirection == HIGH){
    _motorStepsOffset += steps;
  } else if(_motorDirection == LOW){
    _motorStepsOffset -= steps;
  }
  // 
  for( int i=0; i<(steps*_motorDivider); i++){
    digitalWrite( _pinSteps, HIGH );
    delay( _motorStepsDelay );
    digitalWrite( _pinSteps, LOW );
    delay( _motorStepsDelay );
  } 
}

void StepperSkal::laps(int laps){
  int steps = laps * _motorStepsLap * _motorDivider;
  if(_motorDirection == HIGH){
    _motorStepsOffset += steps;
  } else if(_motorDirection == LOW){
    _motorStepsOffset -= steps;
  }
  // Avance de 200 pas
  for( int i=0; i<steps; i++){
    digitalWrite( _pinSteps, HIGH );
    delay( _motorStepsDelay );
    digitalWrite( _pinSteps, LOW );
    delay( _motorStepsDelay );
  }
}

void StepperSkal::stepsLap(int stepsLap){
  _motorStepsLap = stepsLap;
}

void StepperSkal::reset(){
  int actualMotorDirection = _motorDirection;
  int steps = _motorStepsOffset * _motorDivider;

  if(_motorStepsOffset < 0){ // Si la posición actual es menor que 0 (recorremos hasta 0 hacia adelante)
    _motorDirection = HIGH;
    steps = abs(steps); // Pasamos el numero negativo a positivo para mover el motor // steps = -steps;
  } else if(_motorStepsOffset > 0){
    _motorDirection = LOW;
  }
  digitalWrite( _pinDirection, _motorDirection); // Actualizamos la dirección (Encendiendo o pagando la salida correspondiente)

  for( int i=0; i<steps; i++){
    digitalWrite( _pinSteps, HIGH );
    delay( _motorStepsDelay );
    digitalWrite( _pinSteps, LOW );
    delay( _motorStepsDelay );
  }
}