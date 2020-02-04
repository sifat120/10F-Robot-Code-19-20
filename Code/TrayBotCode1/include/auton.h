#include "hardAuton.h"

//Actual autonomous functions for different parts of the field
  void redL() { //2 cubes (not done)
    deploy();
    moveForward(1,true);
    moveBackward(1,true);
    intaking(-2800,100,false);
    moveForward(9.0,true);
    moveForward(9.0,true);
    turnLeft(135,true);
    moveForward(32,false);
    wait(5.0,sec);
    intaking(2400,50,false);
    wait(2,sec);
    moveBackward(10,true);
  }

  void redR() { //5 cubes (not done)
    deploy();
    intaking(-5600,100,false);
    moveForward(35,true);
    turnRight(151.1,true);
    moveForward(25.25,false);
    wait(3.7,sec);
    stack();
  }
  
  void blueL() { //5 cubes (not done)
    deploy();
    intaking(-5600,100,false);
    moveForward(35,true);
    turnLeft(151.1,true);
    moveForward(25.25,false);
    wait(3.7,sec);
    stack();
  }

  void blueR() {
    deploy();
    moveForward(1,true);
    moveBackward(1,true);
    intaking(-2800,100,false);
    moveForward(9.0,true);
    moveForward(9.0,true);
    turnRight(135,true);
    moveForward(32,false);
    wait(5.0,sec);
    intaking(2400,50,false);
    wait(2,sec);
    moveBackward(10,true);
  }