#include <bits/stdc++.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main(){
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0)cout<<"Eroro in creation !\n";

    sockaddr_in server,client;
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(3001);

    if(bind(sockfd,(const sockaddr * )&server,sizeof(server))<0){
        cout<<"Bind failed \n";
        return -1;
    }else cout<<"binded\n";
    char buffer[1024];
    while(true){
        socklen_t len=sizeof(client);
        
        int n=recvfrom(sockfd,&buffer,sizeof(buffer),MSG_WAITALL,(sockaddr*)&client,&len);
        buffer[n]='\0';
        cout<<"Mesage from user : ";
        cout<<buffer<<endl;
        char msg[1024];
        cout<<"enter reply : ";
        scanf("%[^\n]%*c",msg);
        sendto(sockfd,&msg,sizeof(msg),MSG_CONFIRM,(const sockaddr*)&client,len);
    }

    return 0;

}