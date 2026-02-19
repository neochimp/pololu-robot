#include <Pololu3piPlus32U4.h>
#include <Servo.h>
#include "sonar.h"
#include "Pcontroller.h"
using namespace Pololu3piPlus32U4;

//Odometry Parameters
#define diaL 3.2
#define diaR  3.2
#define nL 12
#define nR 12
#define w 96 //distance between two wheels in mm
#define gearRatio 75

//Update kp and kd based on your testing
#define minOutput -2.0
#define maxOutput 2.0
#define kp 0.1 //radians per second per cm
#define base_speed 50 //50mm/s

#define MM_IN_CM 10

Motors motors;
Servo servo;
Sonar sonar(4);

Pcontroller Pcontroller (kp, minOutput, maxOutput);

const double distFromWall=10.0; // Goal distance from wall (cm)

double wallDist;
double Pout;

void setup() {
  Serial.begin(9600);
  servo.attach(5);
  servo.write(0);
  delay(40);
  //Move Sonar to desired direction using Servo
}

void loop() {
  //DO NOTE DELETE CODE AFTER EACH TASK, COMMENT OUT INSTEAD
  wallDist = sonar.readDist();

  //UNCOMMENT AFTER IMPLEMENTING Pcontroller
  Pout = Pcontroller.update(wallDist, distFromWall); //uncomment if using Pcontroller 

  //(LAB 4 - TASK 3.1) IMPLEMENT PCONTROLLER 
  
  /*FIRST GO TO Pcontroller.h AND ADD PRIVATE VARIABLES NEEDED.
    THEN GO TO Pcontroller.cpp AND COMPLETE THE update FUNCTION.
    ONCE YOU IMPLEMENT update, UNCOMMENT CODE ABOVE TO USE CONTROLLER.*/

  //(LAB 4 - TASK 3.2) PCONTROLLER WALL FOLLOWING

  /*NOW THAT YOU HAVE IMPLEMENTED PCONTROLLER, TAKE THE OUTPUT FROM Pout
  AND SET THE MOTOR SPEEDS. CHANGE THE KP AND CLAMPING VALUES AT THE TOP
  TO TEST (B-D).
  Hint: Also use baseSpeed when setting motor speeds*/

  //Also print outputs to serial monitor for testing purposes
  Serial.print("Distance from wall: ");
  Serial.print(wallDist);
  Serial.println("cm\n");
  Serial.print("Angular Velocity: ");
  Serial.print(Pout);
  Serial.println("rad/s");
 
  int leftVelocity = (int)constrain(calculateLeftWheelVelocity(base_speed, Pout * MM_IN_CM), -400, 400);
  int rightVelocity = (int)constrain(calculateRightWheelVelocity(base_speed, Pout * MM_IN_CM), -400, 400);
  motors.setSpeeds(leftVelocity, rightVelocity);

  Serial.print("Left velocity: ");
  Serial.println(leftVelocity);
  Serial.print("Right Velocity: ");
  Serial.println(rightVelocity);
  Serial.println("-----\n");
  
}

double calculateRightWheelVelocity(double baseSpeed, double angularVelocity){
  double v = baseSpeed + ((w/2) * angularVelocity);
  return v;
}

double calculateLeftWheelVelocity(double baseSpeed, double angularVelocity){
  double v = baseSpeed - ((w/2) * angularVelocity);
  return v;
}
