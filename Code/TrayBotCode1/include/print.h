#include "tasks.h"

//Prints necessary values to the screen
void printValues() {
  //For the push value
  Brain.Screen.printAt(1, 20, "Push Rotation: %f degrees", push.rotation(rotationUnits::deg));
  //For the lift value
  Brain.Screen.printAt(1, 40, "Lift Rotation: %f degrees", lift.rotation(rotationUnits::deg));
  //For the push potentiometer value
  Brain.Screen.printAt(1, 60, "Push Pot Rotation: %f degrees", pushPot.value(rotationUnits::deg));
}