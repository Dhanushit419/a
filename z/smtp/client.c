#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345
#define MAX_BUFFER_SIZE 1024
void send_email(int client_socket) {
char buffer[MAX_BUFFER_SIZE];
// Sender and recipient email addresses
const char *from_email = "sender@example.com";
const char *to_email = "recipient@example.com";
// Email subject and body
const char *subject = "Hello, SMTP!";
const char *body = "This is a test email sent via SMTP client.";
// Construct and send the email
snprintf(buffer, sizeof(buffer), "MAIL FROM: <%s>\r\n", from_email);
send(client_socket, buffer, strlen(buffer), 0);
usleep(100000); // Wait briefly for the server to respond
snprintf(buffer, sizeof(buffer), "RCPT TO: <%s>\r\n", to_email);
send(client_socket, buffer, strlen(buffer), 0);
usleep(100000);
snprintf(buffer, sizeof(buffer), "DATA\r\n");
send(client_socket, buffer, strlen(buffer), 0);
usleep(100000);
snprintf(buffer, sizeof(buffer), "Subject: %s\r\n", subject);
send(client_socket, buffer, strlen(buffer), 0);
snprintf(buffer, sizeof(buffer), "From: %s\r\n", from_email);
send(client_socket, buffer, strlen(buffer), 0);
snprintf(buffer, sizeof(buffer), "To: %s\r\n", to_email);
send(client_socket, buffer, strlen(buffer), 0);
snprintf(buffer, sizeof(buffer), "\r\n%s\r\n.\r\n", body);
send(client_socket, buffer, strlen(buffer), 0);
usleep(100000);
// End the email transmission
snprintf(buffer, sizeof(buffer), "QUIT\r\n");
send(client_socket, buffer, strlen(buffer), 0);
usleep(100000);}
int main() {
int client_socket;
struct sockaddr_in server_addr;
// Create a socket
client_socket = socket(AF_INET, SOCK_STREAM, 0);
if (client_socket == -1) {
perror("socket");
exit(1);
}
// Initialize the server address structure
memset(&server_addr, 0, sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(SERVER_PORT);
server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
// Connect to the server
if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
perror("connect");
close(client_socket);
exit(1);
}
printf("Connected to SMTP Server\n");
// Send the email
send_email(client_socket);
// Close the client socket
close(client_socket);
printf("Email sent to the SMTP Server\n");
return 0;
}
