// STOP AND WAIT CLIENT PROGRAM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
int main() {
int sockfd, n, i, len, ack;
struct sockaddr_in servaddr;
printf("\nSearching for server...\n");
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
memset(&servaddr, 0, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(6080);
n = -1;
sendto(sockfd, &n, sizeof (n), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
printf("\nServer connected successfully.\n");
printf("\nEnter the total number of frames: ");
scanf("%d", &n);
sendto(sockfd, &n, sizeof(n), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
for (i=1; i <= n; i++) {
ack=-1;
do {
printf("\nSending frames- %d", i);
sendto(sockfd, &i, sizeof(n), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
printf("\nwaiting for ACK...\n");
recvfrom(sockfd, &ack, sizeof(n), 0, (struct sockaddr *)&servaddr, &len);
if (ack == -1) {
printf("\nNegative ack recieved. resending...\n");
}
} while (ack == -1);
}
n=-99;
sendto(sockfd, &n, sizeof(n), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
printf("\nSuccessfully sent all the frames.\n");
close(sockfd);
return 0;
}
