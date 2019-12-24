/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// lFront               motor         1               
// lBack                motor         2               
// rFront               motor         3               
// rBack                motor         4               
// push                 motor         5               
// lift                 motor         6               
// leftIntake           motor         7               
// rightIntake          motor         8               
// pushPot              pot           A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "pid.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
//Motor degrees (used for autonomous)
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
 
//Arcade Drive function
void arcadeDrive(double sensitivity) {
  int threshold = 10; //Threshold for both joysticks
  int x = Controller1.Axis4.position(percentUnits::pct); //Left Joystick X-Axis 
  int y = Controller1.Axis3.position(percentUnits::pct); //Left Joystick Y-Axis

  if(abs(x) < threshold) x = 0;
  if(abs(y) < threshold) y = 0;

  //sense x and sense y are for sensitivities
  int senseX = pow(x/100, sensitivity) * 100;
  int senseY = pow(y/100, sensitivity) * 100;

  lFront.spin(directionType::fwd, /*y + x*/ senseY + senseX, velocityUnits::pct);
  lBack.spin(directionType::fwd, /*y + x*/ senseY + senseX, velocityUnits::pct);
  rFront.spin(directionType::fwd, /*y - x*/ senseY - senseX, velocityUnits::pct);
  rBack.spin(directionType::fwd, /*y - x*/ senseY - senseX, velocityUnits::pct);
}

//Tank Drive function
void tankDrive(double sensitivity) {
  int threshold = 10; //Threshold for both joysticks
  int ly = Controller1.Axis3.position(percentUnits::pct);  //Left Joystick Y-Axis
  int ry = Controller1.Axis2.position(percentUnits::pct); //Right Joystick Y-Axis

  if(abs(ly) < threshold) ly = 0;
  if(abs(ry) < threshold) ry = 0;
  int sensely = pow(ly/100, sensitivity) * 100;
  int sensery = pow(ry/100, sensitivity) * 100;

  lFront.spin(directionType::fwd, sensely, velocityUnits::pct);
  lBack.spin(directionType::fwd, sensely, velocityUnits::pct);
  rFront.spin(directionType::fwd, sensery, velocityUnits::pct);
  rBack.spin(directionType::fwd, sensery, velocityUnits::pct);
}

//Lift function
void liftN() {
  int threshold = 10;
  int ry = Controller1.Axis2.position(percentUnits::pct); //Right Joystick Y-Axis

 if(abs(ry) < threshold) ry = 0;

  lift.spin(directionType::fwd, ry, velocityUnits::pct);
}

//Lift function when tank drive function is enabled
void liftwT(int liftSpeed) {
  //Going up
  if(Controller1.ButtonL1.pressing()) {
    lift.spin(directionType::rev, liftSpeed, velocityUnits::pct);
  }
  //Going down
  else if(Controller1.ButtonL2.pressing()) {
    lift.spin(directionType::fwd, liftSpeed, velocityUnits::pct);
  }
  //stopped if no button is being pressed
  else {
    lift.stop(brakeType::brake);
  }
} 
 
//Intake function
void intake(int intakeSpeed) {
  //intaking the cube
  if(Controller1.ButtonR1.pressing()){
    leftIntake.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
    rightIntake.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
  }
  //releasing the cube
  else if(Controller1.ButtonR2.pressing()) {
    leftIntake.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
    rightIntake.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
  }
  //stops if neither button is being pressed
  else {
    leftIntake.stop(brakeType::brake);
    rightIntake.stop(brakeType::brake);
  }
}

//Normal (preset) push mechanism
void pushNorm(int pushSpeed) {
  //Pushing to stack the cubes
  if(Controller1.ButtonA.pressing()) {
    push.spin(directionType::fwd, pushSpeed, velocityUnits::pct);
  }
  //Retracting to push back the tray to normal intaking position
  else if(Controller1.ButtonB.pressing()) {
    push.spin(directionType::rev, 75, velocityUnits::pct);
  }
  //stops if neither button is being pressed
  else {
    push.stop(brakeType::brake);
  }
}

//How the push mechanism starts slowing down as it reaches the desired target value (as a percentage)
void pushMechanism(int desired, int speed) {
  //p part in pid (proportional)
  while(pushPot.value(percentUnits::pct) != desired){
    push.spin(directionType::fwd, (desired - pushPot.value(percentUnits::pct))/speed, velocityUnits::pct);
  }
}

//Actually calling the pushMechanism function when the up button is pressed
int pushButton() {
  while(true) {
    if(Controller1.ButtonUp.pressing()) {
      pushMechanism(50, 5); //remember to change these values Desired: 50, Speed: 5
    }
  }
  return(0);
}

//Literally controls the lift
void controlLift(int x) {
  lift.rotateFor(x,rotationUnits::deg, true);
}

