#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
    #include <unistd.h>
#define MYPORT "3490"  // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue holds

int main(void)
{
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    struct addrinfo hints, *res;
    int sockfd, new_fd;

    // !! don't forget your error checking for these calls !!

    // first, load up address structs with getaddrinfo():

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    getaddrinfo(NULL, "1234", &hints, &res);

    // make a socket, bind it, and listen on it:

    sockfd = socket(res->ai_family, res->ai_socktype,
                                                 res->ai_protocol);
    bind(sockfd, res->ai_addr, res->ai_addrlen);
    listen(sockfd, BACKLOG);

    // now accept an incoming connection:

    addr_size = sizeof their_addr;
    while (1)
    {
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr,
                                                       &addr_size);
    if (new_fd >= 0)
        std::cout << "connected suuccesfully" << std::endl;
    else
        break ;
    int length = send(new_fd, "asd", 4, 0);
    std::cout << length << std::endl;
    char buf[1024];
        while (1) {
            int n = recv(new_fd, buf, sizeof(buf)-1, 0);  

            if (n <= 0) {                     
                if (n < 0) perror("recv");
                else printf("Client closed connection\n");
                break;
            }

            buf[n] = '\0';                    // null-terminate
            printf("Received: %s", buf);      // see it on server terminal
            send(new_fd, "You wrote: ", 11, 0);
            send(new_fd, buf, n, 0);
        }
    close(new_fd);
    }
}
