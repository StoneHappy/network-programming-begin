#include <cstdio>
#include <cstring>
#include <gtest/gtest.h>
#include <netdb.h>
#include <sys/socket.h>
TEST(networkprogramming, socket)
{
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo("www.example.com", "http", &hints, &res);
    ASSERT_EQ(status, 0);
    int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    ASSERT_NE(status, -1);
}