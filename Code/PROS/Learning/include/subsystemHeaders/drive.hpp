#include "globals.hpp"

//HELPER FUNCTIONS
void setDrive(int left, int right);

void resetDriveEncoders();

double avgDriveEncoderValue();

//DRIVER CONTROL FUNCTIONS
void setDriveMotors();

//AUTONOMOUS FUNCTIONS
void translate(int distance, int voltage);