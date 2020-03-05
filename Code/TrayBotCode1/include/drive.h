#include "vex.h"

//Motor groups (for drivetrain)
motor_group leftDrive(lFront,lBack);
motor_group rightDrive(rFront,rBack);
motor_group allDrive(lFront,lBack,rFront,rBack);

//Motor groups (for intakes)
motor_group intakeMotors(leftIntake,rightIntake);

//Driver control functions
 
//Arcade Drive function
void arcadeDrive(double sensitivity) {
  int threshold = 10; //Threshold for both joysticks
  int x = Controller1.Axis4.position(percentUnits::pct); //Left Joystick X-Axis 
  int y = Controller1.Axis3.position(percentUnits::pct); //Left Joystick Y-Axis

  if(abs(x) < threshold) x = 0;
  if(abs(y) < threshold) y = 0;

  leftDrive.spin(directionType::fwd,  y + x, velocityUnits::pct);
  rightDrive.spin(directionType::fwd,  y - x, velocityUnits::pct);
}

//Tank Drive function
void tankDriveSense(double sensitivity) {
  double threshold = 10; //Threshold for both joysticks
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

void pullout() {
  if(Controller1.ButtonX.pressing()) {
    while(Controller1.ButtonX.pressing()) {
      intakeMotors.spin(directionType::fwd, 49.5, velocityUnits::pct);
      while(push.rotation(rotationUnits::deg) >= 0) {
        push.spin(directionType::rev, 80, velocityUnits::pct);
        allDrive.spin(directionType::rev, 20, velocityUnits::pct);
      }
    }
    intakeMotors.stop(brakeType::hold);
    push.stop(brakeType::hold);
  }
}