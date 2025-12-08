#include "headers/Server.hpp"

int main()
{
	try {

		Server server;
		server.Get_socket();
		server.run();
	}
	catch(const std::exception& e){
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}