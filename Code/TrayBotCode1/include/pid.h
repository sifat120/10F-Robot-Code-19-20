#include "print.h"

using namespace vex;

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
}

//turns some degrees; right if true, left if false
void moveX(double normDegrees, bool right) {
  mDegrees = sqrt(45000)/64 * normDegrees;
  allDrive.resetRotation();
  
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
}

void blockingY(double distance, bool forward, bool blocking) {
  moveY(distance,forward);
  if(blocking == true) {
    wait(timeStep, msec);
    resetTime();
  } else {
    resetTime();
  }
}

void blockingX(double normDegrees, bool right, bool blocking) {
  moveX(normDegrees,right);
  if(blocking == true) {
    wait(timeStep, msec);
    resetTime();
  } else {
    resetTime();
  }
}