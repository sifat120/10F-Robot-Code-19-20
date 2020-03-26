#include "drive.cpp"

ADIPotentiometer anglerPot('A');

//HELPER FUNCTIONS
void setAngler(int power) {
    angler = power;
}

//DRIVER CONTROL FUNCTIONS
void setAnglerMotor() {
    //top trigger intakes, bottom trigger outtakes
    int anglerPower = 127 * (controller.get_digital(E_CONTROLLER_DIGITAL_UP) - controller.get_digital(E_CONTROLLER_DIGITAL_DOWN)); 
    setAngler(anglerPower);
}