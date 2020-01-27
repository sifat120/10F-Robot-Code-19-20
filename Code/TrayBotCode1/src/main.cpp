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
// leftIntake           motor         3               
// rightIntake          motor         6               
// pushPot              pot           A               
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// leftIntake           motor         2               
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
  int x = Controller1.Axis4.position(percentUnits::pct); //Left Joystick X-Axis 
  int y = Controller1.Axis3.position(percentUnits::pct); //Left Joystick Y-Axis

  if(abs(x) < threshold) x = 0;
  if(abs(y) < threshold) y = 0;

  //senseX and senseY are for sensitivities
  //int senseX = pow(x/100, sensitivity) * 100;
  //int senseY = pow(y/100, sensitivity) * 100;

  leftDrive.spin(directionType::fwd,  y + x, velocityUnits::pct);
  rightDrive.spin(directionType::fwd,  y - x, velocityUnits::pct);
}

//Tank Drive function
void tankDriveSense(double sensitivity) {
  double threshold = 5; //Threshold for both joysticks
  double ly = Controller1.Axis3.position(percentUnits::pct); //Left Joystick Y-Axis
  double ry = Controller1.Axis2.position(percentUnits::pct); //Right Joystick Y-Axis

  if(fabs(ly) < threshold) ly = 0;
  if(fabs(ry) < threshold) ry = 0;
  
  double sensely = pow(fabs(ly)/100, sensitivity) * 100;
  double sensery = pow(fabs(ry)/100, sensitivity) * 100;
  
  if(ly < 0) {
    sensely *= -1;
  }
  if(ry < 0) {
    sensery *= -1;
  }

  leftDrive.spin(directionType::fwd, sensely, velocityUnits::pct);
  rightDrive.spin(directionType::fwd, sensery, velocityUnits::pct);
}

void tankDrive() {
  int threshold = 10; //Threshold for both joysticks
  int ly = Controller1.Axis3.position(percentUnits::pct); //Left Joystick Y-Axis
  int ry = Controller1.Axis2.position(percentUnits::pct); //Right Joystick Y-Axis

  if(abs(ly) < threshold) ly = 0;
  if(abs(ry) < threshold) ry = 0;

  leftDrive.spin(directionType::fwd, ly, velocityUnits::pct);
  rightDrive.spin(directionType::fwd, ry, velocityUnits::pct);
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
    //push.rotateFor(directionType::fwd, 60, rotationUnits::deg);
  }
  //stopped if no button is being pressed
  else {
    lift.stop(brakeType::hold);
  }
} 

void adjustTilt(int val) {
  double potVal = lift.rotation(rotationUnits::deg);

  if(potVal > val) {
    push.spin(directionType::fwd, 200, velocityUnits::rpm);
  }
  else if(potVal < val) {
    push.spin(directionType::rev, 200, velocityUnits::rpm);
  }
  else if(fabs(potVal - val) < 30) {
    push.spin(directionType::fwd, 0, velocityUnits::rpm);
  }
}

void scanLift() {
  double liftPos = lift.rotation(rotationUnits::deg);
  if(liftPos > 170 && liftPos < 800){
    push.setStopping(brakeType::hold);
    adjustTilt(570);
  }
  else{
    push.setStopping(brakeType::coast);
    adjustTilt(0);
  }
}
 
//Intake function (forward)
void intake(int intakeSpeed) {
  //intaking the cube
  if(Controller1.ButtonR1.pressing()) { 
    intakeMotors.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
  }
  //releasing the cube
  else if(Controller1.ButtonR2.pressing()) { //pushes the cube out (into towers)
    intakeMotors.spin(directionType::fwd, 50, velocityUnits::pct);
  }
  //stops if neither button is being pressed
  else {
    /*if(push.rotation(rotationUnits::deg) > 400) {
      intakeMotors.stop(brakeType::brake);
    } else {*/
    intakeMotors.stop(brakeType::hold);
    //}
  }
}

//Intake functions where button is pressed and it just starts spinning (reverse)
int intakeRev() {
  int counter = 0;
  while(true) {
    if(Controller1.ButtonDown.pressing()) {
      while(Controller1.ButtonDown.pressing()) {}
      counter++;
    }
    switch(counter){
      case 1: //Intaking the cubes
        intakeMotors.spin(directionType::rev, 100, velocityUnits::pct);
        break;
      case 2: 
        intakeMotors.stop(brakeType::brake);
        counter = 0;
        break;
      default:
        intakeMotors.stop(brakeType::brake);
        break;
    }
  }
  //returns nothing, because it just does stuff
  return(0);
}

