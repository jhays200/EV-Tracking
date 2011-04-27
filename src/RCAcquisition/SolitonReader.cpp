#include "SolitonReader.hpp"
#include "RCObjects/Motor.hpp"
#include <boost/array.hpp>
SolitonReader::SolitonReader(Motor * data, const char * port): iEMController(data), io_service(),
    receiver_endpoint(boost::asio::ip::address_v4::from_string("127.0.0.1"), SOLITON_PORT),
    socket(io_service)
{
  socket.open(udp::v4());
}

void SolitonReader::Update()
{
    udp::endpoint sender_endpoint;
    size_t len = socket.receive_from(
        boost::asio::buffer(buffer), sender_endpoint);
    
    Parse();
}

void SolitonReader::Parse()
{
  rpm = (short int)buffer[26];
  current = (short int)buffer[10];
  temp = (short int)buffer[12];
  temp *= 10;//C*10
  
  m_data.SetRpm(rpm);
  m_data.SetCurrentAccross(current);
  m_data.SetTemp(temp);
}