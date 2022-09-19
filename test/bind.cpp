#include <cstdio>
#include <cstring>
#include <gtest/gtest.h>
#include <netdb.h>
#include <sys/socket.h>
TEST(networkprogramming, bind)
{
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status = getaddrinfo(NULL, "3490", &hints, &res);
    if (status !=0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        ASSERT_NE(status, 0);
	}
    int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    ASSERT_NE(s, -1);

    status = bind(s, res->ai_addr, res->ai_addrlen);
    ASSERT_NE(status, -1);
}