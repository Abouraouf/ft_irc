#include "../headers/Server.hpp"

Server::Server(){}

// void Server::error(int status)
// {
// 	if (status == 1)
// 		std::cout << "syscall failure" << std::endl;
// 	else
// 		std::cout << "Error" << std::endl;
// }

void Server::Get_socket()
{
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, "0", &hints, &res) != 0)
		throw std::runtime_error(std::string("getaddrinfo failed"));
	socket_fd = socket(res->ai_family, res->ai_socktype
						, res->ai_protocol);
	if (socket_fd < 0)
		throw std::runtime_error(std::string("socket failed"));
	if (bind(socket_fd, res->ai_addr, res->ai_addrlen) != 0)
		throw std::runtime_error(std::string("bind failed"));
	if(listen(socket_fd, SOMAXCONN) != 0) // the second parameter is for the number of pending requests (this is not ai, this is me nigger, ai can not write that hah)
		throw std::runtime_error(std::string("listen failed"));
}

void Server::run()
{
	int address_size = addr_size;
	while (2005)
	{
		int client_fd = accept(socket_fd, (struct sockaddr *)& addr_size, &addr_size);
		if (client_fd < 0)
		{
			std::cerr << "invalid client fd" << std::endl;
			continue;
		}
		clients[client_fd] = Client(client_fd);
		std::cout << "New client connected" << std::endl;
		
	}
	
}