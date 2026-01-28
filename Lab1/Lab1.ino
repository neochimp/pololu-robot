//Macros for calculations. No magic numbers!
#define MILLISECONDS_IN_SECOND 1000
#define MILLIMETERS_IN_METER 1000
#include <Pololu3piPlus32U4Motors.h>
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

// ================== Task Sheet 6a =======================
// for all functions, speed should be input in m/s,
// distance in meters
// duration in seconds
// Also, delay() takes in milliseconds, and setSpeeds() takes mm/s

void turnLeft(float duration, float speed){
  Pololu3piPlus32U4::Motors::setSpeeds((int) -speed * MILLIMETERS_IN_METER, (int) speed * MILLIMETERS_IN_METER);
  delay(duration * MILLISECONDS_IN_SECOND);
  Halt();
}

void turnRight(float duration, float speed){
  Pololu3piPlus32U4::Motors::setSpeeds((int) speed * MILLIMETERS_IN_METER, (int) -speed * MILLIMETERS_IN_METER);
  delay(duration * MILLISECONDS_IN_SECOND);
  Halt();
}

void Halt(){
  Pololu3piPlus32U4::Motors::setSpeeds(0, 0);
}

void moveForward(float distance, float speed){
  Pololu3piPlus32U4::Motors::setSpeeds((int) speed * MILLIMETERS_IN_METER, (int) speed * MILLIMETERS_IN_METER);
  //gives the neccessary duration in milliseconds
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}

void moveBackward(float distance, float speed){
  Pololu3piPlus32U4::Motors::setSpeeds((int) -speed * MILLIMETERS_IN_METER, (int) -speed * MILLIMETERS_IN_METER);
  //gives the neccessary duration in milliseconds
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();

}

void moveForwardTurningLeft(float distance, float speed){
  Pololu3piPlus32U4::Motors::setSpeeds((int) speed * MILLIMETERS_IN_METER * 0.5, (int) speed * MILLIMETERS_IN_METER);
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}

void moveForwardTurningRight(float distance, float speed){
  Pololu3piPlus32U4::Motors::setSpeeds((int) speed * MILLIMETERS_IN_METER, (int) speed * MILLIMETERS_IN_METER * 0.5);
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}

void moveBackwardTurningLeft(float distance, float speed){
  Pololu3piPlus32U4::Motors::setSpeeds((int) -speed * MILLIMETERS_IN_METER, (int) -speed * MILLIMETERS_IN_METER * 0.5);
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}

void moveBackwardTurningRight(float distance, float speed){
  Pololu3piPlus32U4::Motors::setSpeeds((int) -speed * MILLIMETERS_IN_METER * 0.5, (int) -speed * MILLIMETERS_IN_METER);
  float calculatedDelay = distance/speed * MILLISECONDS_IN_SECOND;
  delay(calculatedDelay);
  Halt();
}
