#include "globals.cpp"

//HELPER FUNCTIONS
void setDrive(int left, int right){
    lFront = left;
    lBack = left;
    rFront = right;
    rBack = right;
}

//DRIVER CONTROL FUNCTIONS
void setDriveMotors() {
    int threshold = 10;

    int leftJoystick = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y); //joysticks range from -127 to +127
    int rightJoystick = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y); //joysticks range from -127 to +127

    if(abs(leftJoystick) < threshold) leftJoystick = 0;
    if(abs(rightJoystick) < threshold) rightJoystick = 0;

    setDrive(leftJoystick, rightJoystick);
}