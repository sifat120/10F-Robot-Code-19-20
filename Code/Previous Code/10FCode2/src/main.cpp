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
// rightIntake          motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----      

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
int threshold = 10; //Threshold for both joysticks
int x = Controller1.Axis4.position(percentUnits::pct); //Left Joystick X-Axis 
int y = Controller1.Axis3.position(percentUnits::pct); //Left Joystick Y-Axis
int ry = Controller1.Axis2.position(percentUnits::pct); //Right Joystick Y-Axis
double mDegrees;
int suppAngle;
//Driver control functions
 
//Drive function
void arcadeDrive() {
 // if(abs(x) < threshold) x = 0;
  //if(abs(y) < threshold) y = 0;

  int senseX = 0;//pow(x/100, sensitivity) * 100;
  int senseY = 0;//pow(y/100, sensitivity) * 100;

  lFront.spin(directionType::fwd, senseY + senseX, velocityUnits::pct);
  lBack.spin(directionType::fwd, senseY + senseX, velocityUnits::pct);
  rFront.spin(directionType::fwd, senseY - senseX, velocityUnits::pct);
  rBack.spin(directionType::fwd, senseY - senseX, velocityUnits::pct);
}

//Lift function
void lift(/*int liftSpeed*/) {
//testing
   //int liftMax = LiftPot.value(percentUnits::pct);

  /*if(Controller.ButtonA.pressing()) {
      while(liftMax > 0 && liftMax < 75) {
        leftLift.spin(vex::directionType::fwd, liftSpeed, velocityUnits::pct);
        rightLift.spin(vex::directionType::fwd, liftSpeed, velocityUnits::pct);
      }
    }*/

 if(abs(ry) < threshold) ry = 0;

  leftLift.spin(directionType::fwd, ry, velocityUnits::pct);
  rightLift.spin(directionType::fwd, ry, velocityUnits::pct);
}
 
//Intake function
void intake(int intakeSpeed) {
  if(Controller1.ButtonR1.pressing()){
    leftIntake.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
    rightIntake.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
  }

  else if(Controller1.ButtonR2.pressing()) {
    leftIntake.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
    rightIntake.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
  }

  else {
    leftIntake.stop(brakeType::brake);
    rightIntake.stop(brakeType::brake);
  }
  /*if(Controller.ButtonA.pressed()} {

  }
  else if(Controller.ButtonB.pressed()) {

  }*/
}

//Autonomous movement functions

void moveForward(int dist) {
  mDegrees = (dist/(4*M_PI)) * 360;
 /* lFront.startRotateFor(directionType::fwd, mDegrees, rotationUnits::deg, false);
  lBack.startRotateFor(directionType::fwd, mDegrees, rotationUnits::deg, false);
  rFront.startRotateFor(directionType::fwd, mDegrees, rotationUnits::deg, false);
  rBack.startRotateFor(directionType::fwd, mDegrees, rotationUnits::deg, false);*/
}
 
void moveBackward(int dist) {
  mDegrees = (dist/(4*M_PI)) * 360;
 /* lFront.startRotateFor(directionType::rev, mDegrees, rotationUnits::deg, false);
  lBack.startRotateFor(directionType::rev, mDegrees, rotationUnits::deg, false);
  rFront.startRotateFor(directionType::rev, mDegrees, rotationUnits::deg, false);
  rBack.startRotateFor(directionType::rev, mDegrees, rotationUnits::deg, false);*/
}
 
void turnRight(int degrees) {
  suppAngle = 180 - degrees;
 /* lFront.startRotateFor(directionType::fwd, mDegrees, rotationUnits::deg, false);
  lBack.startRotateFor(directionType::fwd, mDegrees, rotationUnits::deg, false);
  rFront.startRotateFor(directionType::rev, mDegrees, rotationUnits::deg, false);
  rBack.startRotateFor(directionType::rev, mDegrees, rotationUnits::deg, false);*/
}
 
void turnLeft(int degrees) {
  /*suppAngle = 180 - degrees;
  lFront.startRotateFor(directionType::rev, mDegrees, rotationUnits::deg, false);
  lBack.startRotateFor(directionType::rev, mDegrees, rotationUnits::deg, false);
  rFront.startRotateFor(directionType::fwd, mDegrees, rotationUnits::deg, false);
  rBack.startRotateFor(directionType::fwd, mDegrees, rotationUnits::deg, false);*/
}
 
//Different Instances of Autonomous Periods

void blueLeft() {

}

void blueRight() {
 
}

void redLeft() {
 
}
 
void redRight() {
 
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
    //arcadeDrive();
    lift();
    intake(50);
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
