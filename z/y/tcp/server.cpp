#include<bits/stdc++.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<ctime>
#include<unistd.h>

using namespace std;

void chat(int id);
void chatMath(int id);
void date(int id);
void echo(int id);

int main(){

    int sockfd=socket(AF_INET,SOCK_STREAM,0);

    sockaddr_in server,client;
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(3000);

    

    if(sockfd<0){
        cout<<"Socket Creation Failed ! ";
        return -1;
    }

    if(bind(sockfd,(const sockaddr*)&server,sizeof(server))<0){
        cout<<"Binding failed !";
        return -1;
    }

    if(listen(sockfd,4)<0){
        cout<<"Listen failed ! ";
        return -1;
    }
    else {
        cout<<"Server Listening to port 3000 "<<endl;
    }

    socklen_t len=sizeof(client);

    int conn= accept(sockfd,(sockaddr * )&client,&len);
    if(conn<0)cout<<"Client connection failed !";
    else cout<<"Client connected succesfully !"<<endl;

    date(conn);
    close(sockfd);
    return 0;
}

void echo(int conn){
    char buffer[1024];
    while(true){
        read(conn,&buffer,sizeof(buffer));
        cout<<"Message from client : "<<buffer<<endl;
        write(conn,&buffer,sizeof(buffer));
        if(strcmp("exit",buffer)==0){
            break;
        }
    }
}

void chat(int conn){
    char buffer[1024];
    while(true){
        read(conn,&buffer,sizeof(buffer));
        cout<<"Message from client : "<<buffer<<endl;
        scanf("%[^\n]%*c",buffer);
        write(conn,&buffer,sizeof(buffer));
        if(strcmp("exit",buffer)==0){
            break;
        }
    }
}

void date(int conn){
    char buffer[1024];
    while(true){
        read(conn,&buffer,sizeof(buffer));
        cout<<"Request from client : "<<buffer<<endl;
        if(strcmp("date",buffer)==0){
            time_t cur=time(0);
            char * time_now=ctime(&cur);
            write(conn,time_now,strlen(time_now));
        }
        else{
            scanf("%[^\n]%*c",buffer);
            write(conn,&buffer,sizeof(buffer));
            if(strcmp("exit",buffer)==0)break;

        }
    }
}

void chatMath(int conn) {
    char buffer[1024];
    while(true) {
        read(conn, &buffer, sizeof(buffer));
        printf("Message from client : %s\n",buffer);
        string first = "";
        string second = "";
        int op = -1;
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (op == -1) {
                if (buffer[i] == '+') op = 1;
                else if (buffer[i] == '-') op = 2;
                else if (buffer[i] == '*') op = 3;
                else if (buffer[i] == '/') op = 4;
                else first += buffer[i];
            } else {
                second += buffer[i];
            }
        }
        if (op == -1) {
            char errMsg[] = "Invalid expression (Valid format : Num + Num)\0";
            write(conn, &errMsg, sizeof(errMsg));
            continue;
        }
        int f = stoi(first);
        int s = stoi(second);
        int res = op == 1 ? f + s : f - s;
        string ans = to_string(res);
        for (int i = 0; i < ans.size(); i++) {
            buffer[i] = ans[i];
        }
        buffer[ans.size()] = '\0';
        printf("Result calculated and sent to client\n");
        write(conn, &buffer, sizeof(buffer));
        if (strcmp("exit", buffer) == 0) {
            break;
        }
    }
}