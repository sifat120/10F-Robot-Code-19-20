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

  void blueR2() {
    deploy();
    intaking(-6500,100,false);
    blockingY(15,63,true,true);
    turnLeft(90,true);
    blockingY(30,70,true,true);
    Brain.Screen.printAt(1, 100, "Loop ended");
    turnRight(90,true);
  }

  void redL2() {
    deploy();
    intaking(-6500,100,false);
    blockingY(18,63,true,true);
    turnRight(90,true);
    blockingY(30,70,true,true);
    turnRight(40,true);
    blockingY(10,55,true,true);
    blockingY(10,55,false,true);
    intaking(150,30,false);
    turnRight(115,true);
    blockingY(30,100,true,true);
    stack();
    pulloutAuton();
  }

  void blueL2() {
    deploy();
    intaking(-7200,100,false);
    blockingY(37,72,true,true);
    turnRight(50,true);
    blockingY(35.5,72,false,true);
    turnLeft(50,true);
    blockingY(46,52,true,true);
    intaking(150,40,false);
    blockingY(44,100,false,true);
    turnLeft(132,true);
    blockingY(5,100,true,false);
    wait(0.1,sec);
    stack();
    pulloutAuton();
  }
  void redR2() {
    deploy();
    intaking(-7200,100,false);
    blockingY(42,61,true,true);
    turnLeft(50,true);
    blockingY(35.5,72,false,true);
    turnRight(50,true);
    blockingY(50,59,true,true);
    turnRight(170,true);
  }

  void blueL3() {
    deploy();
    intaking(-3900,100,false);
    blockingY(43,50,true,true);
    turnRight(45,true);
    blockingY(11.5,45,true,true);
    blockingY(11.5,45,false,true);
    turnRight(181,true);
    intaking(150,30,false);
    blockingY(36,68,true,true);
    stack();
    pulloutAuton();
  }

  void redR3() {
    deploy();
    intaking(-3900,100,false);
    blockingY(43,50,true,true);
    turnLeft(45,true);
    blockingY(11.5,45,true,true);
    blockingY(11.5,45,false,true);
    turnRight(204,true);
    intaking(150,25,false);
    blockingY(28.25,68,true,true);
    stack();
    pulloutAuton();
  }