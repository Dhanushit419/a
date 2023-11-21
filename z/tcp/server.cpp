#include <bits/stdc++.h>
#include <sys/types.h>
#include <ctime>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

using namespace std;

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server, client;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3000);

    if (sockfd < 0)
    {
        cout << "Error in socket creation \n";
        return -1;
    }

    if (bind(sockfd, (const sockaddr *)&server, sizeof(server)) < 0)
    {
        cout << "Eror in binding\n";
        return -1;
    }

    if (listen(sockfd, 4) < 0)
    {
        cout << "listen failed";
        return -1;
    }
    else
        cout << "Server Listening to port 3000\n";

    socklen_t len = sizeof(client);

        int conn = accept(sockfd, (sockaddr *)&client, &len);
            if (conn < 0)
            {
                printf("Client Connection Failed\n");
            }else
            {   printf("Client is connected\n");

            }
        char buffer[1024];
            while (true)
            {
        
                read(conn, &buffer, sizeof(buffer));
                cout << "Mesage from client : " << buffer << endl;
                if (strcmp(buffer, "exit") == 0)
                {
                    cout << "client disconected \n";
                    break;
                }
                printf("Enter reply : ");
                scanf("%[^\n]%*c", buffer);       
                write(conn, &buffer, sizeof(buffer));
        if (strcmp(buffer, "exit") == 0) {
            printf("You disconnected\n");
            break;
        }
        printf("You : %s\n", buffer);
            
    }
    close(sockfd);
    return 0;
}
