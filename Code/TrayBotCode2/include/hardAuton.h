#include "pid.h"

//Autonomous movement functions
void moveForward(double distance, bool type) {
  mDegrees = (distance/(4*M_PI)) * 360;
  Brain.Screen.printAt(1, 80, "Mdegrees: %f", mDegrees);
  if(type == true) {
    leftDrive.rotateFor(mDegrees, rotationUnits::deg, false);
    rFront.rotateFor(mDegrees, rotationUnits::deg, false);
    rBack.rotateFor(mDegrees, rotationUnits::deg, true);
  }
  else {
    allDrive.rotateFor(mDegrees, rotationUnits::deg, false);
  }
}

void moveBackward(double distance, bool type) {
  mDegrees = (distance/(4*M_PI)) * 360;
  if(type == true) {
    leftDrive.rotateFor(-mDegrees, rotationUnits::deg, false);
    rFront.rotateFor(-mDegrees, rotationUnits::deg, false);
    rBack.rotateFor(-mDegrees, rotationUnits::deg, true);
  }
  else {
    allDrive.rotateFor(-mDegrees, rotationUnits::deg, false);
  }
}

void turnRight(double degrees, bool blocking) {
  mDegrees = sqrt(28000)/64 * degrees;
  if(blocking == true) {
    leftDrive.rotateFor(mDegrees, rotationUnits::deg, false);
    rFront.rotateFor(-mDegrees, rotationUnits::deg, false);
    rBack.rotateFor(-mDegrees, rotationUnits::deg, true);
  }
  else {
    leftDrive.rotateFor(mDegrees, rotationUnits::deg, false);
    rightDrive.rotateFor(-mDegrees, rotationUnits::deg, false);
  }
}

void turnLeft(double degrees, bool blocking) {
  mDegrees = sqrt(28000)/64 * degrees;
  if(blocking == true) {
    leftDrive.rotateFor(-mDegrees, rotationUnits::deg, false);
    rFront.rotateFor(mDegrees, rotationUnits::deg, false);
    rBack.rotateFor(mDegrees, rotationUnits::deg, true);
  }
  else {
    leftDrive.rotateFor(-mDegrees, rotationUnits::deg, false);
    rightDrive.rotateFor(mDegrees, rotationUnits::deg, false);
  }
}

/*void arcRight(double degrees, double radius, bool blocking) {
  lDegrees = (2*M_PI*degrees*(radius + 6.5))/360;
  rDegrees = (2*M_PI*degrees*(radius - 6.5))/360;
  if(blocking == true) {
    leftDrive.rotateFor(lDegrees,rotationUnits::deg,false);
    rightDrive.rotateFor(rDegrees,rotationUnits::deg,true);
  }
  else {
    leftDrive.rotateFor(lDegrees,rotationUnits::deg,false);
    rightDrive.rotateFor(rDegrees,rotationUnits::deg,false);
  }
}

void arcLeft(double degrees, double radius, bool blocking) {
  lDegrees = (2*M_PI*degrees*(radius - 6.5))/360;
  rDegrees = (2*M_PI*degrees*(radius + 6.5))/360;
  if(blocking == true) {
    leftDrive.rotateFor(lDegrees,rotationUnits::deg,false);
    rightDrive.rotateFor(rDegrees,rotationUnits::deg,true);
  }
  else {
    leftDrive.rotateFor(lDegrees,rotationUnits::deg,false);
    rightDrive.rotateFor(rDegrees,rotationUnits::deg,false);
  }
}*/

void intaking(double degrees, double speed, bool blocking) {
  if(blocking == true) {
    leftIntake.rotateFor(degrees, rotationUnits::deg, speed, velocityUnits::pct, false);
    rightIntake.rotateFor(degrees, rotationUnits::deg, speed, velocityUnits::pct, true);
  }
  else {
    intakeMotors.rotateFor(degrees, rotationUnits::deg, speed, velocityUnits::pct, false);
  }
}

//Autonomous helper functions

//function to deploy the robot
void deploy(){
  intakeMotors.rotateFor(directionType::fwd, 600, rotationUnits::deg, 100, velocityUnits::pct, false);
  lift.rotateFor(directionType::fwd, 1000, rotationUnits::deg, 100, velocityUnits::pct, false);
  moveBackward(2.5,false);
  wait(1.3,sec);
  lift.rotateFor(directionType::rev, 1000, rotationUnits::deg, 100, velocityUnits::pct, false);
  wait(1.3,sec);
//moveBackward(2,false);
}

//function to stack the cubes
void stack() {
  /*while(push.rotation(rotationUnits::deg) <= 718) { //pushes the tray to stacking position
    push.spin(directionType::fwd, (825 - push.rotation(rotationUnits::deg))/6,velocityUnits::pct);
    intakeMotors.spin(directionType::fwd, 5, percentUnits::pct);
  }*/
  push.rotateFor(directionType::fwd, 710, rotationUnits::deg, (730 - push.rotation(rotationUnits::deg))/10, velocityUnits::pct, false);
  intakeMotors.rotateFor(directionType::fwd, 370, rotationUnits::deg, 5.5, velocityUnits::pct, true);

}

void pulloutAuton() {
  allDrive.rotateFor(directionType::rev, 2000, rotationUnits::deg, 20, velocityUnits::pct, false);
  intakeMotors.rotateFor(directionType::fwd, 1500, rotationUnits::deg, 28.5, velocityUnits::pct, false);
}

//backup auton (only 1 cube)
void backupAuton() {
    moveBackward(17, false);
    wait(5,sec);
    moveForward(20, false);
    wait(3,sec);
}