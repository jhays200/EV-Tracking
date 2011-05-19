#pragma once
#include <python2.7/Python.h>

class VeloComm
{
public:
	VeloComm();
	~VeloComm();
	void Test(double value);
	
private:
	//PyObject * pName;
	PyObject * pModule;
};