#include <iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<string>
#define PORT 8080
using namespace std;
int main(int argc ,char const *argv[])
{
        int sock=0,valread;
        struct sockaddr_in serv_addr;
        char buffer[1024];
        if((sock = socket(AF_INET,SOCK_STREAM,0))<0)
        {
                cerr<<"Socket Failed"<<endl;
                return -1;
        }

        serv_addr.sin_family =AF_INET;
        serv_addr.sin_port = htons(PORT);

        if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0)
        {
                cout<<"Invaild add"<<endl;
                return -1;
        }
        if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
        {
                cout<<"Connection failed"<<endl;
                return -1;
        }
        while(1)
        {
                cout<<"conversation starts"<<endl;
                cout<<"Enter the msg u want to send"<<endl;
                cin.get(buffer,1024);
                send(sock,buffer,1024,0);
                cout<<"msg sent to server"<<endl;
                memset(buffer,' ',sizeof(buffer));
                recv(sock,buffer,1024,0);
                cout<<"Msg from Server:- "<<buffer<<endl;
                memset(buffer,' ',sizeof(buffer));
        }
        close(sock);
}
