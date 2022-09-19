#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <gtest/gtest.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
TEST(networkprogramming, getaddrinfo)
{
	struct addrinfo hints, *res, *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	const char* input0 = "www.example.net";
	// const char* input0 = "ipv6.example.com";

	if ((status = getaddrinfo(input0, NULL, &hints, &res))!=0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
	}

	printf("IP address for %s: \n\n", input0);

	for (p = res; p != NULL; p=p->ai_next) {
		void *addr;
		char const *ipver;

		if (p->ai_family == AF_INET) { // IPv4
			struct sockaddr_in *ipv4 = (struct sockaddr_in*) p->ai_addr;
			addr = &ipv4->sin_addr;
			ipver = "IPv4";
		}
		else { // IPv6
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6*) p->ai_addr;
			addr = &ipv6->sin6_addr;
			ipver = "Ipv6";
		}

		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
		printf(" %s: %s\n", ipver, ipstr);
	}
}