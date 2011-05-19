#include "testBMS.hpp"
#include <vector>
#include <string>
using std::vector;
using std::cout;
using std::endl;
using std::string;

TestBMS::TestBMS(BMS * data, const char * filepath)
	:iBMSReader(data),current_write(0)
{
	if(access(filepath, F_OK) == -1)
	{
		fprintf(stderr, "Failed to access filepath: %s", filepath);
		exit(EXIT_FAILURE);
	}
	m_pipe = open(filepath, O_RDONLY);
	if(m_pipe == -1)
	{
		fprintf(stderr, "Failed to open filepath: %s", filepath);
		exit(EXIT_FAILURE);
	}
	m_update = new boost::thread(boost::bind(&TestBMS::UpdateLoop,this));
}

TestBMS::~TestBMS()
{
	m_update->interrupt();
	m_update->join();
	delete m_update;
	m_update = 0;
}

void TestBMS::UpdateLoop()
{
	//cout << "UpdateLoop" << endl;
	while(true)
	{
		boost::this_thread::disable_interruption di;

			while(m_buffers[current_write].lock.try_lock())
				current_write = current_write % 5 ? current_write + 1 : 0;

			read(m_pipe,m_buffers[current_write].buffer,
					sizeof(double)*4);

			m_buffers[current_write].lock.unlock();
		boost::this_thread::restore_interruption ri(di);
		
		//cout << "Got: " << m_buffers[current_write].buffer << endl;
 		boost::this_thread::sleep(boost::posix_time::microseconds(200000));
	}
}

void TestBMS::Update()
{
	//indexLock.lock();
	int currentRead = current_write;
	//indexLock.unlock();
	currentRead = currentRead -1 > 0 ? currentRead -1:0;
	double temp[4];
	m_buffers[currentRead].lock.lock();
	
	for(int i(0); i < 4; ++i)
	{
		temp[i] = m_buffers[currentRead].buffer[i];
		cout << "Temp " << i << " : " << temp[i] << endl;
	}
	m_buffers[currentRead].lock.unlock();
	
	BMS & bms = GetBMS();
	bms.Setcharge(100);
	Battery battery;
	battery.Setcurrent(temp[0]);
	battery.Setresist(temp[1]);
	battery.Settemp(temp[2]);
	battery.Setvolt(temp[3]);
	vector<Battery> & batteries = bms.GetBatteries();
	batteries.clear();
	batteries.push_back(battery);
}