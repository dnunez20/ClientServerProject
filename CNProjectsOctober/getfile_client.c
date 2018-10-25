/* TCP client that finds the time from a server */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SIZE 1024
char buf[SIZE];
#define TIME_PORT 16200 //server listens on this port
int main(int argc, char *argv[]) {
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int nread;
    struct sockaddr_in serv_addr;
    struct hostent * h;
    char *hello = "Hello from client";
    if (argc != 2) {
        fprintf(stderr, "usage: %s IPaddr\n", argv[0]);
        exit(1);
    }
/* create endpoint */
    if (sockfd < 0) {
        printf("\n Socket creation error \n");
        perror(NULL);
        exit(2);
    }
    /* connect to server */
    serv_addr.sin_family = AF_INET;

    h = gethostbyname(argv[1]);
    bcopy(h->h_addr, (char *)&serv_addr.sin_addr, h->h_length);
    serv_addr.sin_port = htons(TIME_PORT);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror(NULL);
        exit(3);
    }
/* transfer data */
    nread = read(sockfd, buf, SIZE);
    write(1, buf, nread); // Writes to standard output
    send(sockfd, hello, strlen(hello),0);
    printf("Hello message sent\n");
    close(sockfd);
    exit(0);
}