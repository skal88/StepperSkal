/*
  StepperSkal.cpp - Library for control a stepper motor with driver (in my case DRV8825)
  Created by Albert Mulà Conesa, April 17, 2015.
  http://github.com/skal88/StepperSkal
*/

#include "Arduino.h"
#include "StepperSkal.h"

StepperSkal::StepperSkal(int pinEnable, int pinDirection, int pinSteps)
{
  pinMode(pinEnable, OUTPUT);
  pinMode(pinDirection, OUTPUT);
  pinMode(pinSteps, OUTPUT);
  _pinEnable = pinEnable;
  _pinDirection = pinDirection;
  _pinSteps = pinSteps;
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

void StepperSkal::direction(String direction)
{
   if(direction == "FORWARD"){ _motorDirection = HIGH; }
   else if(direction == "BACKWARD"){ _motorDirection = LOW; }
   digitalWrite( _pinDirection, _motorDirection);
}

void StepperSkal::stepsDelay( int stepsDelay ){
  _motorStepsDelay = stepsDelay;
}

void StepperSkal::steps(int steps){
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

void StepperSkal::laps(int laps){
  int steps = laps * _motorStepsLap;
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
  int steps = _motorStepsOffset;

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