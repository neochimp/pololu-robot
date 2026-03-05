#include <Pololu3piPlus32U4.h>
#include "PIDcontroller.h"
using namespace Pololu3piPlus32U4;

PIDcontroller::PIDcontroller(float kp, float ki, float kd, double minOutput, double maxOutput, double clamp_i) {
  /*Initialize values by copying and pasting from PD controller, then declaring for
  the three new variables.*/

  _kp = kp;
  _kd = kd;
  _minOutput = minOutput;
  _maxOutput = maxOutput;
  _error = 0.0;
  _rawOutput = 0.0;
  _clampOut = 0.0;
  _prevError = 0.0;
  _prevTime = 0;
  _isFirstRun = true;

  _ki = ki;
  _clampI = clamp_i;
  _integral = 0.0;
}

double PIDcontroller::update(double value, double target_value){
  /*Now copy and paste your PD controller. To implement I component,
  keep track of accumulated error, use your accumulated error in the constrain
  function for the integral, multiply ki by your integral, then add your p, d,
  and i components.
  
  Note: Do not just put all of the integral code at the end of PD component. Think
  about step by step how you can integrate these parts into your PDController
  code.*/

  //keeping track of current time
  unsigned long currentTime = millis();
  _error = value - target_value;

  double derivative = 0.0;

  //if first run can't find derivative
  if(_isFirstRun){
    _isFirstRun = false;
  }
  else{ //else calculate the derivative
    double dt = (double)(currentTime - _prevTime);
    if(dt > 0.0){
      derivative = (_error - _prevError)/dt;

      //calculating integral
      _integral += _error * dt;
    }
  }

  //clamping integral
  _integral = constrain(_integral, -_clampI, _clampI);

  //calculating PD output and clamping it
  _rawOutput = (_kp * _error) + (_kd * derivative) + (_ki * _integral);
  _clampOut = constrain(_rawOutput, _minOutput, _maxOutput);

  //saving current error and time for next update
  _prevError = _error;
  _prevTime = currentTime;
  
  return _clampOut;
}
