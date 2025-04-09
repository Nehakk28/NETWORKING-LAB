// UDP CLIENT PROGRAM

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
struct sockaddr_in server;
int sockfd, n;
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
server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
printf("\nClient ready….\n");
n = sizeof server; 
while(1) {
printf("\nClient:");
gets(sBuf); 
sendto(sockfd, sBuf, sizeof sBuf, 0, (struct sockaddr *)&server, n); 
if(strcmp(sBuf, "end") == 0) 
break;
recvfrom(sockfd, rBuf, sizeof rBuf, 0, (struct sockaddr*)&server, &n);
printf("\nServer:%s", rBuf); 
if(strcmp(rBuf, "end") == 0) 
break;
}
close(sockfd); 
}
