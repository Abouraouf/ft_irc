#pragma once
#include <sys/socket.h>      // socket(), bind(), listen(), accept(), send(), recv()
#include <netdb.h>           // getaddrinfo(), freeaddrinfo(), struct addrinfo
#include <arpa/inet.h>       // htons(), htonl(), ntohs(), ntohl(), inet_ntop(), inet_pton()
#include <fcntl.h>           // fcntl() → O_NONBLOCK
#include <poll.h>            // poll(), struct pollfd   <--- your whole life
#include <unistd.h>          // close(), read/write if you insist (but avoid)
// Add this line AT THE VERY TOP of irc.hpp (before everything else)
#include <netinet/in.h>    // THIS IS THE MISSING ONE
// Very common standard headers
#include <cstring>           // memset(), memcpy(), strlen() etc. (C++ version)
#include <string>            // std::string – allowed in .cpp, be careful in .hpp
#include <vector>            // std::vector<pollfd> and client list
#include <map>               // std::map<std::string, Channel>, std::map<int, Client>
#include <iostream>          // only for debugging or error messages
#include <cstdlib>           // exit(), atoi()
#include <cerrno>            // errno
#include <signal.h>          // signal handling if you want to ignore SIGPIPE