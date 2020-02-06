#include "push.h"

//Intake functions where button is pressed and it just starts spinning (reverse)
int intakeRev() {
  int counter = 0;
  while(true) {
    if(Controller1.ButtonDown.pressing()) {
      while(Controller1.ButtonDown.pressing()) {}
      counter++;
    }
    switch(counter){
      case 1: //Intaking the cubes
        intakeMotors.spin(directionType::rev, 100, velocityUnits::pct);
        break;
      case 2: 
        intakeMotors.stop(brakeType::brake);
        counter = 0;
        break;
      default:
        intakeMotors.stop(brakeType::brake);
        break;
    }
  }
  //returns nothing, because it just does stuff
  return(0);
}

//Literally controls the lift
void controlLift(int x) {
  lift.rotateFor(x,rotationUnits::deg, true);
}

//Controls the lift when certain buttons are pressed (x and y)
int liftButton() {
  while(true) {
    if(Controller1.ButtonDown.pressing()) {
      controlLift(280); //Small tower height *TESTING*
    }
    else if(Controller1.ButtonUp.pressing()) {
      controlLift(360); //Large tower height *TESTING*
    }
  }
  //returns nothing, because it just does stuff
  return(0);
}