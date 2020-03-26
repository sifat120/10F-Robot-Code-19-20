#include "intake.cpp"

//HELPER FUNCTIONS
void setLift(int power) {
    lift = power;
}

//DRIVER CONTROL FUNCTIONS
void setLiftMotor() {
    //top trigger intakes, bottom trigger outtakes
    int liftPower = 127 * (controller.get_digital(E_CONTROLLER_DIGITAL_L1) - controller.get_digital(E_CONTROLLER_DIGITAL_L2)); 
    setLift(liftPower);
}