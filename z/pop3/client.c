//pop3client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 2345
#define MAX_BUFFER_SIZE 1024
int main() {
int client_socket;
struct sockaddr_in server_addr;
char buffer[MAX_BUFFER_SIZE];
// Create a socket
client_socket = socket(AF_INET, SOCK_STREAM, 0);if (client_socket == -1) {
perror("socket");
exit(1);
}
// Initialize the server address structure
memset(&server_addr, 0, sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(SERVER_PORT);
server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
// Connect to the POP3 server
if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
perror("connect");
close(client_socket);
exit(1);
}
printf("Connected to POP3 Server\n");
// Receive and display the server greeting
recv(client_socket, buffer, sizeof(buffer), 0);
printf("%s", buffer);
// Send user and password
send(client_socket, "USER user123\r\n", 14, 0);
recv(client_socket, buffer, sizeof(buffer), 0);
printf("%s", buffer);
send(client_socket, "PASS pass123\r\n", 14, 0);
recv(client_socket, buffer, sizeof(buffer), 0);
printf("%s", buffer);
// List emails
send(client_socket, "LIST\r\n", 6, 0);
recv(client_socket, buffer, sizeof(buffer), 0);
printf("%s", buffer);
// Retrieve an email
send(client_socket, "RETR 1\r\n", 8, 0);
recv(client_socket, buffer, sizeof(buffer), 0);
printf("%s", buffer);
// Quit
send(client_socket, "QUIT\r\n", 6, 0);
recv(client_socket, buffer, sizeof(buffer), 0);
printf("%s", buffer);
// Close the connection
close(client_socket);
printf("Disconnected from POP3 Server\n");
return 0;
}
