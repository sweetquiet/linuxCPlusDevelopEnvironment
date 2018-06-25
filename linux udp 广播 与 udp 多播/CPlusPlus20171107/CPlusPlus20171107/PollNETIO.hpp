//
//  PollNETIO.hpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/9.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#ifndef PollNETIO_hpp
#define PollNETIO_hpp


#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <poll.h>
#include <stdio.h>

class PollNETIO {

public:
    PollNETIO();
    int serverfd;/*监听套接字*/
    /*创建套接字 进行绑定 和 监听*/
    int bind_and_listen();
    /*多路复用 开始接受数据*/
    void testServer();
    void do_poll(int listenfd);
    
    ~PollNETIO();


};



#endif /* PollNETIO_hpp */
