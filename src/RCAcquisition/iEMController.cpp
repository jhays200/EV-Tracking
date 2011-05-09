#include "iEMController.hpp"
#include "RCObjects/Motor.hpp"

iEMController::iEMController(Motor * data):m_data(*data)
{}

Motor & iEMController::GetMotorData()
{
  return m_data;
}