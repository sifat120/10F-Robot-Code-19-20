#include "lift&intake.h"

//Normal (preset) push mechanism
void pushStack(int desired, double speed) {
  //Pushing to stack the cubes
  if(Controller1.ButtonUp.pressing() && push.rotation(rotationUnits::deg) <= 845) { //pushes the tray to stacking position (use this for now)
    push.spin(directionType::fwd, (desired - push.rotation(rotationUnits::deg))/speed, velocityUnits::pct);
  }
  //Retracting to push back the tray to normal intaking position
  else if(Controller1.ButtonDown.pressing()) {
    push.spin(directionType::rev, 75, velocityUnits::pct); //tray comes back to normal
    //Remember to change 75 (speed), because that is only a testing value!
  }
  //stops if neither button is being pressed
  else {
    push.stop(brakeType::hold);
  }
}