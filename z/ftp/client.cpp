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
    server.sin_port=htons(3009);

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

    cout<<"Enter filename with extention : ";
    scanf("%[^\n]%*c",buffer);

    write(sockfd,&buffer,sizeof(buffer));
    int len1=read(sockfd,&buffer,sizeof(buffer));
    cout<<"Data on file requested : "<<buffer;
    buffer[len1]='\0';
    FILE* file=fopen("newfile.txt","w");
    fwrite(buffer,1,len1,file);
    cout<<"Data writen on file :-)";

close(sockfd);
return 0;
}