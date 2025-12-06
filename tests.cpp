// save as test.cpp
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>

int main()
{
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;      // IPv4
    hints.ai_socktype = SOCK_STREAM;  // TCP
    hints.ai_flags    = AI_PASSIVE;   // server mode

    int status = getaddrinfo(NULL, "6667", &hints, &res);
    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        return 1;
    }

    struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
    char ip_str[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &ipv4->sin_addr, ip_str, INET_ADDRSTRLEN);

    std::cout << "Ready to bind to:\n";
    std::cout << "  IP   : " << ip_str << "  (0.0.0.0 = all interfaces)\n";
    std::cout << "  Port : " << ntohs(ipv4->sin_port) << "\n";
    int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    freeaddrinfo(res);
    return 0;
}