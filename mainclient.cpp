#include <iostream>
#include <string>
#include <memory>
#include "UdpClient.h"



int main(int argc, char *argv[]) 
{

	if (argc != 2)
	{
		std::cerr << "Usage: client <host>" << std::endl;
		return 1;
	}


	try
	{
		boost::asio::io_service io_service;

		UdpClient udpClient(argv[1], io_service);

		io_service.run();
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}



	return 0;
	
}