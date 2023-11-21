#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main(){
    
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
for(int i=0;i<3;i++){
    char req[1024];
        snprintf(req, sizeof(req), "HTTP GET 1.1/1.1 \r\r\nRequest number : %d", i + 1);

        send(sockfd, req, sizeof(req), 0);
        char res[1024];
        recv(sockfd, res, sizeof(res), 0);
        cout<<"\nResponce from server :"<<res<<endl;
        
    }
    close(sockfd);
    return 0;
}