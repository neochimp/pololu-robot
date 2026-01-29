#include "my_robot.h"
#include <Arduino.h>
#include <Pololu3piPlus32U4Motors.h>
//Macros for calculations. No magic numbers!
#define MILLISECONDS_IN_SECOND 1000
#define MILLIMETERS_IN_METER 1000

//default constructor
MyRobot::MyRobot() : speed(0) {}

MyRobot::MyRobot(float initialSpeed) : speed(initialSpeed){}

void MyRobot::setBaseSpeed(float newSpeed){
  speed = newSpeed;
}

void MyRobot::turnLeft(float duration){
  Pololu3piPlus32U4::Motors::setSpeeds((int) -speed * MILLIMETERS_IN_METER, (int) speed * MILLIMETERS_IN_METER);
  delay(duration * MILLISECONDS_IN_SECOND);
  Halt();
}

void MyRobot::turnRight(float duration){
  Pololu3piPlus32U4::Motors::setSpeeds((int) speed * MILLIMETERS_IN_METER, (int) -speed * MILLIMETERS_IN_METER);
  delay(duration * MILLISECONDS_IN_SECOND);
  Halt();
}

void MyRobot::Halt(){
  Pololu3piPlus32U4::Motors::setSpeeds(0, 0);
}

void MyRobot::moveForward(float distance){
  Pololu3piPlus32U4::Motors::setSpeeds((int) speed * MILLIMETERS_IN_METER, (int) speed * MILLIMETERS_IN_METER);
  //gives the neccessary duration in milliseconds
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}

void MyRobot::moveBackward(float distance){
  Pololu3piPlus32U4::Motors::setSpeeds((int) -speed * MILLIMETERS_IN_METER, (int) -speed * MILLIMETERS_IN_METER);
  //gives the neccessary duration in milliseconds
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();

}

void MyRobot::moveForwardTurningLeft(float distance){
  Pololu3piPlus32U4::Motors::setSpeeds((int) speed * MILLIMETERS_IN_METER * 0.5, (int) speed * MILLIMETERS_IN_METER);
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}

void MyRobot::moveForwardTurningRight(float distance){
  Pololu3piPlus32U4::Motors::setSpeeds((int) speed * MILLIMETERS_IN_METER, (int) speed * MILLIMETERS_IN_METER * 0.5);
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}

void MyRobot::moveBackwardTurningLeft(float distance){
  Pololu3piPlus32U4::Motors::setSpeeds((int) -speed * MILLIMETERS_IN_METER, (int) -speed * MILLIMETERS_IN_METER * 0.5);
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}

void MyRobot::moveBackwardTurningRight(float distance){
  Pololu3piPlus32U4::Motors::setSpeeds((int) -speed * MILLIMETERS_IN_METER * 0.5, (int) -speed * MILLIMETERS_IN_METER);
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}
