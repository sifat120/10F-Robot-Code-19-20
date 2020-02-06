#include "lift&intake.h"

//Normal (preset) push mechanism
void pushStack(int desired, double speed) {
  //Pushing to stack the cubes
  if(Controller1.ButtonUp.pressing() && push.rotation(rotationUnits::deg) <= 850) { //pushes the tray to stacking position (use this for now)
    push.spin(directionType::fwd, (desired - push.rotation(rotationUnits::deg))/speed, velocityUnits::pct);
    intakeMotors.spin(directionType::fwd, 5, percentUnits::pct);
  }
  //Retracting to push back the tray to normal intaking position
  else if(Controller1.ButtonDown.pressing() && push.rotation(rotationUnits::deg) >= 0) {
    push.spin(directionType::rev, 80, velocityUnits::pct); //tray comes back to normal
  }
  //stops if neither button is being pressed
  else {
    push.stop(brakeType::hold);
  }
}