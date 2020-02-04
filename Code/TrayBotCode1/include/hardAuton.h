#include "pid.h"

//Autonomous movement functions
void moveForward(double distance, bool type) {
  mDegrees = (distance/(4*M_PI)) * 360;
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
  intakeMotors.spinFor(directionType::fwd, 800, rotationUnits::deg, 100, velocityUnits::pct, true);
  wait(1.25,sec);
  moveBackward(2,false);
}

//function to stack the cubes
void stack() {
  intaking(500,40,true);
  wait(0.35,sec);
  push.rotateFor(480, rotationUnits::deg, 45, velocityUnits::pct, true);
  allDrive.spinFor(directionType::rev, 1000, rotationUnits::deg, 20, velocityUnits::pct);
  intakeMotors.spinFor(directionType::fwd, 2000, rotationUnits::deg, 28, velocityUnits::pct);
}

//backup auton (only 1 cube)
void backupAuton() {
    moveBackward(17, false);
    wait(5,sec);
    moveForward(20, false);
    wait(3,sec);
}