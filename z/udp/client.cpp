#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>

using namespace std;

int main(){
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0)cout<<"Eroro in creation !\n";
    sockaddr_in server,client;
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(300);
char buffer[1024];
cout<<"enter msg : ";
    while(true){
        
        scanf("%[^\n]%*c",buffer);
        sendto(sockfd,&buffer,1024,MSG_CONFIRM,(const sockaddr*)&server,sizeof(server));
        socklen_t len=sizeof(sockfd);
        int n=recvfrom(sockfd,&buffer,1024,MSG_WAITALL,( sockaddr*)&server,&len);
        buffer[n]='\0';
        cout<<"Reply :"<<buffer<<endl;
        cout<<"msg:";
    }
    close(sockfd);
    return 0;
}