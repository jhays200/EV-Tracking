#pragma once
#include "RCAcquisition/iUpdateStradegy.hpp"

class Motor;

class iEMController: public iUpdateStradegy
{
public:
  iEMController(Motor * motor);
  virtual ~iEMController(){}
  virtual void Update() = 0;
  Motor & GetMotorData();
private:
  Motor & m_data;
};