#include<bits/stdc++.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

using namespace std;

int main(){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);

    sockaddr_in server;

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(3000);

    if(sockfd<0){
        cout<<"Error in creation \n";
        return -1;
    }
    char buffer[1024];
    if(connect(sockfd,(const sockaddr*)&server,sizeof(server))<0){
        cout<<"Server conection eror \n";
        return -1;
    }
    else {
        cout<<"Conected to the server ! \n";
    }

    cout<<"Enter message : ";
    while(true){
        scanf("%[^\n]%*c",buffer);
        write(sockfd,&buffer,sizeof(buffer));
        if(strcmp(buffer,"exit")==0){
            cout<<"End\n";
            break;
        }
        cout<<"waiting for server : ";
        read(sockfd,&buffer,sizeof(buffer));
        cout<<"Reply from server : ";
        cout<<buffer<<endl;
        cout<<"Enter reply : ";
    }

    close(sockfd);
    return 0;
}