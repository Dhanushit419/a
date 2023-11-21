#include <bits/stdc++.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctime>

using namespace std;
void chat(int id);
void echo(int id);
void date(int id);
void math(int id);
sockaddr_in server,client;


int main(){
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0)cout<<"Failed  to create socket ! \n";
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(3000);

    if(bind(sockfd,(const sockaddr * )&server,sizeof(server))<0){
        cout<<"Bind failed \n";
        return -1;
    }
    

        char buffer[1024];
    while(true){
        socklen_t len=sizeof(client);
        int n=recvfrom(sockfd,&buffer,1024,MSG_WAITALL,(sockaddr *)&client,&len);
        buffer[n]='\0';
        cout<<"Datagram received from client : "<<buffer<<endl;
        if(strcmp("exit",buffer)==0)break;
        sendto(sockfd,&buffer,1024,MSG_CONFIRM,(const sockaddr*)&client,len);

    }
    
    math(sockfd);

    close(sockfd);
    return 0;
}

void echo(int sockfd){
    char buffer[1024];
    while(true){
        socklen_t len=sizeof(client);
        int n=recvfrom(sockfd,&buffer,1024,MSG_WAITALL,(sockaddr *)&client,&len);
        buffer[n]='\0';
        cout<<"Datagram received from client : "<<buffer<<endl;
        if(strcmp("exit",buffer)==0)break;
        sendto(sockfd,&buffer,1024,MSG_CONFIRM,(const sockaddr*)&client,len);

    }
}
void chat(int sockfd){
    char buffer[1024];
    while(true){
        socklen_t len=sizeof(client);
        int n=recvfrom(sockfd,&buffer,1024,MSG_WAITALL,(sockaddr *)&client,&len);
        buffer[n]='\0';
        cout<<"Datagram received from client : "<<buffer<<endl;
        if(strcmp("exit",buffer)==0)break;
        char msg[1024];
        scanf("%[^\n]%*c",msg);
        sendto(sockfd,&msg,1024,MSG_CONFIRM,(const sockaddr*)&client,len);

    }
}

void date(int sockfd){
    char buffer[1024];
    while(true){
        socklen_t len=sizeof(client);
        int n=recvfrom(sockfd,&buffer,1024,MSG_WAITALL,( sockaddr * )&client,&len);
        buffer[n]='\0';
        if(strcmp("date",buffer)==0){
            time_t cur=time(0);
            char * time_now=ctime(&cur);
            sendto(sockfd,time_now,strlen(time_now),MSG_CONFIRM,(const sockaddr * )&client,len);
        }
        else{
            if(strcmp("exit",buffer)==0)break;
            cout<<"Enter reply : ";
            char msg[1024];
            scanf("%[^\n]%*c",msg);
            sendto(sockfd,&msg,1024,MSG_CONFIRM,(const sockaddr * )&client,len);
        }
    }
}

void math(int sockfd){
    char buffer[1024];
    while(true){
        socklen_t len=sizeof(client);
        int n=recvfrom(sockfd,&buffer,1024,MSG_WAITALL,(sockaddr * )&client,&len);
        buffer[n]='\n';
        string first="";
        string second="";
        int op=-1;
        for(int i=0;buffer[i]!='\0';i++){
            if(op==-1){
                if(buffer[i]=='+')op=1;
                else if(buffer[i]=='-')op=2;
                else first+=buffer[i];
            }
            else second+=buffer[i];
        }
        int res;
        if(op==-1){
            char err[]="Error in expression ! ";
            sendto(sockfd,&err,size(err),MSG_CONFIRM,(const sockaddr*)&client,len);
            continue;
        }
        if(op==1)res=stoi(first)+stoi(second);
        else res=stoi(first)-stoi(second);
        string ans=to_string(res);

        for(int i=0;i<ans.size();i++){
            buffer[i]=ans[i];
        }
        buffer[ans.size()]='\0';
        sendto(sockfd,&buffer,1024,MSG_CONFIRM,(const sockaddr*)&client,len);

    }
}