#include <Pololu3piPlus32U4.h>
#include "my_robot.h"

//instantiate a robot with a speed of 0.1m/s
MyRobot testRobot(0.1);

void setup() {
  Serial.begin(9600);
  delay(15);
}

void loop() {
  //initial delay
  delay(10000);
  //move forward
  testRobot.moveForward(1);
  delay(1000);

  //move backwards
  testRobot.moveBackward(1);
  delay(1000);

  //turn right (in place)
  testRobot.turnRight(0.94);
  delay(1000);

  //turn left (in place)
  testRobot.turnLeft(0.94);
  delay(1000);
  
  //move forward while turning left
  testRobot.moveForwardTurningLeft(1);
  delay(1000);

  //move forward while turning right
  testRobot.moveBackwardTurningRight(1);
  delay(1000);

  //move backward while turning right
  testRobot.moveForwardTurningRight(1);
  delay(1000);

  //move backward while turning left
  testRobot.moveBackwardTurningLeft(1);
  delay(1000);

  //halt
  testRobot.Halt();
  
}

// ================== Task Sheet 6a =======================
// for all functions, speed should be input in m/s,
// distance in meters
// duration in seconds
// Also, delay() takes in milliseconds, and setSpeeds() takes mm/s
/*
void turnLeft(float duration, float speed){
  //To turn left, left motor and right motor need equal speed while left goes backward and right goes forward
  Pololu3piPlus32U4::Motors::setSpeeds((int) -speed * MILLIMETERS_IN_METER, (int) speed * MILLIMETERS_IN_METER);
  delay(duration * MILLISECONDS_IN_SECOND);
  Halt();
}

void turnRight(float duration, float speed){
  //To turn right, left motor and right motor need equal speed while left goes forward and right goes backward
  Pololu3piPlus32U4::Motors::setSpeeds((int) speed * MILLIMETERS_IN_METER, (int) -speed * MILLIMETERS_IN_METER);
  delay(duration * MILLISECONDS_IN_SECOND);
  Halt();
}

void Halt(){
  //sets both motors speed to 0 in order to stop
  Pololu3piPlus32U4::Motors::setSpeeds(0, 0);
}

void moveForward(float distance, float speed){
  //In order to move straight forward both motors need to go the same speed
  Pololu3piPlus32U4::Motors::setSpeeds((int) speed * MILLIMETERS_IN_METER, (int) speed * MILLIMETERS_IN_METER);
  //gives the neccessary duration in milliseconds
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}

void moveBackward(float distance, float speed){
  //To go straight backward both motors need to go the same speed in reverse
  Pololu3piPlus32U4::Motors::setSpeeds((int) -speed * MILLIMETERS_IN_METER, (int) -speed * MILLIMETERS_IN_METER);
  //gives the neccessary duration in milliseconds
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();

}

void moveForwardTurningLeft(float distance, float speed){
  //To go forward while turning left, the right motor needs to go faster than the left motor while both are going forward
  Pololu3piPlus32U4::Motors::setSpeeds((int) speed * MILLIMETERS_IN_METER * 0.5, (int) speed * MILLIMETERS_IN_METER);
  //gives the neccessary duration in milliseconds
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}

void moveForwardTurningRight(float distance, float speed){
  //To go forward while turning right, the left motor needs to go faster than the right motor while both are going forward
  Pololu3piPlus32U4::Motors::setSpeeds((int) speed * MILLIMETERS_IN_METER, (int) speed * MILLIMETERS_IN_METER * 0.5);
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}

void moveBackwardTurningLeft(float distance, float speed){
  //To go backward while turning left, the left motor needs to go faster than the right motor while both are in reverse
  Pololu3piPlus32U4::Motors::setSpeeds((int) -speed * MILLIMETERS_IN_METER, (int) -speed * MILLIMETERS_IN_METER * 0.5);
  //gives the neccessary duration in milliseconds
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}

void moveBackwardTurningRight(float distance, float speed){
  //To go backward while turning right, the right motor needs to go faster than the left motor while both are in reverse
  Pololu3piPlus32U4::Motors::setSpeeds((int) -speed * MILLIMETERS_IN_METER * 0.5, (int) -speed * MILLIMETERS_IN_METER);
  //gives the neccessary duration in milliseconds
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}
*/
