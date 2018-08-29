#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

#define MAX 80
#define PORT 43454
#define SA struct sockaddr

// send and receive data
void func(int sockfd)
{
    char buff[MAX];
    int n, len;
    struct sockaddr_in client_addr;
    len = sizeof(client_addr);
    for(;;)
    {
        bzero(buff, MAX);
        recvfrom(sockfd, buff, sizeof(buff), 0 , (SA *)&client_addr,&len );
        printf("From client: %s \t To client:", buff);
        if(strncmp("exit", buff, 4) == 0)
               {
                   sendto(sockfd, "exit", 4, 0, (SA *)&client_addr, len);
                   printf("Client exit...\n");
                   break;
               }
        bzero(buff, MAX);
        n=0;
        while((buff[n++] = getchar()) != '\n');
        sendto(sockfd, buff, sizeof(buff), 0, (SA *)&client_addr, len);
    }
}

int main()
{
    // creating a socket
    int sockfd;
    sockfd=socket(AF_INET, SOCK_DGRAM,0);
    if(sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully created..\n");
    }

    // define the server address
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);   // Ip address itself
    servaddr.sin_port=htons(PORT);

    //bind the socket to out specified IP and Port and print out the announcement
    if((bind(sockfd,(SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully binded..\n");
    }

    func(sockfd);
    close(sockfd);
}
