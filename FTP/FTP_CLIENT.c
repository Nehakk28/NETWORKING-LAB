// FTP CLIENT PROGRAM

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
char r_Buf[10000];
void get_function(int csd, struct sockaddr_in data, char *data_addr);
int main(int argc, char *argv[]) {
if (argc < 3) {
printf("Usage: ./client <server IP> <control port> \n");
exit(1);
}
int csd, cport;
char command[100];
struct sockaddr_in servaddr, data;
cport = atoi(argv[2]);
csd = socket(AF_INET, SOCK_STREAM, 0);
if (csd < 0) {
perror("Error creating socket");
exit(1);
}
printf("Socket created\n");
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = inet_addr(argv[1]);
servaddr.sin_port = htons(cport);
if (connect(csd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
perror("Error in connection");
exit(1);
}
printf("Connected to server\n");
while (1) {
printf("Enter 'get' for receiving file from server\nEnter 'close' for closing the connection\n");
scanf("%s", command);
if (strcmp(command, "get") == 0) {
send(csd, command, sizeof(command), 0);
get_function(csd, data, argv[1]);
} else if (strcmp(command, "close") == 0) {
send(csd, command, sizeof(command), 0);
break;
} else {
printf("Invalid command\n");
}
}
close(csd);
return 0;
}
void get_function(int csd, struct sockaddr_in data, char *data_addr) {
char name[256];
char valid[10];
printf("Enter filename: ");
scanf("%s", name);
printf("Name of file=%s\n", name);
send(csd, name, sizeof(name), 0);
recv(csd, valid, sizeof(valid), 0);
if (strcmp(valid, "error") == 0) {
printf("FILE NOT FOUND PROCESS ID = %d\n", getpid());
return;
}
int dd = socket(AF_INET, SOCK_STREAM, 0);
if (dd < 0) {
perror("Error creating data socket");
exit(1);
}
data.sin_family = AF_INET;
data.sin_addr.s_addr = inet_addr(data_addr);
data.sin_port = htons(8050);
if (connect(dd, (struct sockaddr *)&data, sizeof(data)) < 0) {
perror("Error in connection of data socket");
close(dd);
return;
}
if (recv(dd, r_Buf, sizeof(r_Buf), 0) < 0) {
printf("Failed to receive file\n");
} else {
FILE *fp = fopen(name, "w");
if (fp == NULL) {
perror("Error opening file");
close(dd);
return;
}
fprintf(fp, "%s", r_Buf);
fclose(fp);
printf("\n%s\n",r_Buf);
printf("File received successfully\n\n");
}
close(dd);
}
