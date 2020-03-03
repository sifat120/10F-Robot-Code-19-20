#include "print.h"

using namespace vex;

//Motor degrees
float mDegrees = 0, lDegrees = 0, rDegrees = 0;

//All 3 constants for PID (global variables)
float kP;
float kI;
float kD;

//Other PID variables
double error = 0, prevError = 0, power = 0, integral = 0, derivative;

//Keeps track of time
double timeStep = 0;

void resetVariables() {
  error = 0, prevError = 0, power = 0, integral = 0, derivative = 0;
}

//Resets the timeStep variable
void resetTime() {
  timeStep = 0;
}

//moves a distance (in inches); forward if true, backward if false
void moveY(double distance, int driveSpeed, bool forward) {
  allDrive.resetRotation();
  mDegrees = (distance/(4*M_PI)) * 360;
  Brain.Screen.printAt(1, 20, "mDegrees: %f", mDegrees);
  error=mDegrees - allDrive.rotation(rotationUnits::deg);

  kP = 0.3, kI = 0.000, kD = 0.295; //kP = 0.3, kI = 0.05, kD = 0.1, 0.28
  while(error>45) { 
    Brain.Screen.printAt(1, 40, "Rotation: %f", allDrive.rotation(rotationUnits::deg));
    error = mDegrees - allDrive.rotation(rotationUnits::deg); 
    Brain.Screen.printAt(1, 60, "Error: %f", error);
    integral += error;
    if((allDrive.rotation(rotationUnits::deg) > mDegrees)) integral = 0; 
    if (error > 75) integral = 0; //test out the 50
    derivative = error - prevError;
    Brain.Screen.printAt(1, 80, "Derivative: %f", derivative);
    prevError = error;
    power = error*kP + integral*kI + derivative*kD;
    if(power > driveSpeed){
      power = driveSpeed;
    }
    if(forward == true){
      allDrive.spin(directionType::fwd, power, velocityUnits::pct);
    }
    else if(forward == false){
      allDrive.spin(directionType::rev, power, velocityUnits::pct);
    }
    wait(15, msec);
    timeStep += 15;
  }
  resetVariables();
}

//turns some degrees; right if true, left if false
void moveX(double normDegrees, bool right) {
  allDrive.resetRotation();
  mDegrees = sqrt(28000)/64 * normDegrees;
  
  kP = 0.3, kI = 0.00, kD = 0.0; //kP = 0.3, kI = 0.05, kD = 0.1
  while(mDegrees > allDrive.rotation(rotationUnits::deg)) { 
    error = mDegrees - allDrive.rotation(rotationUnits::deg);
    //integral += error;
    //if((allDrive.rotation(rotationUnits::deg) > mDegrees)) integral = 0; 
    //else if (error > 75) integral = 0; //test out the 360
    derivative = error - prevError;
    prevError = error;
    power = error*kP + /*integral*kI + */derivative*kD;
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
  allDrive.resetRotation();
  resetVariables();
}

void blockingY(double distance, int driveSpeed, bool forward, bool blocking) {
  moveY(distance,driveSpeed,forward);
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