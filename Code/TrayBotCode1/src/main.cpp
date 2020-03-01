/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "auton.h"

using namespace vex;

// A global instance of competition
competition Competition;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pullout(double driveSpeed, double intakeSpeed) {
  if(Controller1.ButtonX.pressing()) {
    allDrive.spin(directionType::rev, driveSpeed, velocityUnits::pct);
    intakeMotors.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
  }
}

//initializes all of the potentiometers *USED AFTER TESTING (RESET VALUE)*
//called in the pre auton function, because that is before auton, or before the start of the match
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  intakeMotors.setStopping(brakeType::hold);
  lift.setStopping(brakeType::hold);
  lift.resetRotation();
  allDrive.resetRotation();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------`------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  //backupAuton();
  //redL();
  //redR();
  //blueL();
  //blueR();
  //moveForward(15,true);
  intaking(-4500,100,false);
  blockingY(55,true,true);
  intaking(150,40,false);
  wait(2.5,sec);
  stack();
  wait(1.5,sec);
  pulloutAuton();
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
  task a(quickStack); //Makes a quick stack of 8 or less cubes
  task b(buttonPressedNew); //should move the lift when button is pressed
  while (1) {
    //all of the parameters for all of these calls to the functions are just for testing, so remember to change them if it will be better
    printValues(); //prints values to the brain
    tankDrive(); //for the drive
    liftwT(100); //lift controls with tank drive enabled
    intake(100); //100 sensitivity for releasing the cubes and intaking cubes
    pushStack(1000, 14); //normal push function, with desired as 1000 degrees and speed as 14
    pullout(40,48.5); //original drive speed is 20, and intake speed is 28.5
    fastOuttake(); //for putting the cubes into towers at 100% velocity
    //fastStack(); //for stacking fast (potentially the middle tower)
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
