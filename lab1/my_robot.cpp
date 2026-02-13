#include "my_robot.h"
#include <Arduino.h>
#include <Pololu3piPlus32U4.h>
//Macros for calculations. No magic numbers!
#define MILLISECONDS_IN_SECOND 1000
#define MILLIMETERS_IN_METER 1000
//The right wheel on our robot runs slightly faster than the left, this is to compensate for that
#define RIGHT_WHEEL_COMPENSATION 0.95
using namespace Pololu3piPlus32U4;

Motors motors;
//default constructor
MyRobot::MyRobot() : speed(0) {}

MyRobot::MyRobot(float initialSpeed) : speed(initialSpeed){}

void MyRobot::setBaseSpeed(float newSpeed){
  speed = newSpeed;
}

void MyRobot::turnLeft(float duration){
  //To turn left, left motor and right motor need equal speed while left goes backward and right goes forward
  motors.setSpeeds((int) (-speed * MILLIMETERS_IN_METER), (int) (speed * MILLIMETERS_IN_METER * RIGHT_WHEEL_COMPENSATION));
  delay(duration * MILLISECONDS_IN_SECOND);
  Halt();
}

void MyRobot::turnRight(float duration){
  //To turn right, left motor and right motor need equal speed while left goes forward and right goes backward
  motors.setSpeeds((int) (speed * MILLIMETERS_IN_METER), (int) (-speed * MILLIMETERS_IN_METER * RIGHT_WHEEL_COMPENSATION));
  delay(duration * MILLISECONDS_IN_SECOND);
  Halt();
}

void MyRobot::Halt(){
  //sets both motors speed to 0 in order to stop
  motors.setSpeeds(0, 0);
}

void MyRobot::moveForward(float distance){
  //In order to move straight forward both motors need to go the same speed
  motors.setSpeeds((int) (speed * MILLIMETERS_IN_METER), (int) (speed * MILLIMETERS_IN_METER * RIGHT_WHEEL_COMPENSATION));
  //gives the neccessary duration in milliseconds
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}

void MyRobot::moveBackward(float distance){
  //To go straight backward both motors need to go the same speed in reverse
  motors.setSpeeds((int) (-speed * MILLIMETERS_IN_METER), (int) (-speed * MILLIMETERS_IN_METER * RIGHT_WHEEL_COMPENSATION));
  //gives the neccessary duration in milliseconds
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();

}

void MyRobot::moveForwardTurningLeft(float distance){
  //To go forward while turning left, the right motor needs to go faster than the left motor while both are going forward
  motors.setSpeeds((int) (speed * MILLIMETERS_IN_METER * 0.5), (int) (speed * MILLIMETERS_IN_METER * RIGHT_WHEEL_COMPENSATION));
  //gives the neccessary duration in milliseconds
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}

void MyRobot::moveForwardTurningRight(float distance){
  //To go forward while turning right, the left motor needs to go faster than the right motor while both are going forward
  motors.setSpeeds((int) (speed * MILLIMETERS_IN_METER), (int) (speed * MILLIMETERS_IN_METER * 0.5 * RIGHT_WHEEL_COMPENSATION));
  //gives the neccessary duration in milliseconds
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}

void MyRobot::moveBackwardTurningLeft(float distance){
  //To go backward while turning left, the left motor needs to go faster than the right motor while both are in reverse
  motors.setSpeeds((int) (-speed * MILLIMETERS_IN_METER), (int) (-speed * MILLIMETERS_IN_METER * 0.5 * RIGHT_WHEEL_COMPENSATION));
  //gives the neccessary duration in milliseconds
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}

void MyRobot::moveBackwardTurningRight(float distance){
  //To go backward while turning right, the right motor needs to go faster than the left motor while both are in reverse
  motors.setSpeeds((int) (-speed * MILLIMETERS_IN_METER * 0.5), (int) (-speed * MILLIMETERS_IN_METER * RIGHT_WHEEL_COMPENSATION));
  //gives the neccessary duration in milliseconds
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}