//Controls the lift when certain buttons are pressed (x and y)
int liftButton() {
  while(true) {
    if(Controller1.ButtonX.pressing()) {
      controlLift(50); //Small tower height *TESTING*
    }
    else if(Controller1.ButtonY.pressing()) {
      controlLift(100); //Large tower height *TESTING*
    }
  }
  //returns nothing, because it just does stuff
  return(0);
}

//initializes all of the potentiometers *USED AFTER TESTING (RESET VALUE)*
//called in the pre auton function, because that is before auton, or before the start of the match
void initPot() {}

//prints push potentiometer values to the brain, that may be useful for specific things
void printPushPotValues() {
  //For the push potentiometer values *USE THIS FOR THE BUTTONS*
  Brain.Screen.printAt(1, 20, "Push Potentiometer Values:");
  Brain.Screen.printAt(1, 40, "Rotation: %f degrees", pushPot.value(rotationUnits::deg));
  Brain.Screen.printAt(1, 60, "Percent: %f %", pushPot.value(percentUnits::pct));
  Brain.Screen.printAt(1, 80, "Analog: %f mV", pushPot.value(analogUnits::mV));
}

//prints lift potentiometer values to the brain, that may be useful for specific things
/*void printLiftPotValues() {
  //For the lift potentiometer values *USE THIS FOR THE BUTTONS*
  Brain.Screen.printAt(400, 20, "Lift Potentiometer Values:");
  Brain.Screen.printAt(400, 40, "Rotation: %f degrees", liftPot.value(rotationUnits::deg));
  Brain.Screen.printAt(400, 60, "Percent: %f %", liftPot.value(percentUnits::pct));
  Brain.Screen.printAt(400, 80, "Analog: %f mV", liftPot.value(analogUnits::mV));
}*/

//Autonomous movement functions
void moveForward(double distance, bool type) {
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

void moveBackward(double distance, bool type) {
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

void turnRight(double degrees, bool blocking) {
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

void turnLeft(double degrees, bool blocking) {
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

//Autonomous reference functions
void redL2() {
  moveForward(18.0, false);
  lift.rotateFor(-20, rotationUnits::deg, true);
  leftIntake.rotateFor(-2700, rotationUnits::deg, 100, velocityUnits::pct, false);
  rightIntake.rotateFor(-2700, rotationUnits::deg, 100, velocityUnits::pct, true);
  turnLeft(90.0,true);
  moveForward(19.0,false);
  leftIntake.rotateFor(-3300, rotationUnits::deg, 100, velocityUnits::pct, false);
  rightIntake.rotateFor(-3300, rotationUnits::deg, 100, velocityUnits::pct, true);
  lift.rotateFor(18, rotationUnits::deg, true);
  turnLeft(49.0,true);
  moveForward(18.75,true);
  lift.rotateFor(-40, rotationUnits::deg, true);
  leftIntake.rotateFor(2600, rotationUnits::deg, 23, velocityUnits::pct, false);
  rightIntake.rotateFor(2600, rotationUnits::deg, 23, velocityUnits::pct, false);
  moveForward(0.6, false);
  lift.rotateFor(310, rotationUnits::deg, 8, velocityUnits::pct, true);
  wait(120,msec);
  moveBackward(15, true);
}

void blueR2() {
  moveForward(18.0, false);
  lift.rotateFor(-20, rotationUnits::deg, true);
  leftIntake.rotateFor(-2800, rotationUnits::deg, 100, velocityUnits::pct, false);
  rightIntake.rotateFor(-2800, rotationUnits::deg, 100, velocityUnits::pct, true);
  turnRight(92.0,true);
  moveForward(19.75,false);
  leftIntake.rotateFor(-3300, rotationUnits::deg, 100, velocityUnits::pct, false);
  rightIntake.rotateFor(-3300, rotationUnits::deg, 100, velocityUnits::pct, true);
  turnRight(49.45,true);
  moveForward(19.15,true);
  lift.rotateFor(-60, rotationUnits::deg, true);
  leftIntake.rotateFor(2400, rotationUnits::deg, 21, velocityUnits::pct, false); //velocity = 30
  rightIntake.rotateFor(2400, rotationUnits::deg, 21, velocityUnits::pct, false);
  moveForward(0.6, false);
  lift.rotateFor(320, rotationUnits::deg, 8, velocityUnits::pct, true);
  wait(120,msec);
  moveBackward(15, true);

//Actual autonomous functions for different parts of the field
  /*void redL() {

  }

  void redR() {

  }
  
  void blueL() {

  }

  void blueR() {

  }*/

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
  task a(liftButton);
  task b(pushButton);
  while (1) {
    /*printLiftPotValues();*/ //prints lift potentiometer values
    printPushPotValues(); //prints push potentiometer values
    tankDrive(1.6); //sensitivity = 1.6; sensitivity should be between 1.1(most sensitive) - 2(least sensitive)
    liftwT(75); //lift controls with tank drive enabled (instead of arcade drive)
    intake(100); //100 sensitivity (for picking up the cubes and for releasing the cubes)

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
