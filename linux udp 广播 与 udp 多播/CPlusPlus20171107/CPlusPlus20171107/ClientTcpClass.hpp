//
//  ClientTcpClass.hpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/8.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#ifndef ClientTcpClass_hpp
#define ClientTcpClass_hpp


#include <arpa/inet.h>

#include <unistd.h>
#include <netinet/in.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <string>
#include <stdlib.h>

#include <stdio.h>

#define MAX_LINE 4096


class ClientTcpClass{

public:
    int sockfd, n;
    char recline[MAX_LINE],sendline[MAX_LINE];
    struct sockaddr_in servaddr;
    char* serverIP;
    struct sockaddr_in addrMyself;
    bool fengZhuangBao;
    bool fengZhuangJieGouTi;
    bool readAndWrite;
    ClientTcpClass();
    ~ClientTcpClass();
    
    



};




#endif /* ClientTcpClass_hpp */
