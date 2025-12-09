#include "headers/Server.hpp"

volatile bool g_stop = false;

void handle_sigint(int)
{
    g_stop = true;  // ONLY set a flag, nothing else
}


int main(int ac, char *av[])
{
	if (ac != 3)
		return 1;
	 std::signal(SIGINT, handle_sigint);
	try {

		Server server("ft_irc", av[2], av[1]);
		server.Get_socket();
		server.run();
	}
	catch(const std::exception& e){
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}
