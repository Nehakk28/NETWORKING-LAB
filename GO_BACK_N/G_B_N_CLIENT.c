// GO BACK N ARQ PROTOCOL PROGRAM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define PORT 9060
#define FRAME_SIZE 20
void send_ack(int sock, int frame_no) {
char ack[FRAME_SIZE];
snprintf(ack, sizeof(ack), "ACK-%d", frame_no);
printf("Sending ACK: %s\n", ack);
write(sock, ack, strlen(ack) + 1);
}
int main() {
int client_sock;
struct sockaddr_in server_addr;
client_sock = socket(AF_INET, SOCK_STREAM, 0);
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
printf("Connected to server! Ready to receive frames.\n\n");
char frame[FRAME_SIZE];
int expected_frame = 0;
int loss_frame_no = 2;
int loss_simulated = 0;
while (1) {
memset(frame, 0, sizeof(frame));
int bytes_read = read(client_sock, frame, sizeof(frame));
if (bytes_read <= 0) {
break;
}
printf("Received: %s\n", frame);
int frame_no;
sscanf(frame, "Frame-%d", &frame_no);
if (frame_no == expected_frame) {
if (frame_no == loss_frame_no && !loss_simulated) {
printf("Simulating ACK loss for frame-%d! Not sending ACK.\n\n", frame_no);
loss_simulated = 1; 
continue;
}
send_ack(client_sock, frame_no);
expected_frame++;
} else {
printf("Out of order frame! Expected: %d, Got: %d. Discarding.\n\n", expected_frame, frame_no);
}
}
printf("All frames received. Closing connection.\n");
close(client_sock);
return 0;
}
