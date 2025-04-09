// GO BACK N ARQ PROTOCOL PROGRAM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#define PORT 9060
#define WINDOW_SIZE 2
#define TOTAL_FRAMES 5
#define FRAME_SIZE 20
void send_frame(int sock, int frame_no) {
char frame[FRAME_SIZE];
snprintf(frame, sizeof(frame), "Frame-%d", frame_no);
printf("Sending: %s\n", frame);
write(sock, frame, strlen(frame) + 1);
}
int wait_for_ack(int sock, int frame_no) {
char ack[FRAME_SIZE];
fd_set read_fds;
struct timeval timeout;
FD_ZERO(&read_fds);
FD_SET(sock, &read_fds);
timeout.tv_sec = 3; 
timeout.tv_usec = 0;
int retval = select(sock + 1, &read_fds, NULL, NULL, &timeout);
if (retval == -1) {
perror("select()");
return 0;
} else if (retval == 0) {
printf("Timeout! No ACK for frame-%d\n", frame_no);
return 0;
} else {
read(sock, ack, sizeof(ack));
printf("Received ACK: %s\n", ack);
return 1;
}
}
int main() {
int server_sock, client_sock;
struct sockaddr_in server_addr, client_addr;
socklen_t addr_size;
server_sock = socket(AF_INET, SOCK_STREAM, 0);
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
server_addr.sin_addr.s_addr = INADDR_ANY;
bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
listen(server_sock, 1);
printf("Server is up, waiting for connection...\n");
addr_size = sizeof(client_addr);
client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
printf("Client connected! Starting Go-Back-N Protocol (Window Size = %d)\n\n", WINDOW_SIZE);
int next_frame = 0;
while (next_frame < TOTAL_FRAMES) {
int sent_frames = 0;
for (int i = 0; i < WINDOW_SIZE && next_frame + i < TOTAL_FRAMES; i++) {
send_frame(client_sock, next_frame + i);
sent_frames++;
}
int acks_received = 0;
for (int i = 0; i < sent_frames; i++) {
int ack = wait_for_ack(client_sock, next_frame + i);
if (!ack) {
printf("Go-Back to frame-%d\n\n", next_frame + i);
next_frame += i; 
break;
}
acks_received++;
}
if (acks_received == sent_frames) {
next_frame += sent_frames;
}
}
printf("All frames sent successfully!\n");
close(client_sock);
close(server_sock);
return 0;
}
