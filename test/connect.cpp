#include <cstdio>
#include <cstring>
#include <gtest/gtest.h>
#include <netdb.h>
#include <sys/socket.h>
TEST(networkprogramming, connect)
{
    struct addrinfo hints, *res;
    // 首先，用 getaddrinfo() 載入 address structs：

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo("www.example.com", "http", &hints, &res);
    if (status !=0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        ASSERT_EQ(status, 0);
	}
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    ASSERT_NE(sockfd, -1);

    status = connect(sockfd, res->ai_addr, res->ai_addrlen);
    ASSERT_NE(status, -1);
}