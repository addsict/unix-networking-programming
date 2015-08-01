#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>

int main()
{
    struct sockaddr_in servaddr, cliaddr;
    int port = 5000;
    int sock = socket(PF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if (bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr))) {
        fprintf(stderr, "bind failed: port = %d", port);
        exit(1);
    }

    char buf[1024];
    socklen_t cli_addrlen = sizeof(cliaddr);
    while (1) {
        int bytes = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&cliaddr, &cli_addrlen);
        sendto(sock, buf, bytes, 0, (struct sockaddr*)&cliaddr, cli_addrlen);
    }

    return 0;
}
