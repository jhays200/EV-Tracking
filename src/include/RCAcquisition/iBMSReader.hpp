#pragma once
#include "iUpdateStradegy.hpp"
#include "RCObjects/BMS.hpp"

#include <vector>

class iBMSReader: virtual public iUpdateStradegy
{
public:
  iBMSReader(BMS * data);
  
  virtual void Update() = 0;
  
  std::vector<Battery> * GetBatteries();
  BMS & GetBMS();
private:
  BMS * m_data;
};