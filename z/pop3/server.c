//pop3server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 2345
#define MAX_BUFFER_SIZE 1024
#define MAX_MAILBOX_SIZE 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[MAX_BUFFER_SIZE];
    char mailbox[MAX_MAILBOX_SIZE];

    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        exit(1);
    }

    // Initialize the server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

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

    printf("POP3 Server listening on port %d\n", SERVER_PORT);

    while (1) {
        // Accept a connection from a client
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("accept");
            continue;
        }

        printf("Client connected\n");

        // Server greeting
        send(client_socket, "+OK POP3 Server ready\r\n", 25, 0);

        // Initialize the mailbox with a test email
        strcpy(mailbox, "From: sender@example.com\r\n");
        strcat(mailbox, "To: recipient@example.com\r\n");
        strcat(mailbox, "Subject: Test Email\r\n");
        strcat(mailbox, "\r\n");
        strcat(mailbox, "This is a test email.\r\n");

        while (1) {
            // Receive client commands
            ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
            if (bytes_received <= 0) {
                break;
            }
            buffer[bytes_received - 2] = '\0';  // Fix: Remove '\r\n' from the end of the command

            // Implement basic POP3 commands
            if (strncmp(buffer, "USER", 4) == 0) {
                send(client_socket, "+OK User accepted\r\n", 19, 0);
            } else if (strncmp(buffer, "PASS", 4) == 0) {
                send(client_socket, "+OK Password accepted\r\n", 24, 0);
            } else if (strncmp(buffer, "LIST", 4) == 0) {
                char list_response[256];
                snprintf(list_response, sizeof(list_response), "+OK 1 message (100 bytes)\r\n");
                send(client_socket, list_response, strlen(list_response), 0);
            } else if (strncmp(buffer, "RETR 1", 6) == 0) {
                send(client_socket, "+OK\r\n", 4, 0);
                send(client_socket, mailbox, strlen(mailbox), 0);
                send(client_socket, ".\r\n", 3, 0);
            } else if (strncmp(buffer, "QUIT", 4) == 0) {
                send(client_socket, "+OK POP3 Server signing off\r\n", 29, 0);
                break;
            } else {
                send(client_socket, "-ERR Unknown command\r\n", 22, 0);
            }
        }

        // Close the client socket
        close(client_socket);
        printf("Client disconnected\n");
    }

    close(server_socket);
    return 0;
}

