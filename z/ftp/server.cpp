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
    server.sin_port = htons(3009);

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
    }
    else
    {
        printf("Client is connected\n");
    }

    string filename;

    char buffer[1024];
    int n=read(conn,&buffer,sizeof(buffer));
    if(n<0){
        cout << "Error reading file name from client" << endl;
        close(conn);
        close(sockfd);
        return 1;
    }
    buffer[sizeof(buffer)]='\0';
    filename=buffer;

    cout<<filename<<":-Reading \n";
    FILE* file=fopen(buffer,"r");
    char data[1024];
    socklen_t len1=fread(data,1,sizeof(data),file);
    printf("%s",data);
    write(conn,&data,len1);
    cout<<"File read seithu client ku anupa patathu ";
    close(sockfd);
    return 0;
}
