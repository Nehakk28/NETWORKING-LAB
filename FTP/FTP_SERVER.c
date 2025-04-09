// FTP SERVER PROGRAM

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
char send_buf[10000];
void send_file(FILE *fp) {
 char ch;
 int i = 0;
 while ((ch = fgetc(fp)) != EOF) {
 send_buf[i++] = ch;
 }
 send_buf[i] = '\0';
}
int main(int argc, char *argv[]) {
 if (argc < 2) {
 printf("Usage: ./server <control port>\n");
 exit(1);
 }
 struct sockaddr_in client, control, data, data_client;
 FILE *fp;
 int lfd, confd, fd, confd2;
 char rBuf[100] = "";
 int port = atoi(argv[1]);
 lfd = socket(AF_INET, SOCK_STREAM, 0);
 if (lfd < 0) {
 perror("Error creating socket");
 exit(1);
 }
 control.sin_family = AF_INET;
 control.sin_port = htons(port);
 control.sin_addr.s_addr = INADDR_ANY;
 if (bind(lfd, (struct sockaddr *)&control, sizeof(control)) < 0) {
 perror("Bind failed");
 close(lfd);
 exit(1);
 }
 listen(lfd, 5);
 printf("\nServer ready, waiting for client....\n");
 socklen_t n = sizeof(client);
 confd = accept(lfd, (struct sockaddr *)&client, &n);
 if (confd < 0) {
 perror("Accept failed");
 close(lfd);
 exit(1);
 }
 printf("\nClient connected....\n");
 while (1) {
 recv(confd, rBuf, sizeof(rBuf), 0);
 if (strcmp(rBuf, "get") == 0) {
 printf("Client command: %s\n", rBuf);
 recv(confd, rBuf, sizeof(rBuf), 0);
 printf("\nServer received the file to fetch: %s\n", rBuf);
 fp = fopen(rBuf, "r");
 if (fp == NULL) {
 send(confd, "error", sizeof("error"), 0);
 printf("\nError in opening file: %s\n", rBuf);
 } 
 else {
 send(confd, "success", sizeof("success"), 0);
 fd = socket(AF_INET, SOCK_STREAM, 0);
 if (fd < 0) {
 perror("Error creating data socket");
 exit(1);
 }
 data.sin_family = AF_INET;
 data.sin_addr.s_addr = INADDR_ANY;
 data.sin_port = htons(8050);
 if (bind(fd, (struct sockaddr *)&data, sizeof(data)) < 0) {
 perror("Bind failed for data socket");
 close(fd);
 exit(1);
 }
 listen(fd, 5);
 printf("\nServer ready, waiting for client to connect to data socket\n");
 n = sizeof(data_client);
 confd2 = accept(fd, (struct sockaddr *)&data_client, &n);
 if (confd2 < 0) {
 perror("Accept failed for data socket");
 close(fd);
 exit(1);
 }
 printf("\nClient connected to data socket\n");
 send_file(fp);
 if (send(confd2, send_buf, sizeof(send_buf), 0) < 0) {
 printf("Sending failed\n");
 } else {
 printf("File sent successfully\n");
 }
 fclose(fp);
 close(confd2);
 close(fd);
 }
 } else if (strcmp(rBuf, "close") == 0) {
 printf("\nClient command: %s\n", rBuf);
 printf("\nClient disconnected and server closed\n");
 break;
 }
 }
 close(confd);
 close(lfd);
 return 0;
}