//Normal (preset) push mechanism
void pushNorm(int desired, int speed) {
  //Pushing to stack the cubes
  if(Controller1.ButtonUp.pressing()) { //pushes the tray to stacking position (use this for now)
    push.spin(directionType::fwd, 35, velocityUnits::pct);
    /*while(pushPot.value(rotationUnits::deg) > desired){
      push.spin(directionType::fwd, (desired - pushPot.value(pct))/speed, velocityUnits::pct);
    }*/
  }
  //Retracting to push back the tray to normal intaking position
  else if(Controller1.ButtonDown.pressing()) {
    push.spin(directionType::rev, 75, velocityUnits::pct); //tray comes back to normal
    //Remember to change 75 (speed), because that is only a testing value!
  }
  //stops if neither button is being pressed
  else {
    push.stop(brakeType::brake);
  }
}

void checkPush(int value) {
  if(pushPot.value(rotationUnits::deg) < value) {
    intakeMotors.setStopping(brakeType::hold);
  } else {
    intakeMotors.setStopping(brakeType::brake);
  }
}

//How the push mechanism starts slowing down as it reaches the desired target value (as a percentage)
void pushMechanism(int desired, int speed) {
  //p part in pid (proportional)
  while(pushPot.value(rotationUnits::deg) > desired){
    push.spin(directionType::fwd, (desired - pushPot.value(pct))/speed, velocityUnits::pct);
  }
}

//Actually calling the pushMechanism function when the up button is being pressed
int pushButton() {
  int counter = 0;
  while(true) {
    if(Controller1.ButtonUp.pressing()) {
      while(Controller1.ButtonUp.pressing()) {}
      counter++;
    }
    switch(counter){
        case 1: 
        pushMechanism(50, 1); //remember to change these values Desired: 50 (degrees), Speed: 5
        break;
        case 2:
        push.spinFor(directionType::rev, 50, rotationUnits::deg, 75, velocityUnits::pct); //rotation units(50) has to be same as push mechanism desired
        //If the speed when coming back is too fast, lower the velocity units pct (75)
        counter = 0;
        break;
        default:
        push.stop(brakeType::brake);
        break;
      }
  }
  //returns nothing, because it just does stuff
  return(0);
}

//Literally controls the lift
void controlLift(int x) {
  lift.rotateFor(x,rotationUnits::deg, true);
}

//Controls the lift when certain buttons are pressed (x and y)
int liftButton() {
  while(true) {
    if(Controller1.ButtonDown.pressing()) {
      controlLift(280); //Small tower height *TESTING*
    }
    else if(Controller1.ButtonUp.pressing()) {
      controlLift(360); //Large tower height *TESTING*
    }
  }
  //returns nothing, because it just does stuff
  return(0);
}

void driverHold() {
  allDrive.stop(brakeType::hold);
}

void driverCoast() {
  allDrive.stop(brakeType::coast);
}

//select the type of brake on the drive
int driveSelector() {
  int counter = 0;
  while(true) {
    if(Controller1.ButtonX.pressing()) {
      while(Controller1.ButtonX.pressing()) {}
      counter++;
    }
    switch(counter){
        case 1: 
        allDrive.setStopping(brakeType::hold);
        counter = 0;
        break;
        default:
        allDrive.setStopping(brakeType::coast);
        break;
      }
  }
  //returns nothing, because it just does stuff
  return(0);
}

void pullout(double driveSpeed, double intakeSpeed) {
  if(Controller1.ButtonY.pressing()) {
    allDrive.spin(directionType::rev, driveSpeed, velocityUnits::pct);
    intakeMotors.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
  }
}

void checkTray() {
  if(push.rotation(rotationUnits::deg) > 400) {
    intakeMotors.setStopping(brakeType::brake);
  }
}

void setCube() {
  intakeMotors.spinFor(directionType::fwd, 20, rotationUnits::deg, 15, velocityUnits::pct);
}

void isPressed() {
  Controller1.ButtonA.pressed(driverHold);
  Controller1.ButtonB.pressed(driverCoast);
  Controller1.ButtonRight.pressed(setCube);
}

//initializes all of the potentiometers *USED AFTER TESTING (RESET VALUE)*
//called in the pre auton function, because that is before auton, or before the start of the match

