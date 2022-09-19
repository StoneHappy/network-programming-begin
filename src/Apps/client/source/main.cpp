#include <cmdline.h>
#include <cstdio>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    cmdline::parser cmdparser;
    cmdparser.add<std::string>("host", 'h', "host name", true, "");
    cmdparser.add<int>("port", 'p', "port number", false, 80, cmdline::range(1, 65535));
    cmdparser.parse_check(argc, argv);

    std::string host = cmdparser.get<std::string>("host");
    int port = cmdparser.get<int>("port");
    
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &res);
    if (status !=0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return -1;
    }

    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    status = connect(sockfd, res->ai_addr, res->ai_addrlen);
    if (status == -1) {
        throw std::runtime_error("socket connect error!");
        close(sockfd);
        return -1;
    }

    freeaddrinfo(res);
    close(sockfd);
}
