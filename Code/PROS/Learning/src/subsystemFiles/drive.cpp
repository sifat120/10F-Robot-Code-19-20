#include "globals.cpp"

ADIGyro gyro('B', 1.05);

int mDegrees;

//HELPER FUNCTIONS
void setDrive(int left, int right){
    lFront = left;
    lBack = left;
    rFront = right;
    rBack = right;
}

void resetDriveEncoders() {
    lFront.tare_position(); //resets the drive encoders
    lBack.tare_position();
    rFront.tare_position();
    rBack.tare_position();
}

double avgDriveEncoderValue() {
    return (fabs(lFront.get_position()) +
           fabs(lBack.get_position()) +  
           fabs(rFront.get_position()) +
           fabs(rBack.get_position()))/4;
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

//AUTONOMOUS FUNCTIONS
void translate(int distance, int voltage){
    //define a direction based on distance provided
    int direction = abs(distance)/distance;

    //define the amount of degrees the motor has to turn based on the distance (in inches)
    int mDegrees = (distance/(4*M_PI)) * 360;

    //reset motor encoders
    resetDriveEncoders();
    gyro.reset();

    //drive forward until units are reached (this is also where pid can go)
    while(avgDriveEncoderValue() < abs(mDegrees)){
        setDrive(voltage * direction + gyro.get_value(), voltage * direction - gyro.get_value()); //direction is either positive or negative one which signifies direction of motor
        delay(10);
    }

    //brief brake
    setDrive(-10 * direction,-10 * direction); //needs to go in opposite direction a little to stop motor since it has momentum
    delay(50);

    //set drive back to normal
    setDrive(0,0);
}

void rotate(int degrees, int voltage) {
    //define direction, based on the units provided
    int direction = abs(degrees)/degrees;
    //resetting the gyro
    gyro.reset();
    //turn until units are reached
    setDrive(-voltage*direction, voltage*direction);
    while(fabs(gyro.get_value()) < abs(degrees * 10)) {
        delay(10);
    }
    delay(100);
    if(fabs(gyro.get_value()) > abs(degrees * 10)){
        while(fabs(gyro.get_value()) > abs(degrees * 10)) {
        setDrive(0.5*voltage*direction, 0.5*-voltage*direction);
        delay(10);
        }
    }
    else if(fabs(gyro.get_value()) < abs(degrees * 10)){
        while(fabs(gyro.get_value()) < abs(degrees * 10)) {
        setDrive(0.5*-voltage*direction, 0.5*voltage*direction);
        delay(10);
        }
    }
    //reset drive to 0
    setDrive(0,0);
}