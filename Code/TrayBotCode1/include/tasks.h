#include "push.h"

int counter = 0;

void addCounter() {
  counter += 1;
}

//adjusts the tray as lift is going up
void adjustTilt(int val) {
  double potVal = lift.rotation(rotationUnits::deg);

  if(potVal > val) {
    push.rotateFor(200, rotationUnits::deg, 80, velocityUnits::pct, false);
  }
  else if(potVal < val) {
    push.rotateFor(-200, rotationUnits::deg, 80, velocityUnits::pct, false);
  }
  // else if(fabs(potVal - val) < 30) {
  //   push.spin(directionType::fwd, 0, velocityUnits::pct);
  // }
}

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

//Controls the lift when certain buttons are pressed (x and y)
/*int liftButton() {
  int counter = 0;
  while(true) {
    Controller1.ButtonRight.pressed(addCounter);
    switch(counter){
      case 1: //Intaking the cubes
        controlLift(500);
        break;
      case 2: 
        push.startRotateFor(200, rotationUnits::deg, 100, velocityUnits::pct);
        controlLift(650);
        counter = 0;
        break;
      default:
        break;
    }
  }
  //returns nothing, because it just does stuff
  return(0);
}*/

int scanLift() {
  while(true) {
    if(lift.rotation(rotationUnits::deg) > 120) {
      adjustTilt(300);
    }
  }
  //returns nothing, because it just does stuff
  return(0);
}

void quickSmallStack() {
  while(push.rotation(rotationUnits::deg) <= 720) { //pushes the tray to stacking position (use this for now)
    push.spin(directionType::fwd, (825 - push.rotation(rotationUnits::deg))/6,velocityUnits::pct); //was 850 and 8
    intakeMotors.spin(directionType::fwd, 5, percentUnits::pct);
    /*if(Controller1.ButtonX.pressing()) {
      while(Controller1.ButtonX.pressing()) {}
      break;
    }*/
  }
}

int quickStack() {
  while(true) {
    Controller1.ButtonRight.pressed(quickSmallStack);
  }
  return(0);
}