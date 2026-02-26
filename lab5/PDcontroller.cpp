#include <Pololu3piPlus32U4.h>
#include "PDcontroller.h"
using namespace Pololu3piPlus32U4;

PDcontroller::PDcontroller(float kp, float kd, double minOutput, double maxOutput) {
  // initialize the private varaibles from Pcontroller.h here
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
}

double PDcontroller::update(double value, double target_value){
  //Controller math here
  /*Hints: To add damping (derivative), you must have something to
           keep track of time for the rate of change.
           
           Also note that the first time PD controller is ran, we only have
           the P component, so consider using an if-else statement.

           Again, you need to return actuator controller value (_clampOut)
  */
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
    }
  }

  //calculating PD output and clamping it
  _rawOutput = (_kp * _error) + (_kd * derivative);
  _clampOut = constrain(_rawOutput, _minOutput, _maxOutput);

  //saving current error and time for next update
  _prevError = _error;
  _prevTime = currentTime;
  
  return _clampOut;


}
