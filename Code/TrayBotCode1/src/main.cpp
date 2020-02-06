
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// lFront               motor         4               
// lBack                motor         1               
// rFront               motor         9               
// rBack                motor         18              
// push                 motor         8               
// lift                 motor         7               
// leftIntake           motor         12              
// rightIntake          motor         6               
// pushPot              pot           A               
// ---- END VEXCODE CONFIGURED DEVICES ----
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

//initializes all of the potentiometers *USED AFTER TESTING (RESET VALUE)*
//called in the pre auton function, because that is before auton, or before the start of the match
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  intakeMotors.setStopping(brakeType::hold);
  lift.setStopping(brakeType::hold);

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
  //User control code here, inside the loop
  /*task a(liftButton); //when the lift button is pressed, lift goes up to specific tower height
  task b(driveSelector); //allows the driver to select the brake type of the motor
  task b(pushButton); //when the push button is pressed, the tray pushes cubes to become stacked
  task c(intakeRev); //buttons for when the intake is being reversed*/
  while (1) {
    //all of the parameters for all of these calls to the functions are just for testing, so remember to change them if it will be better
    printValues(); //prints values to the brain
    tankDrive(); 
    liftwT(100); //lift controls with tank drive enabled (instead of arcade drive)
    intake(100); //100 sensitivity for releasing the cubes and intaking cubes
    pushStack(870, 10); //normal push function, with desired as 835 degrees and speed as 8
    pullout(20,28); //drive speed is 20, and intake speed is 28 (need to make it faster)
    isPressed(); //all the button pressed functions
    fastIntake(); //for putting the cubes into towers at 100% velocity
    //scanLift(); //to move the tray forward after the lift is raised (testing)
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
