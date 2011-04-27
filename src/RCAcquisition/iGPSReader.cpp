#include "iGPSReader.hpp"

iGPSReader::iGPSReader(GPSdata* data):m_data(data)
{
}

GPSdata& iGPSReader::GetGPSData()
{
  return *m_data;
}
