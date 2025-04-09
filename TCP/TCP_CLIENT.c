//TCP CLIENT PROGRAM


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main() {
struct sockaddr_in server;
int client_socket, connsts;
char rBuf[100] = "", sBuf[100] = ""; 
client_socket = socket(AF_INET, SOCK_STREAM, 0);
if (client_socket == -1) {
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");
server.sin_family = AF_INET;
server.sin_port = 6060;
server.sin_addr.s_addr = inet_addr("127.0.0.1");
printf("\nClient ready....\n");
connsts = connect(client_socket, (struct sockaddr *)&server, sizeof(server)); 
if (connsts != 0) {
printf("connection with the server failed...\n");
exit(0);
}
else
printf("connected to the server..\n");
while (1) { 
printf("\nClient: "); 
gets(sBuf);
send(client_socket, sBuf, sizeof(sBuf), 0); 
if (strcmp(sBuf, "end") == 0)
break;
recv(client_socket, rBuf, sizeof(rBuf), 0);
printf("\nServer: %s", rBuf);
if (strcmp(rBuf, "end") == 0)
break;
printf("\n");
}
close(client_socket);
return 0;
}
