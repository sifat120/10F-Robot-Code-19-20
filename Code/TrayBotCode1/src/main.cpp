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

//Added the intake motors to be a motor group
motor_group intakeMotors(leftIntake,rightIntake);

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
float mDegrees1; //Motor degrees (used for autonomous)

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
  int x = Controller1.Axis4.position(pct); //Left Joystick X-Axis 
  int y = Controller1.Axis3.position(pct); //Left Joystick Y-Axis

  if(abs(x) < threshold) x = 0;
  if(abs(y) < threshold) y = 0;

  //senseX and senseY are for sensitivities
  int senseX = pow(x/100, sensitivity) * 100;
  int senseY = pow(y/100, sensitivity) * 100;

  leftDrive.spin(directionType::fwd,  senseY + senseX, velocityUnits::pct);
  rightDrive.spin(directionType::fwd,  senseY - senseX, velocityUnits::pct);
}

//Tank Drive function
void tankDrive(double sensitivity) {
  int threshold = 10; //Threshold for both joysticks
  int ly = Controller1.Axis3.position(pct);  //Left Joystick Y-Axis
  int ry = Controller1.Axis2.position(pct); //Right Joystick Y-Axis

  if(abs(ly) < threshold) ly = 0;
  if(abs(ry) < threshold) ry = 0;

  //sensely and sensery are for sensitivities
  int sensely = pow(ly/100, sensitivity) * 100;
  int sensery = pow(ry/100, sensitivity) * 100;

  leftDrive.spin(directionType::fwd, sensely, velocityUnits::pct);
  rightDrive.spin(directionType::fwd, sensery, velocityUnits::pct);
}

//Lift function (dw about this, because it is for arcade drive)
void liftN() {
  int threshold = 10;
  int ry = Controller1.Axis2.position(pct); //Right Joystick Y-Axis

 if(abs(ry) < threshold) ry = 0;

  lift.spin(directionType::fwd, ry, velocityUnits::pct);
}

