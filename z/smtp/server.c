//smtpserver.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#define PORT 12345
#define MAX_BUFFER_SIZE 1024
void create_email_file(const char *email_content) {
time_t now;
struct tm *timeinfo;
char filename[256];
FILE *email_file;
time(&now);
timeinfo = localtime(&now);
// Generate a filename based on the timestamp
strftime(filename, sizeof(filename), "email_%Y%m%d%H%M%S.txt", timeinfo);
// Create the email file and save the content
email_file = fopen(filename, "w");
if (email_file == NULL) {
perror("fopen");
return;
}
fprintf(email_file, "%s", email_content);
fclose(email_file);
printf("Email saved to %s\n", filename);
}
int main() {
int server_socket, client_socket;
struct sockaddr_in server_addr, client_addr;
socklen_t client_addr_len = sizeof(client_addr);
char buffer[MAX_BUFFER_SIZE];
char email_content[MAX_BUFFER_SIZE];
// Create a socket
server_socket = socket(AF_INET, SOCK_STREAM, 0);
if (server_socket == -1) {
perror("socket");
exit(1);
}
// Initialize the server address structure
memset(&server_addr, 0, sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);server_addr.sin_addr.s_addr = INADDR_ANY;
// Bind the socket to the server address
if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
perror("bind");
exit(1);
}
// Listen for incoming connections
if (listen(server_socket, 5) == -1) {
perror("listen");
exit(1);
}
printf("SMTP Server listening on port %d\n", PORT);
while (1) {
// Accept a connection from a client
client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
if (client_socket == -1) {
perror("accept");
continue;
}
printf("Client connected\n");
// Initialize email content
memset(email_content, 0, sizeof(email_content));
// Receive and store the email
while (1) {
ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
if (bytes_received <= 0) {
break;
}
// Append received data to email content
strncat(email_content, buffer, bytes_received);
// Check for end of email
if (strstr(email_content, "\r\n.\r\n") != NULL) {
break;
}
}
// Create a file and save the email
create_email_file(email_content);
close(client_socket);
printf("Email received and saved\n");
}
close(server_socket);
return 0;
}
