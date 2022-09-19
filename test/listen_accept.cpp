#include <cstdio>
#include <cstring>
#include <gtest/gtest.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>


#define MYPORT "3490"
#define BACKLOG 10
TEST(networkprogramming, listen_accept)
{
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status = getaddrinfo(NULL, MYPORT, &hints, &res);
    if (status !=0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        ASSERT_NE(status, 0);
	}
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    ASSERT_NE(sockfd, -1);

    status = bind(sockfd, res->ai_addr, res->ai_addrlen);
    ASSERT_NE(status, -1);

    status = listen(sockfd, BACKLOG);
    ASSERT_NE(status, -1);

    addr_size = sizeof their_addr;
    int new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &addr_size);
    ASSERT_NE(new_fd, 0);
}