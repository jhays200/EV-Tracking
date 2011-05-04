#pragma once
#include "RCAcquisition/iUpdateStradegy.hpp"
#include "RCObjects/Motor.hpp"

class iEMController: virtual public iUpdateStradegy
{
public:
  iEMController(Motor * motor);
  virtual void Update() = 0;
  Motor & GetMotorData();
private:
  Motor m_data;
};