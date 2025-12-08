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

class Client{
	private:
	int         fd;               
    std::string recv_buffer;      
    std::string send_buffer;      
    
    std::string nickname;          
    std::string username;
    std::string realname;    
    bool        registered;
	public:
		Client();
		Client(int fd);
};