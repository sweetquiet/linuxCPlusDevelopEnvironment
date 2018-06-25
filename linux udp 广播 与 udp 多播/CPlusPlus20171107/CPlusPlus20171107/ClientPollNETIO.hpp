//
//  ClientPollNETIO.hpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/9.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#ifndef ClientPollNETIO_hpp
#define ClientPollNETIO_hpp

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

class ClientPollNETIO{

public:
    ClientPollNETIO();
    ~ClientPollNETIO();

};


#endif /* ClientPollNETIO_hpp */
