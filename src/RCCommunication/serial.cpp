#include "serial.h"

EvSerialIO::EvSerialIO(const char * file, int open_options)
{
  fd = open(file, open_options);
  
  if( fd == -1 )
    throw "Invalid serial file, could not establish connection.";
  
  tcgetattr(fd,&options);
}

EvSerialIO::~EvSerialIO()
{
  close(fd);
}

void EvSerialIO::SetReadOptions(bool options)
{
  if(options)
    fcntl(fd, F_SETFL, 0);
  else
    fcntl(fd, F_SETFL, FNDELAY);
  
  tcsetattr(fd, TCSANOW, &(this->options));
}

void EvSerialIO::SetBaud(int baud, int options)
{
  cfsetispeed(&(this->options), options);
  cfsetospeed(&(this->options), options);
  tcsetattr(fd, TCSANOW, &(this->options));
}

void EvSerialIO::SetParityChecking(int check)
{
  switch(check)
  {
    case SPACE_PARITY:
    case NO_PARITY:
      options.c_cflag &= ~PARENB;
      options.c_cflag &= ~CSTOPB;
      options.c_cflag &= ~CSIZE;
      options.c_cflag |= CS8;
      break;
    case EVEN_PARITY:
      options.c_cflag |= PARENB;
      options.c_cflag &= ~PARODD;
      options.c_cflag &= ~CSTOPB;
      options.c_cflag &= ~CSIZE;
      options.c_cflag |= CS7;
      break;
    case ODD_PARITY:
      options.c_cflag |= PARENB;
      options.c_cflag |= PARODD;
      options.c_cflag &= ~CSTOPB;
      options.c_cflag &= ~CSIZE;
      options.c_cflag |= CS7;
      break;
    default:
      throw "Invalid Parity option";
  }
  
  tcsetattr(fd, TCSANOW, &options);
}

void EvSerialIO::SetHardwareFlowControl(bool control)
{
  if(control)
    options.c_cflag |= CNEW_RTSCTS; 
  else options.c_cflag &= ~CNEW_RTSCTS;
  
  tcsetattr(fd, TCSANOW, &options);
}

void EvSerialIO::SetLocal(int local, int other)
{
  switch(local)
  {
    case OTHER:
      options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
      options.c_lflag |= other;
      break;
    case RAW:
      options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
      break;
    case CANONICAL:
      options.c_lflag |= (ICANON | ECHO | ECHOE);
      break;
    default:
      throw "Invalid local selection";
  }
  tcsetattr(fd, TCSANOW, &options);
}

void EvSerialIO::SetInputOptions(int option)
{
  switch(option)
  {
    case OTHER:
      options.c_lflag |= option;
      break;
    case RAW:
      options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
      break;
    case CANONICAL:
      options.c_lflag |= (ICANON | ECHO | ECHOE);
      break;
    default:
      throw "Invalid input option";
  }
  tcsetattr(fd, TCSANOW, &options);
}

void EvSerialIO::SetSoftwareFlowControl(bool control)
{
  if(control)
    options.c_iflag |= (IXON | IXOFF | IXANY);
  else options.c_iflag &= ~(IXON | IXOFF | IXANY);
  
  tcsetattr(fd, TCSANOW, &options);
}

void EvSerialIO::SetOutputOptions(int option, int other)
{
  switch(option)
  {
    case RAW:
      options.c_oflag &= ~OPOST;
      break;
    case PROCESSED:
      options.c_oflag |= OPOST;
      break;
    case OTHER:
      options.c_oflag |= other;
      break;
    default:
      throw "Invalid Output Option selection";
  }
  
  tcsetattr(fd, TCSANOW, &options);
}

void EvSerialIO::Read(char * buffer, size_t size)
{
  int n = read(fd, (void *)buffer, size);
  if( n < 0 )
    throw "Serial read failed";
}

void EvSerialIO::Write(const char * data, size_t size)
{
    int n = write(fd, data, size);

    if (n < 0)
      throw "Serial write failed\n";
}