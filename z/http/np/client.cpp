#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main(){
    for(int i=0;i<3;i++){
        int sockfd=socket(AF_INET,SOCK_STREAM,0);
        if(sockfd<0)cout<<"Creation failed ! \n";

        sockaddr_in server;

        server.sin_family=AF_INET;
        server.sin_addr.s_addr=INADDR_ANY;
        server.sin_port=htons(3005);

        if(connect(sockfd,(const sockaddr*)&server,sizeof(server))<0){
            cout<<"Conection failure \n";
        }
        else cout<<"Conected with server !\n";

        char req[]="HTTP GET 1.1/1.1 \r\r";
        send(sockfd, req, sizeof(req), 0);
        char res[1024];
        recv(sockfd, res, sizeof(res), 0);
        cout<<"Responce from server :"<<res<<endl;
        close(sockfd);
    }
}