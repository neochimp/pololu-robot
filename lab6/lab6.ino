#include <Pololu3piPlus32U4.h>
#include "printOLED.h"
#include "PIDcontroller.h"
// #include "odometry.h" //If using odometry, import odometry.h and odometry.cpp
// #include "PDcontroller.h" //Import your PDcontroller.h and PDcontroller.cpp then uncomment
using namespace Pololu3piPlus32U4;

Motors motors;
Encoders encoders;

//Odometry Parameters
#define diaL 3.2
#define diaR  3.2
#define nL 12
#define nR 12
#define w 9.6
#define gearRatio 75
#define DEAD_RECKONING false

//Update kp, kd, and ki based on your testing
#define minOutput -100
#define maxOutput 100
#define kp ... //Tune Kp here
#define kd ... //Tune Kd here
#define ki ... //Tune Ki here
#define clamp_i ... //Tune ki integral clamp here
#define base_speed 50

#define PI 3.14159
//Odometry odometry(diaL, diaR, w, nL, nR, gearRatio, DEAD_RECKONING); //Uncomment if using odometry class
//PDcontroller pdcontroller(kp, kd, minOutput, maxOutput); //Uncomment when using PDController
//PIDcontroller pidcontroller(kp, ki, kd, minOutput, maxOutput, clamp_i); //Uncomment after you implement PIDController

//Feel free to use this in your PD/PID controller for target values
// Given goals in cm and radians
const float goal_theta = PI; // Must put in radians

//odometry
int16_t deltaL=0, deltaR=0;
int16_t encCountsLeft = 0, encCountsRight = 0;
float x, y, theta;

//controller 
//Lab 6
//Note: Here are some suggested variables to use for your code.
double PDout, PIDout; //Output variables for your controllers

void setup() {
  Serial.begin(9600);
}

void loop() {

  //Use this code if you are using odometry. Comment out if you are not.
  //If using, consider turning this into its own function for repeated use.
  // Read data from encoders
  refreshOdometry();

  current_theta = odometry.getTheta();

  //Lab 6
  //Note: To help with testing, print the theta and PD/PID outputs to serial monitor.

  /*TASK 2.1
  Move your PDController.h and PDController.cpp files here to use for task 2.2.
  Also move your odometry.h and odometry.cpp if you decide to use it for 
  measuring the angle of your robot.*/
  
  /*TASK 2.2
  Utilize your PDController to go to angles PI, -PI/2, and PI/2.
  Write your code below and comment out when moving to next task.*/
  
  PDout = PDcontroller.update(current_theta, goal_theta);
  Serial.print("Current Theta: ");
  Serial.println(current_theta);
  Serial.print("PDout: ");
  Serial.println(PDout);
  Serial.println();

  int leftVelocity = (int)constrain(calculateLeftWheelVelocity(0, PDout), -400, 400);
  int rightVelocity = (int)constrain(calculateRightWheelVelocity(0, PDout), -400, 400);
  motors.setSpeeds(leftVelocity, rightVelocity);

    /*TASK 3.1
  Implement PID controller to use for task 3.2.*/

  /*TASK 3.2
  Utilize your PIDController to go to angles PI, PI/2, and PI/2.
  Write your code below.*/
  
  /*
  PIDout = PIDcontroller.update(current_theta, goal_theta);
  Serial.print("Current Theta: ");
  Serial.println(current_theta);
  Serial.print("PIDout: ");
  Serial.println(PIDout);
  Serial.println();

  int leftVelocity = (int)constrain(calculateLeftWheelVelocity(0, PIDout), -400, 400);
  int rightVelocity = (int)constrain(calculateRightWheelVelocity(0, PIDout), -400, 400);
  motors.setSpeeds(leftVelocity, rightVelocity);
  */

  Serial.print("Left velocity: ");
  Serial.println(leftVelocity);
  Serial.print("Right Velocity: ");
  Serial.println(rightVelocity);
  Serial.println("-----\n");
  

}

void refreshOdometry(){
  deltaL = encoders.getCountsAndResetLeft();
  deltaR = encoders.getCountsAndResetRight();

  // Increment total encoder cound
  encCountsLeft += deltaL;
  encCountsRight += deltaR;  

  odometry.update_odom(encCountsLeft,encCountsRight, x, y, theta); //calculate robot's position
}

double calculateRightWheelVelocity(double baseSpeed, double angularVelocity){
  double v = baseSpeed + ((w/2) * angularVelocity);
  return v;
}

double calculateLeftWheelVelocity(double baseSpeed, double angularVelocity){
  double v = baseSpeed - ((w/2) * angularVelocity);
  return v;
}
