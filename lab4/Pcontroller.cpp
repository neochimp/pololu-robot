#include <Pololu3piPlus32U4.h>
#include "Pcontroller.h"
using namespace Pololu3piPlus32U4;

Pcontroller::Pcontroller(float kp, double minOutput, double maxOutput) {
  // initialize the private varaibles from Pcontroller.h here
  _kp = kp;
  _minOutput = minOutput;
  _maxOutput = maxOutput;
}

//returns angular velocity in radians/second
double Pcontroller::update(double value, double target_value){
  //Controller math here
  //Hint: Need to return actuator controller value (_clampOut)
  _error = value - target_value;
  _rawOutput = _kp * _error;
  _clampOut = constrain(_rawOutput, _minOutput, _maxOutput);
  
  return _clampOut;

}
