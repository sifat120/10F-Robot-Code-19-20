#include "vex.h"

using namespace vex;

//Motor groups (for drivetrain)
motor_group leftDrive(lFront,lBack);
motor_group rightDrive(rFront,rBack);
motor_group allDrive(lFront,lBack,rFront,rBack);

//Motor degrees
float mDegrees;

//All 3 constants for PID (global variables)
float kP;
float kI;
float kD;

//Other PID variables
double error, prevError, power, integral, derivative = 0;

//Keeps track of time
double timeStep = 0;

//Resets the timeStep variable
void resetTime() {
  timeStep = 0;
}

float turnDegreeToRotations(float degree) {
  float rotationsPerDegree = 0; //This has to be tested first
  float rotations = degree * rotationsPerDegree;
  return rotations;
}

//moves a distance (in inches); forward if true, backward if false
void moveY(double distance, bool forward) {
  mDegrees = (distance/4*M_PI) * 360;
  allDrive.resetRotation();

  kP = 0.3, kI = 0.05, kD = 0.1;
  while(mDegrees > allDrive.rotation(degrees)) { 
    error = mDegrees - allDrive.rotation(degrees);
    integral += error;
    if((error = 0) || (allDrive.rotation(degrees) > mDegrees)) integral = 0; 
    else if (error > 540) integral = 0; //test out the 540
    derivative = error - prevError;
    prevError = error;
    power = error*kP + integral*kI + derivative*kD;
    if(forward == true){
      allDrive.spin(directionType::fwd, power, velocityUnits::pct);
    } else {
      allDrive.spin(directionType::rev, power, velocityUnits::pct);
    }
    wait(15, msec);
    timeStep += 15;
  }
  wait(timeStep, msec);
  resetTime();
}

//turns some degrees; right if true, left if false
void moveX(double normDegrees, bool right) {
  mDegrees = turnDegreeToRotations(normDegrees);
  if(right == true){
    leftDrive.spinFor(directionType::fwd, mDegrees, rotationUnits::deg);
    rightDrive.spinFor(directionType::rev, mDegrees, rotationUnits::deg);
  } else {
    leftDrive.spinFor(directionType::rev, mDegrees, rotationUnits::deg);
    rightDrive.spinFor(directionType::fwd, mDegrees, rotationUnits::deg);
    }
  /*allDrive.resetRotation();
  
  kP = 0.3, kI = 0.05, kD = 0.1;
  while(mDegrees > allDrive.rotation(degrees)) { 
    error = mDegrees - allDrive.rotation(degrees);
    integral += error;
    if((error = 0) || (allDrive.rotation(degrees) > mDegrees)) integral = 0; 
    else if (error > 360) integral = 0; //test out the 360
    derivative = error - prevError;
    prevError = error;
    power = error*kP + integral*kI + derivative*kD;
    if(right == true){
      leftDrive.spin(directionType::fwd, power, velocityUnits::pct);
      rightDrive.spin(directionType::rev, power, velocityUnits::pct);
    } else {
      leftDrive.spin(directionType::rev, power, velocityUnits::pct);
      rightDrive.spin(directionType::fwd, power, velocityUnits::pct);
    }
    wait(15, msec);
    timeStep += 15;
  }
  wait(timeStep, msec);
  resetTime();
  */
}