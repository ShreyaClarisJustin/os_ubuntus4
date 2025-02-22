//file correct code. in record
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 7012
#define MAX_BUFFER_SIZE 1024
int main() {
int client_socket;
struct sockaddr_in server_addr;
char filename[MAX_BUFFER_SIZE];
ssize_t bytes_received;
// Create socket
if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
perror("Error creating socket");
exit(EXIT_FAILURE);
}
// Initialize server address struct
memset(&server_addr, 0, sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
// Connect to server
if (connect(client_socket, (struct sockaddr*)&server_addr,sizeof(server_addr))<0){
	perror("Error connecting to server");
	exit(EXIT_FAILURE);
}
// Get filename from user input
printf("Enter filename: ");
fgets(filename, sizeof(filename), stdin);
filename[strcspn(filename, "\n")] = '\0'; // Remove newline character
// Send filename to server

if (send(client_socket, filename, strlen(filename), 0) < 0) {

perror("Error sending filename to server");
exit(EXIT_FAILURE);
}
// Receive data from server
char buffer[MAX_BUFFER_SIZE];
while ((bytes_received = recv(client_socket,buffer,sizeof(buffer),0))>0){
	fwrite(buffer, 1, bytes_received, stdout);
}
if(bytes_received<0){
	perror("Error receiving data from server");
	exit(EXIT_FAILURE);
}
// Close socket
close(client_socket);
return 0;
}
