#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor lFront = motor(PORT1, ratio18_1, false);
motor lBack = motor(PORT2, ratio18_1, false);
motor rFront = motor(PORT3, ratio18_1, false);
motor rBack = motor(PORT4, ratio18_1, false);
motor push = motor(PORT5, ratio36_1, false);
motor lift = motor(PORT6, ratio18_1, false);
motor leftIntake = motor(PORT7, ratio18_1, false);
motor rightIntake = motor(PORT8, ratio18_1, false);
pot pushPot = pot(Brain.ThreeWirePort.A);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}