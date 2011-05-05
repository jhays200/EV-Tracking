#include "VeloComm.hpp"
#include <unistd.h>
#include <string>
#include <iostream>

using namespace std;
using std::string;

VeloComm::VeloComm(): pModule(0)
{
	string command = "sys.path.append(\"";
	char cwdPath[100];
	int i = 0;
	
	//getcwd and store it into cwdPath
	
	//create a command to add the script to the path
	getcwd(cwdPath, 100);
	command.append(cwdPath);
	command.append("\")\n");
	cout << command << endl;
	
	Py_Initialize();
	
	//set the path to the script
	PyRun_SimpleString("import sys\n");
	PyRun_SimpleString(command.c_str());
	PyRun_SimpleString("from VeloComm import Test, Init\n");
	PyRun_SimpleString("Init(5)\n");
	PyRun_SimpleString("Test(5)\n");
	//PyRun_SimpleString("time.sleep(100)");
	PyRun_SimpleString("Test(3)\n");
	//PyRun_SimpleString("time.sleep(100)");
	PyRun_SimpleString("Test(5)\n");
	//PyRun_SimpleString("time.sleep(100)");
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
	VeloComm * test = new VeloComm;
	delete test;
}