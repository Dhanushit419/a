#include <bits/stdc++.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <ctime>

using namespace std;

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in client, server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3001);

    if (bind(sockfd, (const sockaddr *)&server, sizeof(server)) < 0) {
        printf("Error in binding...\n");
        return -1;
    } 
    
    if (listen(sockfd, 4) < 0) {
        printf("Listen failed\n");
        return -1;
    } else {
        printf("Server is listening...\n");
    }
    
    socklen_t len = sizeof(client);
    while (true) {
    int c_socket;
    c_socket = accept(sockfd, (sockaddr *)&client, &len);
    pid_t p1 = fork();
    if (p1 == 0) {
    if (c_socket < 0) {
        printf("Client Connection Failed\n");
    } else {
        printf("Client is connected\n");
    }
    char buffer[100];
    strcpy(buffer, "You are connected to the server.\n");
    write(c_socket, &buffer, sizeof(buffer));
            while (true)
            {
        
                read(c_socket, &buffer, sizeof(buffer));
                cout << "Mesage from client : " << buffer << endl;
                if (strcmp(buffer, "exit") == 0)
                {
                    cout << "client disconected \n";
                    break;
                }
                printf("Enter reply : ");
                scanf("%[^\n]%*c", buffer);       
                write(c_socket, &buffer, sizeof(buffer));
        if (strcmp(buffer, "exit") == 0) {
            printf("You disconnected\n");
            break;
        }
        printf("You : %s\n", buffer);

            }
        close(c_socket);
    } else {
        close(c_socket);
    }
    }
    return 0;
}