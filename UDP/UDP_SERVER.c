// UDP SERVER PROGRAM

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
void main() {
struct sockaddr_in client, server; 
int sockfd, n, bindsts; 
char rBuf[100] = "", sBuf[100] = "";
sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
if (sockfd == -1) { 
printf("socket creation failed...\n"); 
exit(0); 
} 
else
printf("Socket successfully created..\n"); 
server.sin_family = AF_INET; 
server.sin_port = 2025; 
server.sin_addr.s_addr = htonl(INADDR_ANY);
bindsts = bind(sockfd, (struct sockaddr *)&server, sizeof server); 
if (bindsts != 0) { 
printf("socket bind failed...\n"); 
exit(0); 
} 
else
printf("Socket successfully binded..\n"); 
printf("\nServer ready, waiting for client….\n"); 
n = sizeof client;
while(1) {
recvfrom(sockfd, rBuf, sizeof rBuf, 0, (struct sockaddr *)&client, &n); 
printf("\nClient:%s", rBuf); 
if(strcmp(rBuf, "end") == 0) 
break;
printf("\nServer:"); 
gets(sBuf); 
sendto(sockfd, sBuf, sizeof sBuf, 0, (struct sockaddr *)&client, n); 
if(strcmp(sBuf, "end") == 0) 
break;
}
close(sockfd); 
}
