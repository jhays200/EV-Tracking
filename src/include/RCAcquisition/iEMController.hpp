#pragma once
#include "RCAcquisition/iUpdateStradegy.hpp"

class Motor;

/*******************************************
 * Class: iEMController
 * Purpose: 
 * 	Generic interface that will be used to 
 * 	store data from any EMC
 *******************************************/
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