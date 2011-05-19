#include "iNamedPipeReader.hpp"

iNamedPipeReader::iNamedPipeReader(TestObject * data):m_data(data)
{}
iNamedPipeReader::~iNamedPipeReader()
{}

TestObject & iNamedPipeReader::GetData()
{
	return *m_data;
}