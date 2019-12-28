using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor lFront;
extern motor lBack;
extern motor rFront;
extern motor rBack;
extern motor push;
extern motor lift;
extern motor leftIntake;
extern motor rightIntake;
extern pot pushPot;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );