#include "vex.h";

using namespace vex;

//Motor degrees
float mDegrees;

//All 3 constants for PID (global variables)
float kP;
float kI;
float kD;

//error value
int error;

void moveForward(double distance, bool blocking) {
  mDegrees = (distance/4*M_PI) * 360;
  if(blocking == true) {

  }
  else {

  }
}

void moveBackward(double distance, bool blocking) {
  mDegrees = (distance/4*M_PI) * 360;
}

void turnRight(double degrees, bool blocking) {
  mDegrees = sqrt(45000)/64 * degrees;
}

void turnLeft(double degrees, bool blocking) {
  mDegrees = sqrt(45000)/64 * degrees;
}