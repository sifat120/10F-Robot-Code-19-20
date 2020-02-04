#include "drive.h"

//Lift function (dw about this, because it is for arcade drive)
void liftN() {
  int threshold = 10;
  int ry = Controller1.Axis2.position(pct); //Right Joystick Y-Axis

 if(abs(ry) < threshold) ry = 0;

  lift.spin(directionType::fwd, ry, velocityUnits::pct);
}

//Lift function when tank drive function is enabled
void liftwT(int liftSpeed) {
  //Going up
  if(Controller1.ButtonL1.pressing()) { //lift is going down
    lift.spin(directionType::rev, liftSpeed, velocityUnits::pct);
  }
  //Going down
  else if(Controller1.ButtonL2.pressing()) { //lift is going up
    lift.spin(directionType::fwd, liftSpeed, velocityUnits::pct);
    //push.rotateFor(directionType::fwd, 60, rotationUnits::deg);
  }
  //stopped if no button is being pressed
  else {
    lift.stop(brakeType::hold);
  }
} 

void adjustTilt(int val) {
  double potVal = lift.rotation(rotationUnits::deg);

  if(potVal > val) {
    push.rotateFor(400, rotationUnits::deg, 75, velocityUnits::pct);
  }
  else if(potVal < val) {
    push.rotateFor(-400, rotationUnits::deg, 75, velocityUnits::pct);
  }
  /*else if(fabs(potVal - val) < 30) {
    push.spin(directionType::fwd, 0, velocityUnits::rpm);
  }*/
}

void scanLift() {
  double liftPos = lift.rotation(rotationUnits::deg);
  if(liftPos > 170 && liftPos < 800){
    push.setStopping(brakeType::hold);
    adjustTilt(570);
  }
  else{
    push.setStopping(brakeType::coast);
    adjustTilt(0);
  }
}

//Intake function 
void intake(int intakeSpeed) {
  //intaking the cube
  if(Controller1.ButtonR1.pressing()) { 
    intakeMotors.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
  }
  //releasing the cube
  else if(Controller1.ButtonR2.pressing()) { //pushes the cube out (into towers)
    intakeMotors.spin(directionType::fwd, 50, velocityUnits::pct);
  }
  //stops if neither button is being pressed
  else {
    if(push.rotation(rotationUnits::deg) < 800) {
      intakeMotors.stop(brakeType::hold);
    } else {
    intakeMotors.stop(brakeType::brake);
    }
  }
}

//Fast reverse intake function
void fastIntake() {
  if(Controller1.ButtonLeft.pressing()) { //pushes the cube out (into towers if far away)
    intakeMotors.spin(directionType::fwd, 100, velocityUnits::pct);
    }
}