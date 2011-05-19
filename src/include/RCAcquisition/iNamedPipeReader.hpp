#pragma once
#include "iUpdateStradegy.hpp"
#include "RCObjects/testObject.hpp"

class iNamedPipeReader: public iUpdateStradegy
{
public:
	iNamedPipeReader(TestObject * data);
    virtual ~iNamedPipeReader();
	virtual void Update() = 0;
	TestObject & GetData();
private:
	TestObject * m_data;
};