//Lift function when tank drive function is enabled
void liftwT(int liftSpeed) {
  //Going up
  if(Controller1.ButtonL1.pressing()) { //lift is going down
    lift.spin(directionType::rev, liftSpeed, velocityUnits::pct);
  }
  //Going down
  else if(Controller1.ButtonL2.pressing()) { //lift is going up
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
  if(Controller1.ButtonR1.pressing()){ //intakes the cube in
    intakeMotors.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
  }
  //releasing the cube
  else if(Controller1.ButtonR2.pressing()) { //pushes the cube out (into towers)
    intakeMotors.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
  }
  //stops if neither button is being pressed
  else {
    intakeMotors.stop(brakeType::brake);
  }
}

//Normal (preset) push mechanism
void pushNorm(int pushSpeed) {
  //Pushing to stack the cubes
  if(Controller1.ButtonA.pressing()) { //pushes the tray to stacking position (use this for now)
    push.spin(directionType::fwd, pushSpeed, velocityUnits::pct);
  }
  //Retracting to push back the tray to normal intaking position
  else if(Controller1.ButtonB.pressing()) {
    push.spin(directionType::rev, 75, velocityUnits::pct); //tray comes back to normal
    //Remember to change 75 (speed), because that is only a testing value!
  }
  //stops if neither button is being pressed
  else {
    push.stop(brakeType::brake);
  }
}

//How the push mechanism starts slowing down as it reaches the desired target value (as a percentage)
void pushMechanism(int desired, int speed) {
  //p part in pid (proportional)
  while(pushPot.value(rotationUnits::deg) != desired){
    push.spin(directionType::fwd, (desired - pushPot.value(pct))/speed, velocityUnits::pct);
  }
}

//Actually calling the pushMechanism function when the up button is pressed
int pushButton() {
  while(true) {
    int counter = 0;
    if(Controller1.ButtonUp.pressing()) {
      counter++;
      switch(counter){
        case 1: 
        pushMechanism(50, 5); //remember to change these values Desired: 50 (percentage), Speed: 5
        case 2:
        push.spinFor(directionType::rev, 50, rotationUnits::deg, 75, velocityUnits::pct); //rotation units(50) has to be same as push mechanism desired
        //If the speed when coming back is too fast, lower the velocity units pct (75)
        counter = 0;
      }
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
      controlLift(280); //Small tower height *TESTING*
    }
    else if(Controller1.ButtonY.pressing()) {
      controlLift(360); //Large tower height *TESTING*
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
  //For the push potentiometer values *USE THIS FOR THE BUTTONS THAT DO TASKS*
  Brain.Screen.printAt(1, 20, "Push Potentiometer Values:");
  Brain.Screen.printAt(1, 40, "Rotation: %f degrees", pushPot.value(rotationUnits::deg));
  Brain.Screen.printAt(1, 60, "Percent: %f %", pushPot.value(pct));
  Brain.Screen.printAt(1, 80, "Analog: %f mV", pushPot.value(analogUnits::mV));
}

//prints lift potentiometer values to the brain, that may be useful for specific things
/*void printLiftPotValues() { 
  //For the lift potentiometer values *USE THIS FOR THE BUTTONS THAT DO TASKS*
  Brain.Screen.printAt(400, 20, "Lift Potentiometer Values:");
  Brain.Screen.printAt(400, 40, "Rotation: %f degrees", liftPot.value(rotationUnits::deg));
  Brain.Screen.printAt(400, 60, "Percent: %f %", liftPot.value(pct));
  Brain.Screen.printAt(400, 80, "Analog: %f mV", liftPot.value(analogUnits::mV));
}*/

//Autonomous movement functions
void moveForward1(double distance, bool type) {
  mDegrees1 = (distance/(4*M_PI)) * 360;
  if(type == true) {
    leftDrive.rotateFor(mDegrees1, rotationUnits::deg, false);
    rFront.rotateFor(mDegrees1, rotationUnits::deg, false);
    rBack.rotateFor(mDegrees1, rotationUnits::deg, true);
  }
  else {
    allDrive.rotateFor(mDegrees1, rotationUnits::deg, false);
  }
}

void moveBackward1(double distance, bool type) {
  mDegrees1 = (distance/(4*M_PI)) * 360;
  if(type == true) {
    leftDrive.rotateFor(-mDegrees1, rotationUnits::deg, false);
    rFront.rotateFor(-mDegrees1, rotationUnits::deg, false);
    rBack.rotateFor(-mDegrees1, rotationUnits::deg, true);
  }
  else {
    allDrive.rotateFor(-mDegrees1, rotationUnits::deg, false);
  }
}

void turnRight1(double degrees, bool blocking) {
  mDegrees1 = sqrt(45000)/64 * degrees;
  if(blocking == true) {
    leftDrive.rotateFor(mDegrees1, rotationUnits::deg, false);
    rFront.rotateFor(-mDegrees1, rotationUnits::deg, false);
    rBack.rotateFor(-mDegrees1, rotationUnits::deg, true);
  }
  else {
    leftDrive.rotateFor(mDegrees1, rotationUnits::deg, false);
    rightDrive.rotateFor(-mDegrees1, rotationUnits::deg, false);
  }
}

void turnLeft1(double degrees, bool blocking) {
  mDegrees1 = sqrt(45000)/64 * degrees;
  if(blocking == true) {
    leftDrive.rotateFor(-mDegrees1, rotationUnits::deg, false);
    rFront.rotateFor(mDegrees1, rotationUnits::deg, false);
    rBack.rotateFor(mDegrees1, rotationUnits::deg, true);
  }
  else {
    leftDrive.rotateFor(-mDegrees1, rotationUnits::deg, false);
    rightDrive.rotateFor(mDegrees1, rotationUnits::deg, false);
  }
}

void intaking(double degrees, double speed, bool blocking) {
  if(blocking == true) {
    leftIntake.rotateFor(degrees, rotationUnits::deg, speed, velocityUnits::pct, false);
    rightIntake.rotateFor(degrees, rotationUnits::deg, speed, velocityUnits::pct, true);
  }
  else {
    intakeMotors.rotateFor(degrees, rotationUnits::deg, speed, velocityUnits::pct, false);
  }
}

//Autonomous reference functions (from previous comp)
//If the last parameter of the call to the function is set to true, then that means that it is a blocking command, 
//which means that all the commands before it and itself will have to finish before the autonomous period moves on
//(before the next commands are executed)
//If it is false, then it will happen simultaneously, because it is a non-blocking command
void redL2() {
  moveForward1(18.0, false); //18.0 represents inches
  lift.rotateFor(-20, rotationUnits::deg, true); //-20 refers to the amount the lift will rotate, in degrees
  intaking(-2700,100,true); //-2700 is the amount it will rotate, 100 is velocity (percentage(pct), true means that it is a blocking command
  turnLeft1(90.0,true); //turns left 90.0 degrees
  moveForward1(19.0,false); // 19.0 represents inches
  intaking(-3300,100,true);
  lift.rotateFor(18, rotationUnits::deg, true);
  turnLeft1(49.0,true);
  moveForward1(18.75,true);
  lift.rotateFor(-40, rotationUnits::deg, true);
  intaking(2600,23,false); //velocity is slower here (23), so that it stacks easily
  moveForward1(0.6, false);
  lift.rotateFor(310, rotationUnits::deg, 8, velocityUnits::pct, true);
  wait(120,msec);
  moveBackward1(15, true);
}

void blueR2() {
  moveForward1(18.0, false);
  lift.rotateFor(-20, rotationUnits::deg, true);
  intaking(-2800,100,true);
  turnRight1(92.0,true);
  moveForward1(19.75,false);
  intaking(-3300,100,true);
  turnRight1(49.45,true);
  moveForward1(19.15,true);
  lift.rotateFor(-60, rotationUnits::deg, true);
  intaking(2400,21,false);
  moveForward1(0.6, false);
  lift.rotateFor(320, rotationUnits::deg, 8, velocityUnits::pct, true);
  wait(120,msec);
  moveBackward1(15, true);

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
  initPot(); //initializes the push potentiometer value

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
  moveY(15,true); //moves forward 15 inches
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
    //all of the parameters for all of these calls to the functions are just for testing, so remember to change them if it will be better
    /*printLiftPotValues();*/ //prints lift potentiometer values
    printPushPotValues(); //prints push potentiometer values
    tankDrive(1.6); //sensitivity = 1.6; sensitivity should be between 1.1(most sensitive) - 2(least sensitive); set to 1 if you want it back to normal
    liftwT(75); //lift controls with tank drive enabled (instead of arcade drive)
    intake(100); //100 sensitivity (for picking up the cubes and for releasing the cubes)
    pushNorm(50); //normal push function, and pushes the tray at 50% speed if button is pressed
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
