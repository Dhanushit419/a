#include <bits/stdc++.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

void chat(int id);

int main(){
        int sockfd=socket(AF_INET,SOCK_STREAM,0);

    sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(3000);

    if(sockfd<0){
        cout<<"Socket creation failed"<<endl;
    }
    if(connect(sockfd,(const sockaddr*)&server,sizeof(server))<0){
        cout<<"Not connected "<<endl;
    }
    else{
        cout<<"Connected to the server ! "<<endl;
    }

    chat(sockfd);
    close(sockfd);
}

void chat(int conn){
    char buffer[1024];
    cout<<"Enter Your Message : "<<endl;
    while(true){
        scanf("%[^\n]%*c",buffer);
        if(strcmp("exit",buffer)==0){
            break;
        }
        write(conn,&buffer,sizeof(buffer));
        read(conn,&buffer,sizeof(buffer));
        cout<<"Message from server : "<<buffer<<endl<<"Enter Reply : ";
    }
}