#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include<strings.h>
#include<time.h>
#include <unistd.h>

#define SIZE 1024
char buf[SIZE];

#define TIME_PORT 16200 //server will listen on this port
int main(int argc, char *argv[]) {
    int sockfd, client_sockfd;
    int nread, len;
    struct sockaddr_in serv_addr, client_addr;
    time_t t;
    char *hello = "Hello from server";
/* create endpoint */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket errors");
        exit(2);
    }
    /* bind address */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(TIME_PORT);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind failed");
        exit(3);
    }
/* specify queue */
    len = sizeof(client_addr);
    listen(sockfd, 5);
    for (;;) {
        client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &len);
        if (client_sockfd == -1) {
            perror("accept");
            continue;
        }
        /* transfer data */
        time(&t);
        sprintf(buf, "%s", asctime(localtime(&t)));
        len = strlen(buf) + 1;
        write(client_sockfd, buf, len);
        send(client_sockfd, hello, strlen(hello), 0);
        printf("Hello message sent\n");
        close(client_sockfd);
        return 0;
    }
}