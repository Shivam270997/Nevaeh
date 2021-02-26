#include<unistd.h>
#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<string>
#include<arpa/inet.h>
#include<fstream>
using namespace std;
int main(int argc,char const *argv[])
{
        int server_fd,new_socket,valread,PORT;
        ofstream f;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        cout<<"Enter the port:-"<<endl;
        cin>>PORT;
        //creating socket file descriptor
        if((server_fd = socket(AF_INET,SOCK_STREAM,0))==0)
        {
                cerr<<"Socket Failed"<<endl;
                exit(EXIT_FAILURE);
        }
        if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt)))
                {
                        cerr<<"setsockopt"<<endl;
                        exit(EXIT_FAILURE);
                }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr=INADDR_ANY;
        address.sin_port=htons( PORT );

        cout<<"NOTE=>if u want to leave the chatting just write \"quit\" either on server side or client side as input during chatting"<<endl<<endl;
        if(bind(server_fd,(struct sockaddr *)&address,sizeof(address))<0)
        {
                cerr<<"bind failure"<<endl;
                exit(EXIT_FAILURE);
        }
        if(listen(server_fd,3)<0)
        {
                cerr<<"listen error"<<endl;
                exit(EXIT_FAILURE);
        }
        else
        {
                cout<<"Waiting for connection"<<endl;
        }
       if((new_socket = accept(server_fd,(struct sockaddr *)&address,(socklen_t*)&addrlen))<0)
        {
                cerr<<"Accept"<<endl;
                exit(EXIT_FAILURE);
        }
        cin.ignore();
        f.open("Server.txt");
        cout<<"\t Conversation starts"<<endl;
        f<<"Conversation starts"<<endl;
        while(1)
        {
                char msg[1024]={'\0'},buff[1024]={'\0'};
                int nRet=recv(new_socket,buff,1024,0);
                if(nRet == 0)
                {
                        cout<<"connection has been terminated by Client Side"<<endl;
                        f<<"connection is close by client side";
                        break;
                }
                cout<<"Msg from Client:- ";
                cout<<buff<<endl;
                f<<"msg from client:- "<<buff<<endl;
                cout<<"enter the u want to send to client"<<endl;
                cin.get(msg,1024);
                if(strcmp(msg,"quit")==0)
                {
                        cout<<"connection is terminatd by Server side"<<endl;
                        f<<"connection was terminated by the server"<<endl;
                        break;
                }
                write(new_socket,msg,strlen(msg));
                cout<<"msg sent.."<<endl;
                cin.ignore();
        }
        f.close();
}
