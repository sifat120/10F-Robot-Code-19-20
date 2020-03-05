#include "drive.h"

//Lift function (dw about this, because it is for arcade drive)
void liftN() {
  int threshold = 10;
  int ry = Controller1.Axis2.position(pct); //Right Joystick Y-Axis

 if(abs(ry) < threshold) ry = 0;

  lift.spin(directionType::fwd, ry, velocityUnits::pct);
}

//Lift function when tank drive function is enabled
int liftwT() {
  while(true){
  // //Going up
  // if(Controller1.ButtonL1.pressing()) { //lift is going down
  //   while(Controller1.ButtonL1.pressing()) {
  //     lift.spin(directionType::fwd, liftSpeed, velocityUnits::pct);
  //   }
  //   lift.stop(brakeType::hold);
  // }
  // //Going down
  // else if(Controller1.ButtonL2.pressing() && lift.rotation(rotationUnits::deg) >= 0) { //lift is going up
  //   while(Controller1.ButtonL2.pressing() && lift.rotation(rotationUnits::deg) >= 0){
  //     lift.spin(directionType::rev, liftSpeed, velocityUnits::pct);
  //   }
  //   lift.stop(brakeType::hold);
  // }
    if(Controller1.ButtonL1.pressing()) {
      while(Controller1.ButtonL1.pressing()) {
        lift.spin(directionType::fwd, 100, velocityUnits::pct);
      }
      lift.stop(brakeType::hold);
    }
    else if(Controller1.ButtonL2.pressing() && lift.rotation(rotationUnits::deg) >= 0) {
      while(Controller1.ButtonL2.pressing()) {
        lift.spin(directionType::rev, 100, velocityUnits::pct);
      }
      lift.stop(brakeType::hold);
    }
    /*else {
      lift.stop(brakeType::hold);
    }*/
  }
  return(0);
} 

//Intake function 
int intake() {
  while(true) {
  // //intaking the cube
  // if(Controller1.ButtonR1.pressing()) { 
  //   while(Controller1.ButtonR1.pressing()){
  //     intakeMotors.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
  //   }
  //   intakeMotors.stop(brakeType::hold);
  // }
  // //releasing the cube
  // else if(Controller1.ButtonR2.pressing()) { //pushes the cube out (into towers)
  //   while(Controller1.ButtonR2.pressing()) {
  //     intakeMotors.spin(directionType::fwd, 65, velocityUnits::pct);
  //   } 
  //   intakeMotors.stop(brakeType::hold); 
  // }
  if(Controller1.ButtonR1.pressing()) {
    while(Controller1.ButtonR1.pressing()) {
      intakeMotors.spin(directionType::rev, 100, velocityUnits::pct);
      //intakeMotors.spin(directionType::rev, 12, voltageUnits::volt);
    }
    intakeMotors.stop(brakeType::hold);
  }
  else if(Controller1.ButtonR2.pressing()) {
    while(Controller1.ButtonR2.pressing()) {
      intakeMotors.spin(directionType::fwd, 55, velocityUnits::pct);
    }
    intakeMotors.stop(brakeType::hold);
  }
  }
  return(0);
    /*else {
      intakeMotors.stop(brakeType::hold);
    }*/
}



//Fast reverse intake function
int reset() {
  while(true) {
    if(Controller1.ButtonLeft.pressing()) { //pushes the cube out (into towers if far away)
      //intakeMotors.spin(directionType::fwd, 100, velocityUnits::pct);
      while(Controller1.ButtonLeft.pressing()) {}
      push.startRotateTo(0,rotationUnits::deg,35,velocityUnits::pct);
      lift.startRotateTo(0,rotationUnits::deg,100,velocityUnits::pct);
    }
  }
  return(0);
}

//for the smaller tower
void smallTower() {
  /*while(lift.rotation(rotationUnits::deg) <= 475) {
    push.spin(directionType::fwd, 15, velocityUnits::pct);
    lift.spin(directionType::fwd, 95, velocityUnits::pct);
  }*/
   push.startRotateFor(directionType::fwd,200,rotationUnits::deg,10,velocityUnits::pct);
   lift.startRotateFor(directionType::fwd,500,rotationUnits::deg,100,velocityUnits::pct);
  // if(Controller1.ButtonX.pressing()) {
  //     while(Controller1.ButtonX.pressing()) {}
  //     push.stop(brakeType::hold);
  //     lift.stop(brakeType::hold);
  // }
}

//for the medium tower
void mediumTower() {
  while(lift.rotation(rotationUnits::deg) <= 600) {
    push.spin(directionType::fwd, 30, velocityUnits::pct);
    lift.spin(directionType::fwd, 95, velocityUnits::pct);
  }
}

/*int buttonPressed() {
  while(true) {
    Controller1.ButtonB.pressed(smallTower);
    Controller1.ButtonA.pressed(mediumTower);
  }
  return(0);
}*/

int buttonPressedNew() {
  while(true) {
    if(Controller1.ButtonB.pressing()) {
      while(Controller1.ButtonB.pressing()) {}
      push.startRotateTo(250,rotationUnits::deg,35,velocityUnits::pct);
      lift.startRotateTo(500,rotationUnits::deg,100,velocityUnits::pct);
    }
    else if(Controller1.ButtonA.pressing()) {
      while(Controller1.ButtonA.pressing()) {}
      push.startRotateTo(250,rotationUnits::deg,25,velocityUnits::pct);
      lift.startRotateTo(650,rotationUnits::deg,100,velocityUnits::pct);
    }
  }
  return(0);
}