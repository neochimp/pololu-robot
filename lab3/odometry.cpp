#include <Pololu3piPlus32U4.h>
#include <Pololu3piPlus32U4IMU.h>
#include "odometry.h"
#include "printOLED.h"
using namespace Pololu3piPlus32U4;

#define PI 3.14159

PrintOLED printOLED;

Odometry::Odometry(float diaL, float diaR, float w, int nL, int nR, int gearRatio, bool dead_reckoning){
  _diaL = diaL;
  _diaR = diaR;
  _w = w;
  _nL = nL;
  _nR = nR;
  _gearRatio = gearRatio;
  _deadreckoning = dead_reckoning;

  _x = 0;
  _y = 0;
  _theta = 0;

  _left_encoder_counts_prev = 0;
  _right_encoder_counts_prev = 0;

  if(_deadreckoning){ // if using dead reckoning, initialize and calibrate IMU
    Wire.begin();
    _imu.init();
    _imu.enableDefault();

    //calibrate IMU
    int total = 0;
    for (int i = 0; i < 100; i++)
    {
      _imu.readGyro();
      total += _imu.g.z;
      delay(1);
    }
    _IMUavg_error = total / 100;  
  }
}

// USE ODOMETRY FORMULAS TO CALCULATE ROBOT'S NEW POSITION AND ORIENTATION
void Odometry::update_odom(int left_encoder_counts, int right_encoder_counts, float &x, float &y, float &theta){
	//calculating change in encoder counts
  int deltaR_counts = right_encoder_counts - _right_encoder_counts_prev;
  int deltaL_counts = left_encoder_counts - _left_encoder_counts_prev;

  //Calculating NR and NL
  float rightCountsPerRev = _nR *_gearRatio;
  float leftCountsPerRev = _nL * _gearRatio;

  //Calculating distance traveled for wheels
  float deltaR = (deltaR_counts / rightCountsPerRev) * PI * _diaR;
  float deltaL = (deltaL_counts / leftCountsPerRev) * PI * _diaL;

  // IF USING dead reckoning, GET THE ANGLE _theta FROM IMU
  if(_deadreckoning){
    _imu.readGyro();
    float angleRate = (_imu.g.z - _IMUavg_error);
    _theta += angleRate * 0.0001;
  }else{ // OTHERWISE, CALCULATE THE ANGLE _theta FROM ENCODERS DATA BASED ON THE FORMULA FROM THE LECTURES
    _theta += (deltaR - deltaL)/_w;
  }
  
  // CALCULATE _x BASED ON THE FORMULA FROM THE LECTURES
  _x += ((deltaR + deltaL) / 2.0) * cos(_theta);

  // CALCULATE _y BASED ON THE FORMULA FROM THE LECTURES
  _y += ((deltaR + deltaL) / 2.0) * sin(_theta);

  // CALCULATE CUMULATIVE x, AND CUMULATIVE y. 
  //AKA UPDATE THE VALUE OF &x AND &y (THE PARAMETERS OF THE update_odom FUNCTIONS, WHICH ARE PASSED BY REFERENCE)
  //REMINDER: CUMULATIVE theta IS EQUAL TO _theta.
  x = (float)_x;
  y = (float)_y;
  theta = (float)_theta;

  // PRINT THE x, y, theta VALUES ON OLED
  printOLED.print_odom(x, y, theta);

  // PRINT THE x, y, theta VALUES ON SERIAL MONITOR
  Serial.print(" x:  "); 
  Serial.println(x); 
  Serial.println(" y:  ");
  Serial.println(y);
  Serial.print(" theta:  ");
  Serial.println(theta);

  // Save the current encoder values as the "previous" values, so you can use it in the next iteration
  _right_encoder_counts_prev = right_encoder_counts;
  _left_encoder_counts_prev = left_encoder_counts;
}
