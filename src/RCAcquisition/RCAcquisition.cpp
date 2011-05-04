#include "RCAcquisition/RCAcquisition.hpp"

RCAcquisition::RCAcquisition():m_num_threads(0),m_update_time(5)
{
  
}

RCAcquisition::~RCAcquisition()
{}

void RCAcquisition::AddService(iUpdateStradegy service)
{
  m_updates += service;
}