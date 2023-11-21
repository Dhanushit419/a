#include <bits/stdc++.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in client, server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3005);

    if (bind(sockfd, (const sockaddr *) &server, sizeof(server)) < 0) {
        cout << "Error in binding socket" << endl;
    } 

    if (listen(sockfd, 4) < 0) {
        cout << "Not listening" << endl;
    } else {
        cout << "Listening on PORT 3000" << endl;
    }

    while(true){
        socklen_t len=sizeof(client);
        int conn=accept(sockfd,(sockaddr*)&client,&len);
        printf("Conection acepted with client : %s:%d",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
        while(true){
        char buffer[1024];
        int n=read(conn,&buffer,sizeof(buffer));
        if(n<=0){
            close(conn);
            printf("Conection closed with client : %s:%d\n\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
            break;
        }
        cout<<"Received request : "<<buffer<<endl;
        char res[]="Hi nan than ";
        write(conn,&res,sizeof(res));
        }
    }
    close(sockfd);
    return 0;
}