#include "VeloComm.hpp"
#include <unistd.h>
#include <string>
#include <cstdio>

using namespace std;
using std::string;

const int PYSCRIPT_PATH_LEN = 100;
const int COMMAND_LEN = 30;

VeloComm::VeloComm(): pModule(0)
{
	string command = "sys.path.append(\"";
	char cwdPath[PYSCRIPT_PATH_LEN];
	int i = 0;
	
	//getcwd and store it into cwdPath
	
	//create a command to add the script to the path
	getcwd(cwdPath, PYSCRIPT_PATH_LEN); //get current working directory path
	command.append(cwdPath);
	command.append("\")\n");
	printf(command.c_str());
	
	Py_Initialize();
	
	//set the path to the script
	PyRun_SimpleString("import sys\n");
	PyRun_SimpleString(command.c_str());
	PyRun_SimpleString("from VeloComm import Test, Init\n");
	PyRun_SimpleString("Init()\n");
	
}
	

VeloComm::~VeloComm()
{
	Py_Finalize();
}

void VeloComm::Test(double value)
{
	char command[COMMAND_LEN];
	sprintf(command, "Test(%f)\n", value);
	PyRun_SimpleString(command);
}

int main()
{
	VeloComm * test = new VeloComm;
	for(int i = 32; i != 0; --i)
		test->Test((double)i);
	delete test;
}