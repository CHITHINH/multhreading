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

void func (int sockfd)
{
    char buff[MAX];
    int n;

    for(;;)
    {
        bzero(buff, MAX);
        printf("Message: ");
        n=0;
        while((buff[n++] = getchar()) != '\n');
        write(sockfd, buff, sizeof(buff));
        bzero(buff,MAX);
        read(sockfd ,buff, sizeof(buff));
        printf( "\tFrom server : %s", buff);

        if (strncmp(buff, "exit", 4) == 0)
        {
            printf("Server exit. \n");
            break;
		}
	}
}

int main()
{
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        printf ("Socket creation failed ... \n");
        exit(0);
    }
    else
    {
        printf(" Socket successfully created\n");
    }
    // specify an address for the socket
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // checking for error with the connection
    if(connect(sockfd,(SA*) &servaddr, sizeof(servaddr)) != 0)
    {
        printf("Connetion with the server failed. \n");
        close(sockfd);
        exit(0);
    }
    else
    {
        printf(" Conneted to the server. \n");
    }

    func(sockfd);
    close(sockfd);
}

