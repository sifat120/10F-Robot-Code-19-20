using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor rFront;
extern motor lFront;
extern motor lBack;
extern motor rBack;
extern motor leftLift;
extern motor rightLift;
extern motor leftIntake;
extern motor rightIntake;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );