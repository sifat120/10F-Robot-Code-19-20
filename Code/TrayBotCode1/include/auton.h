#include "skills.h"

//Actual autonomous functions for different parts of the field
  void redL() { //2 cubes (not done)
    deploy();
    intaking(-6500,100,false);
    moveForward(20,true);
    turnRight(92, true);
    moveForward(14, true);
    turnRight(155,true);
    moveForward(11,false);
    intaking(150,40,false);
    wait(2,sec);
    stack();
    wait(1.5,sec);
    pulloutAuton();
  }

  void redR() { //5 cubes (not done)
    deploy();
    intaking(-6300,100,false);
    moveForward(40, true);
    turnRight(153,true);
    moveForward(38,false);
    intaking(150,40,false);
    wait(3,sec);
    stack();
    wait(1.25,sec);
    pulloutAuton();
  }
  
  void blueL() { //5 cubes (not done)
    deploy();
    intaking(-6300,100,false);
    moveForward(40, true);
    turnLeft(155.85,true);
    moveForward(38,false);
    intaking(150,40,false);
    wait(3,sec);
    stack();
    wait(1.25,sec);
    pulloutAuton();
  }

  void blueR() {
    deploy();
    intaking(-5500,100,false);
    moveForward(20,true);
    turnRight(92, true);
    moveForward(18, true);
    turnRight(30,true);
    moveForward(9,false);
    intaking(150,40,false);
    wait(0.75,sec);
    stack();
    wait(1.75,sec);
    pulloutAuton();
  }