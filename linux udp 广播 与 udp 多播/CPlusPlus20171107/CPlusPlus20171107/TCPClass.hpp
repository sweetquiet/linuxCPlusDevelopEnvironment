//
//  TCPClass.hpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/8.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#ifndef TCPClass_hpp
#define TCPClass_hpp


#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <string>
#include <stdlib.h>

#include <stdio.h>

#define MAX_LINE 4096


class TCPClass{

public:
    int listenfd,connfd;
    
    struct sockaddr_in servaddr;/*本机地址信息*/
    struct sockaddr_in their_addr;/*客户地址信息*/
    char buff[4096];
    
    int64_t n;
    
    bool fengZhuangBao;
    bool fengZhuangJieGouTi;
    bool waiting;
    
    TCPClass();
    
    ~TCPClass();

};


#endif /* TCPClass_hpp */
