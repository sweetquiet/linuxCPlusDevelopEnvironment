//
//  ClientPollNETIO.cpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/9.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#include "ClientPollNETIO.hpp"
#define MAXLINE 1024
#define DEFAULT_PORT 6666
#define max(a,b) (a>b)?a:b

static void handle_connection(int sockfd)
{
    char sendline[MAXLINE] ,recvline[MAXLINE];
    
    int maxfdp,stdineof;
    
    struct pollfd pfds[2];
    
    int n;
    
    /*
     添加连接描述符
     */
    
    pfds[0].fd=sockfd;
    pfds[0].events=POLLIN;
    
    /*
     添加标准输入描述符
     */
    
    pfds[1].fd=STDIN_FILENO;
    
    pfds[1]
    .events=POLLIN;
    
    while (1) {
        poll(pfds, 2, -1);
        if (pfds[0].revents&POLLIN) {
            n= read(sockfd, recvline, MAXLINE);
            
            if (n==0) {
                fprintf(stderr, "client: server is closed\n");
                close(sockfd);
            }
            
            write(STDOUT_FILENO, recvline, n);
        }
        
        /*
         测试标准输入是否准备好
         */
        
        if (pfds[1].revents&POLLIN) {
            n=read(STDIN_FILENO, sendline, MAXLINE);
            if (n==0) {
                shutdown(sockfd, SHUT_WR);
                continue;
            }
            write(sockfd, sendline, n);
        }
        
    }
}



ClientPollNETIO::ClientPollNETIO(){
    
    int connfd=0;
    int cLen=0;
    
    char* serverIP="127.0.0.1";
    
    struct sockaddr_in server;
    
    server.sin_family=AF_INET;
    
    server.sin_port=htons(DEFAULT_PORT);
    

    server.sin_addr.s_addr=inet_addr(serverIP);
    
    connfd=socket(AF_INET, SOCK_STREAM, 0);
    
    if (connfd<0) {
        perror("socket");
        return;
    }
    
    if (connect(connfd, (struct sockaddr*)&server, sizeof(server))<0) {
        perror("connect");
        return ;
    }
    
    /*处理描述连接符*/
    handle_connection(connfd);
}




ClientPollNETIO::~ClientPollNETIO()
{


}

