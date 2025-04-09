// LINK STATE ROUTING PROTOCOL PROGRAM 

#include <stdio.h>
#include <limits.h>
void main() {
int n, i, j, adj[50][50], d, max = 1000;
printf("\nEnter the Number of Nodes: ");
scanf("%d",&n);
printf("Enter the cost between Nodes:\n");
for (i = 0; i < n; i++) {
for (j = 0; j < n; j++) {
if (i == j)
adj[i][j] = 0;
else {
printf("Cost from %d -> %d: ", i + 1, j + 1);
scanf("%d", &adj[i][j]);
}
}
}
int dist[n], visited[n], round, v, src;
for (i = 0; i < n; i++) {
dist[i] = max;
visited[i] = 0;
}
printf("\nEnter the source Node: ");
scanf("%d", &src);
src -= 1;
dist[src] = 0;
int nxhop[n];
for (i = 0; i < n; i++)
nxhop[i] = 0;
for (round = 0; round < n - 1; round++) {
int min = max, min_index;
for (v = 0; v < n; v++) {
if (visited[v] == 0 && dist[v] < min) {
min = dist[v];
min_index = v;
}
}
visited[min_index] = 1;
for (d = 0; d < n; d++) {
if (!visited[d] && adj[min_index][d] && dist[min_index] != max
&& dist[min_index] + adj[min_index][d] < dist[d]) {
dist[d] = dist[min_index] + adj[min_index][d];
if (min_index != src)
nxhop[d] = min_index + 1;
}
}
if (min_index == src) {
printf("\nRouting Table of Node %d", src + 1);
printf("\nDestination\tCost\tNext Hop\n");
for (i = 0; i < n; i++) {
if (dist[i] == 0)
printf("%d\t\t-\t-\n", i + 1);
else
printf("%d\t\t%d\t-\n", i + 1, dist[i]);
}
}
}
printf("\n");
printf("\nAfter Applying Dijkstra's Algorithm:\n");
printf("\nRouting Table of Node %d", src + 1);
printf("\nDestination\tCost\tNext Hop\n");
for (i = 0; i < n; i++) {
printf("%d\t\t%d\t\t", i + 1, dist[i]);
if (nxhop[i] == 0)
printf("-\n");
else
printf("%d\n", nxhop[i]);
}
for (i = 1; i < n; i++)
printf("The cost of the shortest path from router %d to %d is %d\n",src + 1, i + 1, dist[i]);
}
