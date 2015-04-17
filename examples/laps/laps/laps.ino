#include <StepperSkal.h>

StepperSkal step1(13, 8, 9);


void setup(){
  step1.velocity(0);
  step1.enable();
}

void loop(){
  step1.direction("FORWARD");
  step1.laps(2);
  delay(2000);
  step1.direction("BACKWARD");
  step1.laps(1);
  delay(2000);
}

