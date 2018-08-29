#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#define MAX 80
#define PORT 43454
#define SA struct sockaddr

// sent and receive messages
void func(int sockfd)
{
    char buff[MAX];

    for (;;)
    {
        bzero(buff, MAX);
        read(sockfd, buff, sizeof(buff));

        // exit chat when recieve exit message
        if(strncmp( buff,"exit", 4) == 0)
                {
                    printf("Client exit. \n");
                    break;
                }

        printf("Frome client: %s\t To client : ", buff);
        bzero(buff, MAX);
        int n=0;
        while ((buff[n++] = getchar()) != '\n');
        write(sockfd, buff, sizeof(buff));
	}
}

int main(){

    int sockfd, client_socket ;
    struct sockaddr_in servaddr;

    // created a server socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // checking for error with the connection
    if(sockfd == -1)
    {
        printf(" Socket creation faild. \n");
        exit(0);
    }
    else
    {
        printf("Socket successfully created. \n");
    }

    bzero(&servaddr, sizeof(servaddr));

    // define the server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;         // htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    //bind the socket to out specified IP and Port and print out the announcement
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf(" Socket bind failed. \n");
        exit(0);
    }
    else
    {
        printf(" Socket successfully binded.");
    }

    // listen from client and print out the announcement
    if((listen(sockfd,5)) != 0)
    {
        printf(" listen failed. \n");
        exit(0);
    }else
    {
        printf("Server listening. \n");
    }

    // accept connection from client and print out the announcement
    client_socket = accept(sockfd, NULL, NULL) ;        //(SA *) &client_addr, sizeof(client_addr));
    if(client_socket < 0){
        printf(" server accept failed.\n");
        exit(0);
    }else
    {
        printf("server accept the client. \n");
    }

    func(client_socket);
    close(sockfd);
}
