#include "angler.cpp"

//HELPER FUNCTIONS
void setIntake(int power) {
    intakeLeft = power;
    intakeRight = power;
}

//DRIVER CONTROL FUNCTIONS
void setIntakeMotors() {
    //top trigger intakes, bottom trigger outtakes
    int intakePower = 127 * (controller.get_digital(E_CONTROLLER_DIGITAL_R2) - controller.get_digital(E_CONTROLLER_DIGITAL_R1)); 
    setIntake(intakePower);
}