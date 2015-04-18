#include <StepperSkal.h>
#include <IRremote.h>

// IR
int IR_pin = 2;
IRrecv irrecv(IR_pin);
decode_results results;


StepperSkal step1(13, 8, 9, 7, 6, 5);
int stepperStatus = 0;
int stepperPlay = 0;
int stepperDelayC = 1;

void setup(){
  Serial.begin(9600);
  // IR
  irrecv.enableIRIn();
}

void loop(){
  step1.stepsDelay(stepperDelayC);
  if(stepperStatus == 1){ step1.enable(); }
  else{ step1.disable(); }
  
  if(stepperPlay == 1){ step1.steps(1); }
  
  // IR
  if (irrecv.decode(&results)){
    Serial.println(results.value);
    String actDir = step1.getDirection();
    switch(results.value){
      case 16724175:
        if(stepperStatus == 1){ stepperStatus = 0; }
        else{ stepperStatus = 1; }
        break;
        
      case 16720095:
        stepperPlay = 1;
        break;
      case 16716015:
        stepperPlay = 0;
        break;
      case 16732335:
        if(stepperPlay == 0){ stepperPlay = 1; }
        else{ stepperPlay = 0; }
        break;
        
      case 16712445:
        if(stepperDelayC < 100){ stepperDelayC++; }
        break;
      case 16724685:
        if(stepperDelayC > 1){ stepperDelayC--; }
        break;
        
      case 16756815:
        step1.microstep("FULL");
        break;
      case 16748655:
        step1.microstep("HALF");
        break;
      case 16752735:
        step1.microstep("1/4");
        break;
      case 16773645:
        step1.microstep("1/8");
        break;
      case 16765485:
        step1.microstep("1/16");
        break;
      case 16769565:
        step1.microstep("1/32");
        break;
      case 16726215:
        step1.direction("FORWARD");
        break;
      case 16767525:
        step1.direction("BACKWARD");
        break;
      case 16736415:
        step1.laps(1);
        break;
      case 16771605:
        step1.direction("BACKWARD");
        step1.steps(1);
        step1.direction(actDir);
        break;
      case 16713975:
        step1.direction("FORWARD");
        step1.steps(1);
        step1.direction(actDir);
        break;
        
      case 16760895:
        step1.reset();
        break;
    }

    irrecv.resume(); // Receive the next value
  }
  
}

