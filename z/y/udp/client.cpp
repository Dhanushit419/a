#include <bits/stdc++.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main(){
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0)cout<<"Failed  to create socket ! \n";
    sockaddr_in server,client;
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(3000);

    while(true){
        char buffer[1024];
        cout<<"Enter Message : ";
        scanf("%[^\n]%*c",buffer);
        sendto(sockfd,&buffer,sizeof(buffer),MSG_CONFIRM,(const sockaddr * )&server,sizeof(server));
        socklen_t i=sizeof(sockfd);
        int n=recvfrom(sockfd,&buffer,1024,MSG_WAITALL,(sockaddr *)&server,&i);
        buffer[n]='\0';
        cout<<"Message revced from Server : "<<buffer<<endl;
    }
    return 0;

}