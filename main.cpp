#include "headers/Server.hpp"

int main(int ac, char *av[])
{
	if (ac != 3)
		return 1;
	try {

		Server server("ft_irc", av[2], std::atoi(av[1]));
		server.Get_socket();
		server.run();
	}
	catch(const std::exception& e){
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}
