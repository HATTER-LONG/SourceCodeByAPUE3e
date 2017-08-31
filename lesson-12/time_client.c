#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PORT            5050
#define MAXDATASIZE     100

int main(int argc, char *argv[])
{
    int                  fd, numbytes;
    char                 buf[MAXDATASIZE];
    struct sockaddr_in   server;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Create socket failed.");
        exit(-1);
    }
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    if (connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {
        perror("connect failed.");
        exit(-1);
    }
    if( ((numbytes = recv(fd, buf, MAXDATASIZE, 0)) == -1))
    {
        perror("recv error.");
        exit(-1);
    }
    buf[numbytes] ='\0';
    printf("Server Message: %s\n",buf);
    close(fd);
}