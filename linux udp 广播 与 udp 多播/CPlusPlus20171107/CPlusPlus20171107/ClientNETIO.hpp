//
//  ClientNETIO.hpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/9.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#ifndef ClientNETIO_hpp
#define ClientNETIO_hpp

#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/select.h>
#include <stdio.h>

class ClientNETIO{

public:
    ClientNETIO();
    ~ClientNETIO();
    

};


#endif /* ClientNETIO_hpp */
