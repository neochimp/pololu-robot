#ifndef MY_ROBOT_H
#define MY_ROBOT_H
#include <Pololu3piPlus32U4.h>
using namespace Pololu3piPlus32U4;
//my_robot header stuff here

class MyRobot {
public:
  //constructor
  MyRobot();
  MyRobot(float initialSpeed);
  
  //member functions
  void setBaseSpeed(float newSpeed);
  void turnLeft(float duration);
  void turnRight(float duration);
  void Halt();
  void myDelay(float duration_ms);
  void moveForward(float distance);
  void moveBackward(float distance);
  void moveForwardTurningRight(float distance);
  void moveForwardTurningLeft(float distance);
  void moveBackwardTurningRight(float distance);
  void moveBackwardTurningLeft(float distance);

private:
  float speed;
};
  
#endif
