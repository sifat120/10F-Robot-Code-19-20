#include "vex.h";

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

void moveForward(double distance, bool blocking) {
  mDegrees = (distance/4*M_PI) * 360;
  
  kP = 0.3, kI = 0.05, kD = 0.1;
  while(true) { //replace true with mDegrees != allDrive.rotation(degrees)
    error = mDegrees - allDrive.rotation(degrees);
    integral += error;
    if((error = 0) || (allDrive.rotation(degrees) > mDegrees)) integral = 0; 
    else if (error > 540) integral = 0; //test out the 540
    derivative = error - prevError;
    prevError = error;
    power = error*kP + integral*kI + derivative*kD;
    wait(15, msec);
  }

  if(blocking == true) {
  
  }
  else {

  }
}

void moveBackward(double distance, bool blocking) {
  mDegrees = (distance/4*M_PI) * 360;
  if(blocking == true) {

  }
  else {

  }
}

void turnRight(double degrees, bool blocking) {
  mDegrees = sqrt(45000)/64 * degrees;
  if(blocking == true) {

  }
  else {

  }
}

void turnLeft(double degrees, bool blocking) {
  mDegrees = sqrt(45000)/64 * degrees;
  if(blocking == true) {

  }
  else {

  }
}