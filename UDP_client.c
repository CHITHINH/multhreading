#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 80
#define PORT 43454
#define SA struct sockaddr
int main()
{
    char buff[MAX];

    // creating a socket and checking out result
    int sockfd,n, len;
    sockfd=socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully created..\n");
    }

    // define the socket address
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);       //inet_addr("127.0.0.1"); IP; address server
    servaddr.sin_port = htons(PORT);
    len = sizeof(servaddr);
    // send and receice data
    for(;;)
    {
        printf("\nMessage : ");
        n=0;
        while((buff[n++] = getchar()) != '\n');
        sendto(sockfd, buff, sizeof(buff), 0,(SA *)&servaddr, len);
        bzero(buff,sizeof(buff));
        recvfrom(sockfd, buff, sizeof(buff), 0,(SA *)&servaddr, &len);
        printf("From Server: %s\n", buff);
        if(strncmp("exit", buff,4) == 0)
        {
            sendto(sockfd, "exit", 4, 0, (SA *)&servaddr, len);
            printf("Server exit...\n");
            break;
        }
    }
    close(sockfd);
}
