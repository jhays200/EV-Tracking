#include "iBMSReader.hpp"

std::vector<Battery> * iBMSReader::GetBatteries()
{
	return m_data->GetBatteries();
}

BMS & iBMSReader::GetBMS()
{
  return *m_data;
}
iBMSReader::iBMSReader(BMS * data):m_data(data)
{
}
