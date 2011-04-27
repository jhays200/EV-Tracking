#pragma once
#include "iUpdateStradegy.hpp"
#include "RCObjects/Motor.hpp"

class iEMController: virtual public iUpdateStrategy
{
public:
  iEMController(Motor * motor);
  virtual void Update() = 0;
  Motor & GetMotorData();
private:
  Motor & m_data;
};