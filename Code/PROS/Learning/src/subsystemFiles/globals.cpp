#include "main.h"

//Motors
Motor lift(1,E_MOTOR_GEARSET_36,false,E_MOTOR_ENCODER_COUNTS);
//1 is port number
//E_MOTOR_GEARSET_18 signifies that it is a 200 rpm motor
//false means that the motor is not reversed
//E_MOTOR_ENCODER_COUNTS represents the encoder values(gets ticks for now)
Motor angler(2,E_MOTOR_GEARSET_36,false,E_MOTOR_ENCODER_COUNTS);
Motor intakeLeft(3,E_MOTOR_GEARSET_18,false,E_MOTOR_ENCODER_COUNTS);
Motor intakeRight(4,E_MOTOR_GEARSET_18,true,E_MOTOR_ENCODER_COUNTS);
Motor lFront(5,E_MOTOR_GEARSET_18,false,E_MOTOR_ENCODER_COUNTS);
Motor lBack(6,E_MOTOR_GEARSET_18,false,E_MOTOR_ENCODER_COUNTS);
Motor rFront(7,E_MOTOR_GEARSET_18,true,E_MOTOR_ENCODER_COUNTS);
Motor rBack(8,E_MOTOR_GEARSET_18,true,E_MOTOR_ENCODER_COUNTS);

//Controller
Controller controller(E_CONTROLLER_MASTER);
//sets up controller (E_CONTROLLER_MASTER signifies that it is the master controller)

//Miscellaneous