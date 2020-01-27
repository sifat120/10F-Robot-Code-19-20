/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// rFront               motor         1               
// lFront               motor         2               
// lBack                motor         3               
// rBack                motor         4               
// leftLift             motor         5               
// rightLift            motor         6               
// leftIntake           motor         7               
// rightIntake          motor         9               
// ---- END VEXCODE CONFIGURED DEVICES ----

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]         
// ---- END VEXCODE CONFIGURED DEVICES ----      

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

float mDegrees;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
//Driver control functions
 
//Drive function
void arcadeDrive(/*double sensitivity*/) {
  int threshold = 10; //Threshold for both joysticks
  int x = Controller1.Axis4.position(percentUnits::pct); //Left Joystick X-Axis 
  int y = Controller1.Axis3.position(percentUnits::pct); //Left Joystick Y-Axis

  if(abs(x) < threshold) x = 0;
  if(abs(y) < threshold) y = 0;

  /*int senseX = pow(x/100, sensitivity) * 100;
  int senseY = pow(y/100, sensitivity) * 100;*/

  lFront.spin(directionType::fwd, /*senseY + senseX*/y+x, velocityUnits::pct);
  lBack.spin(directionType::fwd, /*senseY + senseX*/y+x, velocityUnits::pct);
  rFront.spin(directionType::fwd, /*senseY - senseX*/y-x, velocityUnits::pct);
  rBack.spin(directionType::fwd, /*senseY - senseX*/y-x, velocityUnits::pct);
}

//Lift function
void lift() {
  int threshold = 10;
  int ry = Controller1.Axis2.position(percentUnits::pct); //Right Joystick Y-Axis

 if(abs(ry) < threshold) ry = 0;

  leftLift.spin(directionType::fwd, ry, velocityUnits::pct);
  rightLift.spin(directionType::fwd, ry, velocityUnits::pct);
}
 
//Intake function
void intake(int intakeSpeed) {
  if(Controller1.ButtonR1.pressing()){
    leftIntake.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
    rightIntake.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
  }

  else if(Controller1.ButtonR2.pressing()) {
    leftIntake.spin(directionType::fwd, 50, velocityUnits::pct);
    rightIntake.spin(directionType::fwd, 50, velocityUnits::pct);
  }

  else {
    leftIntake.stop(brakeType::brake);
    rightIntake.stop(brakeType::brake);
  }
}

//Autonomous movement functions

void moveForward(int distance, bool type) {
  mDegrees = (distance/(4*M_PI)) * 360;
  if(type == true) {
    lFront.rotateFor(mDegrees, rotationUnits::deg, false);
    lBack.rotateFor(mDegrees, rotationUnits::deg, false);
    rFront.rotateFor(mDegrees, rotationUnits::deg, false);
    rBack.rotateFor(mDegrees, rotationUnits::deg, true);
  }
  else {
    lFront.rotateFor(mDegrees, rotationUnits::deg, false);
    lBack.rotateFor(mDegrees, rotationUnits::deg, false);
    rFront.rotateFor(mDegrees, rotationUnits::deg, false);
    rBack.rotateFor(mDegrees, rotationUnits::deg, false);
  }
}

void moveBackward(int distance, bool type) {
  mDegrees = (distance/(4*M_PI)) * 360;
  if(type == true) {
    lFront.rotateFor(-mDegrees, rotationUnits::deg, false);
    lBack.rotateFor(-mDegrees, rotationUnits::deg, false);
    rFront.rotateFor(-mDegrees, rotationUnits::deg, false);
    rBack.rotateFor(-mDegrees, rotationUnits::deg, true);
  }
  else {
    lFront.rotateFor(-mDegrees, rotationUnits::deg, false);
    lBack.rotateFor(-mDegrees, rotationUnits::deg, false);
    rFront.rotateFor(-mDegrees, rotationUnits::deg, false);
    rBack.rotateFor(-mDegrees, rotationUnits::deg, false);
  }
}

void turnRight(int degrees, bool blocking) {
  mDegrees = sqrt(45000)/64 * degrees; //65365 in sqrt function
  if(blocking == true) {
    lFront.rotateFor(mDegrees, rotationUnits::deg, false);
    lBack.rotateFor(mDegrees, rotationUnits::deg, false);
    rFront.rotateFor(-mDegrees, rotationUnits::deg, false);
    rBack.rotateFor(-mDegrees, rotationUnits::deg, true);
  }
  else {
    lFront.rotateFor(mDegrees, rotationUnits::deg, false);
    lBack.rotateFor(mDegrees, rotationUnits::deg, false);
    rFront.rotateFor(-mDegrees, rotationUnits::deg, false);
    rBack.rotateFor(-mDegrees, rotationUnits::deg, false);
  }
}

