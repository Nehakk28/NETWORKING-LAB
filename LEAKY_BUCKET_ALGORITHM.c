// LEAKY BUCKET ALGORITHM PROGRAM

#include <stdio.h>
int main() {
int incoming, outgoing, buck_size, n, store = 0; 
printf("Enter the bucket size (Bytes): ");
scanf("%d", &buck_size);
printf("Enter the outgoing rate (Bytes per second): ");
scanf("%d", &outgoing);
printf("Enter the number of packets: ");
scanf("%d", &n);
printf("-----------\n");
while(n != 0) {
printf("Enter the incoming packet size (Bytes): ");
scanf("%d", &incoming);
if(incoming <= (buck_size - store)) {
store += incoming;
printf("Current Bucket buffer size %d out of %d\n", store, buck_size);
} else {
printf("Dropped %d bytes of data from Packet\n", incoming - (buck_size - store));
printf("Current Bucket buffer size %d out of %d\n", buck_size - store, buck_size);
store = buck_size;
}
store = store - outgoing;
if (store < 0) {
store = 0;
}
printf("After outgoing %d bytes left out of %d in buffer\n", store, buck_size);
printf("----------------------------\n"); 
n--;
}
return 0;
}
