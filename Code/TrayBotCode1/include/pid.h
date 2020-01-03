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

//Keeps track of time
double timeStep = 0;

//Resets the timeStep variable
void resetTime() {
  timeStep = 0;
}

//moves forward a distance (in inches)
void moveForward(double distance) {
  mDegrees = (distance/4*M_PI) * 360;
  
  kP = 0.3, kI = 0.05, kD = 0.1;
  while(mDegrees <= allDrive.rotation(degrees)) { 
    error = mDegrees - allDrive.rotation(degrees);
    integral += error;
    if((error = 0) || (allDrive.rotation(degrees) > mDegrees)) integral = 0; 
    else if (error > 540) integral = 0; //test out the 540
    derivative = error - prevError;
    prevError = error;
    power = error*kP + integral*kI + derivative*kD;
    allDrive.spin(directionType::fwd, power, velocityUnits::pct);
    wait(15, msec);
    timeStep += 15;
  }
  wait(timeStep, msec);
  resetTime();
}

//moves backward a distance (in inches)
void moveBackward(double distance, bool blocking) {
  mDegrees = (distance/4*M_PI) * 360;
}

//turns right some degrees
void turnRight(double degrees, bool blocking) {
  mDegrees = sqrt(45000)/64 * degrees;
}

//turns left some degrees
void turnLeft(double degrees, bool blocking) {
  mDegrees = sqrt(45000)/64 * degrees;
}