#include "headers/Server.hpp"

int main()
{
	try {
		Server server;
		server.Get_socket();
	}
	catch(...){
		return 1;
	}
	return 0;
}