//
//  ClientNETIO.cpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/9.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#include "ClientNETIO.hpp"
#define DEFAULT_PORT 6666

ClientNETIO::ClientNETIO(){

    int connfd = 0;
    
    int cLen =0 ;
    
    struct sockaddr_in client;
    
    char* serverIP="127.0.0.1";
    
    client.sin_family=AF_INET;
    
    client.sin_port= htons(DEFAULT_PORT);
    
client.sin_addr.s_addr=inet_addr(serverIP);
    
    connfd=socket(AF_INET, SOCK_STREAM, 0);
    
    if (connfd<0) {
        perror("socket");
        return;
    }
    
    if (connect(connfd, (struct sockaddr*)&client, sizeof(client))<0) {
        perror("connet");
        
        return;
    }

    
    char buffer[1024];
    
    
    bzero(buffer, sizeof(buffer));
    
    recv(connfd, buffer, 1024, 0);
    
    printf("recv:%s\n",buffer);
    
    strcpy(buffer, "this is client!\n");
    
    send(connfd, buffer, 1024, 0);
    
    while (1) {
        bzero(buffer, sizeof(buffer));
        
        scanf("%s",buffer);
        
        int p = strlen(buffer);
        
        buffer[p]='\0';
        
        send(connfd, buffer, 1024, 0);
        
        printf("i have send buffer\n");
    }
    
    close(connfd);
    
}


ClientNETIO::~ClientNETIO()
{

}




