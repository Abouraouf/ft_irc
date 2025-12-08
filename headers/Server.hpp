#pragma once
#include <sys/socket.h>      // socket(), bind(), listen(), accept(), send(), recv()
#include <netinet/in.h>      // struct sockaddr_in, htons(), INADDR_ANY  ← MANDATORY on 42 Macs
#include <netdb.h>           // getaddrinfo(), freeaddrinfo(), struct addrinfo
#include <arpa/inet.h>       // inet_ntop(), inet_pton(), INET_ADDRSTRLEN
#include <fcntl.h>           // fcntl(fd, F_SETFL, O_NONBLOCK)
#include <poll.h>            // poll(), struct pollfd  ← your entire life
#include <unistd.h>          // close()
#include <cstring>           // memset(), strlen()
#include <string>            // std::string
#include <vector>            // std::vector<pollfd>
#include <map>               // std::map<int, Client>
#include <iostream>          // debugging only
#include <csignal>           // signal(SIGPIPE, SIG_IGN)
#include <exception>
#include "Client.hpp"

class Server
{
	private:
		int socket_fd;
		std::vector<int> poll_fds;
		std::map<int, Client>  clients;
		struct addrinfo hints, *res;
		socklen_t	addr_size;
	public:
		Server();
		void Get_socket();
		void error(int status);
		void run();
};
