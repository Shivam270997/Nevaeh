#include <iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<string>

using namespace std;
int main(int argc ,char const *argv[])
{
        int PORT;
        int sock=0,valread;
        char c;
        struct sockaddr_in serv_addr;
        cout<<"Enter the port number:-";
        cin>>PORT;
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
                cin.ignore();
                cout<<"\t conversation starts"<<endl;
        while(1)
        {
                int u=0;
                char msg[1024]={'\0'},buff[1024]={'\0'};
                cout<<"Enter the msg u want to send"<<endl;
                cin.get(msg,1024);
                if(strcmp(msg,"quit")==0)
                {
                        cout<<"connection is terminated by Client side"<<endl;
                        break;
                }
                write(sock,msg,strlen(msg));
                cout<<"msg sent to server"<<endl;
                int nRet=recv(sock,buff,1024,0);
                if(nRet == 0)
                {
                        cout<<"Connection has been terminated by Server Side ";
                        exit(EXIT_FAILURE);
                }
                cout<<"Msg from Server:- "<<buff<<endl;
                cin.ignore();
        }
        close(sock);
}
