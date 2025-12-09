#include "../headers/Server.hpp"
//handle the eof
// do the destructor
//handle the ctrl + c;


Server::Server(std::string Name,std::string Password, std::string Port) : name(Name), password(Password), port(Port)
{
}
void Server::Get_socket()
{
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	if (getaddrinfo(NULL, port.c_str(), &hints, &res) != 0)
		throw std::runtime_error(std::string("getaddrinfo failed"));
	socket_fd = socket(res->ai_family, res->ai_socktype
						, res->ai_protocol);
	if (socket_fd < 0)
		throw std::runtime_error(std::string("socket failed"));
	int yes = 1;
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
    	throw std::runtime_error("setsockopt SO_REUSEADDR failed");
	if (bind(socket_fd, res->ai_addr, res->ai_addrlen) != 0)
		throw std::runtime_error(std::string("bind failed"));	
	if(listen(socket_fd, SOMAXCONN) != 0) // the second parameter is for the number of pending requests (this is not ai, this is me nigger, ai can not write that hah)
		throw std::runtime_error(std::string("listen failed"));
}

void Server::acceptnewclient()
{
	socklen_t address_size = sizeof(addr_size);
	int client_fd = accept(socket_fd, (struct sockaddr *)& addr_size, &address_size);
	if (client_fd < 0)
		std::cerr << "invalid client fd" << std::endl;
	fcntl(client_fd, F_SETFL, O_NONBLOCK);

    clients[client_fd] = Client(client_fd);        // this is the "push_back"

    struct pollfd new_pollfd = { client_fd, POLLIN, 0 };
    poll_fds.push_back(new_pollfd);
    std::cout << "New client connected: fd " << client_fd << std::endl;
}

void Server::run()
{
	struct pollfd tmp;
	tmp.fd      = socket_fd;
	tmp.events  = POLLIN;
	tmp.revents = 0;
	poll_fds.push_back(tmp);
    while (true)
    {
        if (poll(poll_fds.data(), poll_fds.size(), -1) == -1) {
            perror("poll");
            break;
        }
        if (poll_fds[0].revents & POLLIN) {
            acceptnewclient();
        }
        for (size_t i = 1; i < poll_fds.size(); ++i) {
			if (poll_fds[i].revents & POLLIN) {
    		char buf[512];
    		int fd = poll_fds[i].fd;
    		ssize_t n = recv(fd, buf, sizeof(buf)-1, 0);

    		if (n <= 0) {
    		    close(fd);
    		    clients.erase(fd);
    		    poll_fds.erase(poll_fds.begin() + i);
    		    std::cout << "Client " << fd << " disconnected\n";
    		} else {
    		    buf[n] = '\0';
    		    std::cout << "Client " << fd << " sent: " << buf << std::endl;
    			}
			}
        }
		
    }
}


Server::~Server()
{
	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		close(it->first);
	}
	clients.clear();
	if (socket_fd != -1)
		close(socket_fd);
	if (res != NULL){
		freeaddrinfo(res);
		res = NULL;
	}
	poll_fds.clear();
}
