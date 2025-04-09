// STOP AND WAIT SERVER PROGRAM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
int main() {
int sockfd, len, frames[100], n, p, ack;
struct sockaddr_in servaddr, cliaddr;
sockfd = socket (AF_INET, SOCK_DGRAM, 0);
printf("\nwaiting for client...\n");
memset(&servaddr, 0, sizeof(servaddr));
memset(&cliaddr, 0, sizeof(cliaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(6080);
bind(sockfd, (struct sockaddr *)&servaddr, sizeof servaddr);
len = sizeof(cliaddr);
recvfrom(sockfd, &n, sizeof (n), 0, (struct sockaddr *)&cliaddr, &len);
printf("\nClient connected successfuly.\n");
printf("\nwaiting for total number of frames...\n");
recvfrom(sockfd, &n, sizeof (n), 0, (struct sockaddr *)&cliaddr, &len);
while (1) {
recvfrom(sockfd, &p, sizeof(n), 0, (struct sockaddr *)&cliaddr, &len);
if (p==-99)
return 0;
printf("\nReceived frame-%d ", p);
printf("\nEnter 1 for +ve ack and -1 for -ve ack.\n");
scanf("%d", &ack);
sendto(sockfd, &ack, sizeof(n), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
}
return 0;
}