//prints push potentiometer values to the brain, that may be useful for specific things
void printValues() {
  //For the push potentiometer values *USE THIS FOR THE BUTTONS THAT DO TASKS*
  Brain.Screen.printAt(1, 20, "Rotation: %f degrees", push.rotation(rotationUnits::deg));
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
void moveForward(double distance, bool type) {
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

void moveBackward(double distance, bool type) {
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

void turnRight(double degrees, bool blocking) {
  mDegrees1 = sqrt(28000)/64 * degrees;
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

void turnLeft(double degrees, bool blocking) {
  mDegrees1 = sqrt(28000)/64 * degrees;
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
  moveForward(18.0, false); //18.0 represents inches
  lift.rotateFor(-20, rotationUnits::deg, true); //-20 refers to the amount the lift will rotate, in degrees
  intaking(-2700,100,true); //-2700 is the amount it will rotate, 100 is velocity (percentage(pct), true means that it is a blocking command
  turnLeft(90.0,true); //turns left 90.0 degrees
  moveForward(19.0,false); // 19.0 represents inches
  intaking(-3300,100,true);
  lift.rotateFor(18, rotationUnits::deg, true);
  turnLeft(49.0,true);
  moveForward(18.75,true);
  lift.rotateFor(-40, rotationUnits::deg, true);
  intaking(2600,23,false); //velocity is slower here (23), so that it stacks easily
  moveForward(0.6, false);
  lift.rotateFor(310, rotationUnits::deg, 8, velocityUnits::pct, true);
  wait(120,msec);
  moveBackward(15, true);
}

void blueR2() {
  moveForward(18.0, false);
  lift.rotateFor(-20, rotationUnits::deg, true);
  intaking(-2800,100,true);
  turnRight(92.0,true);
  moveForward(19.75,false);
  intaking(-3300,100,true);
  turnRight(49.45,true);
  moveForward(19.15,true);
  lift.rotateFor(-60, rotationUnits::deg, true);
  intaking(2400,21,false);
  moveForward(0.6, false);
  lift.rotateFor(320, rotationUnits::deg, 8, velocityUnits::pct, true);
  wait(120,msec);
  moveBackward(15, true);
}
//Autonomous helper functions

//function to deploy the robot
void deploy(){
  intakeMotors.spinFor(directionType::fwd, 800, rotationUnits::deg, 100, velocityUnits::pct, true);
  wait(1.25,sec);
  moveBackward(2,false);
}

//function to stack the cubes
void stack() {

}

//backup auton (only 1 cube)
void backupAuton() {
    moveBackward(17, false);
    wait(5,sec);
    moveForward(20, false);
    wait(3,sec);
}

//Actual autonomous functions for different parts of the field
  void redL() {
    moveForward(1,true);
    moveBackward(1,true);
    intaking(-2800,100,false);
    moveForward(9.0,true);
    moveForward(9.0,true);
    turnLeft(135,true);
    moveForward(32,false);
    wait(5.0,sec);
    intaking(2400,50,false);
    wait(2,sec);
    moveBackward(10,true);
  }

  void redR() {
    intaking(-5600,100,false);
    moveForward(35,true);
    turnRight(151.1,true);
    moveForward(25.25,false);
    wait(3.7,sec);
    intaking(500,40,true);
    wait(0.35,sec);
    push.rotateFor(480, rotationUnits::deg, 45, velocityUnits::pct, true);
    allDrive.spinFor(directionType::rev, 1000, rotationUnits::deg, 20, velocityUnits::pct);
    intakeMotors.spinFor(directionType::fwd, 2000, rotationUnits::deg, 28, velocityUnits::pct);
  }
  
  void blueL() {
    intaking(-5600,100,false);
    moveForward(35,true);
    turnLeft(151.1,true);
    moveForward(25.25,false);
    wait(3.7,sec);
    intaking(500,40,true);
    wait(0.35,sec);
    push.rotateFor(480, rotationUnits::deg, 45, velocityUnits::pct, true);
    allDrive.spinFor(directionType::rev, 1000, rotationUnits::deg, 20, velocityUnits::pct);
    intakeMotors.spinFor(directionType::fwd, 2000, rotationUnits::deg, 28, velocityUnits::pct);
  }

  void blueR() {
  }

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
  backupAuton();
  deploy();
  //redL();
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
    pushNorm(23, 1); //normal push function, and pushes the tray at 50% speed if button is being pressed
    pullout(20,28); //drive speed is 20, and intake speed is 28
    isPressed(); //all the button pressed functions
    //checkTray();
    if(Controller1.ButtonLeft.pressing()) { //pushes the cube out (into towers if far away)
    intakeMotors.spin(directionType::fwd, 100, velocityUnits::pct);
    }
    //scanLift();
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