void turnLeft(int degrees, bool blocking) {
  mDegrees = sqrt(45000)/64 * degrees;
  if(blocking == true) {
    lFront.rotateFor(-mDegrees, rotationUnits::deg, false);
    lBack.rotateFor(-mDegrees, rotationUnits::deg, false);
    rFront.rotateFor(mDegrees, rotationUnits::deg, false);
    rBack.rotateFor(mDegrees, rotationUnits::deg, true);
  }
  else {
    lFront.rotateFor(-mDegrees, rotationUnits::deg, false);
    lBack.rotateFor(-mDegrees, rotationUnits::deg, false);
    rFront.rotateFor(mDegrees, rotationUnits::deg, false);
    rBack.rotateFor(mDegrees, rotationUnits::deg, false);
  }
}

void lift(bool type, int degrees, bool blocking) {

  if(type == true) {
    if(blocking == true) {
      leftLift.rotateFor(degrees, rotationUnits::deg, false);
      rightLift.rotateFor(degrees, rotationUnits::deg, true);
    } else {
      leftLift.rotateFor(degrees, rotationUnits::deg, false);
      rightLift.rotateFor(degrees, rotationUnits::deg, false);
    }
  }

  else {
    if(blocking == true) {
      leftLift.rotateFor(-degrees, rotationUnits::deg, false);
      rightLift.rotateFor(-degrees, rotationUnits::deg, true);
    } else {
      leftLift.rotateFor(-degrees, rotationUnits::deg, false);
      rightLift.rotateFor(-degrees, rotationUnits::deg, false);
    }
  }

}

void rollersBack(int degrees, bool blocking) {
  leftIntake.rotateFor(-degrees, rotationUnits::deg, 100, velocityUnits::pct, blocking);
  rightIntake.rotateFor(-degrees, rotationUnits::deg, 100, velocityUnits::pct, blocking);
}
void rollersFront(int degrees, bool blocking) {
  leftIntake.rotateFor(degrees, rotationUnits::deg, 100, velocityUnits::pct, blocking);
  rightIntake.rotateFor(degrees, rotationUnits::deg, 100, velocityUnits::pct, blocking);
}

void redL() {
  moveForward(15, false);
  leftLift.rotateFor(90, rotationUnits::deg, false);
  rightLift.rotateFor(90, rotationUnits::deg, true);
  leftLift.rotateFor(-95, rotationUnits::deg, false);
  rightLift.rotateFor(-95, rotationUnits::deg, true);
  leftIntake.rotateFor(-3900, rotationUnits::deg, 100, velocityUnits::pct, false);
  rightIntake.rotateFor(-3900, rotationUnits::deg, 100, velocityUnits::pct, true);
  leftLift.rotateFor(20, rotationUnits::deg, false);
  rightLift.rotateFor(20, rotationUnits::deg, true);
  turnLeft(105,true);
  moveForward(34,true);
  leftLift.rotateFor(-40, rotationUnits::deg, false);
  rightLift.rotateFor(-40, rotationUnits::deg, true);
  leftIntake.rotateFor(2400, rotationUnits::deg, 37, velocityUnits::pct, false); //velocity = 100
  rightIntake.rotateFor(2400, rotationUnits::deg, 37, velocityUnits::pct, false);
  leftLift.rotateFor(250, rotationUnits::deg, false);
  rightLift.rotateFor(250, rotationUnits::deg, true);
  wait(120,msec);
  moveBackward(10, true);
}

void blueR() {
   moveForward(15, false);
  leftLift.rotateFor(110, rotationUnits::deg, false);
  rightLift.rotateFor(110, rotationUnits::deg, true);
  leftLift.rotateFor(-115, rotationUnits::deg, false);
  rightLift.rotateFor(-115, rotationUnits::deg, true);
  leftIntake.rotateFor(-4800, rotationUnits::deg, 100, velocityUnits::pct, false);
  rightIntake.rotateFor(-4800, rotationUnits::deg, 100, velocityUnits::pct, true);
  leftLift.rotateFor(20, rotationUnits::deg, false);
  rightLift.rotateFor(20, rotationUnits::deg, true);
  turnRight(115,true);
  moveForward(36,true);
  leftLift.rotateFor(-95, rotationUnits::deg, false);
  rightLift.rotateFor(-95, rotationUnits::deg, true);
  leftIntake.rotateFor(2400, rotationUnits::deg, 37, velocityUnits::pct, false); //velocity = 100
  rightIntake.rotateFor(2400, rotationUnits::deg, 37, velocityUnits::pct, false);
  leftLift.rotateFor(250, rotationUnits::deg, false);
  rightLift.rotateFor(250, rotationUnits::deg, true);
  wait(30, msec);
  moveBackward(15, true);
}

void redL2() {
  leftIntake.rotateFor(-2500, rotationUnits::deg, 100, velocityUnits::pct, false);
  rightIntake.rotateFor(-2500, rotationUnits::deg, 100, velocityUnits::pct, false);
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.

  blueR();

  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    //initialize between 1 - 3
    arcadeDrive();
    lift();
    intake(100);
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
