#include "lift&intake.h"

//For the stacking to be fast and smooth (p-loop)
void stackNorm(int desired, double speed) {
  int power = 0;
  int error = desired - push.rotation(rotationUnits::deg);
  double kP = speed;
  while(push.rotation(rotationUnits::deg) < desired) {
    error = desired - push.rotation(rotationUnits::deg);
    power = error * kP;
    push.spin(directionType::fwd, power, velocityUnits::pct);
  }
}

//Normal (preset) push mechanism
void pushStack(int desired, double speed) {
  //Pushing to stack the cubes
  if(Controller1.ButtonUp.pressing() && push.rotation(rotationUnits::deg) <= 850) { //pushes the tray to stacking position (use this for now)
    stackNorm(desired,speed);
    if(push.rotation(rotationUnits::deg) <= 350) {
      intakeMotors.spin(directionType::rev, 10, percentUnits::pct);
    } else {
      intakeMotors.spin(directionType::fwd, 7, percentUnits::pct); //Was 5
    }
  }
  //Retracting to push back the tray to normal intaking position
  else if(Controller1.ButtonDown.pressing() && push.rotation(rotationUnits::deg) >= 15) {
    push.spin(directionType::rev, 80, velocityUnits::pct); //tray comes back to normal
  }
  //stops if neither button is being pressed
  else {
    push.stop(brakeType::hold);
  }
}