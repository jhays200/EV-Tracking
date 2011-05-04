#include "VeloComm.hpp"
#include <boost/python.hpp>
#include <boost/thread.hpp>

using namespace boost::python;

VeloComm::VeloComm()
{
	int i = 0;
	
	try
	{
		Py_Initialize();
		
		eval
	}
}

VeloComm::~VeloComm()
{
	Py_Finalize();
}

void VeloComm::Test(double value)
{
}

int main()
{
	
}