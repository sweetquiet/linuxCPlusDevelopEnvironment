//
//  testnserver.c
//  NServerDuplicate
//
//  Created by admindyn on 2018/5/30.
//  Copyright © 2018年 admindyn. All rights reserved.
//
#include "Queue.h"
#include "SocketConnLink.h"
#include "testnserver.h"

void readCallBackPKT(PKT* pkt)
{
    
}

void writeCallBackPKT(PKT* pkt)
{
    
}
void testNServerUDPServer(void)
{
    readyKeyLoopStart();
    
    init_client_conn();
    
InitUDPSocketServerQueue("127.0.0.1", 8083, readCallBackPKT, writeCallBackPKT);
    
    start_event_loop();
}



void testNServerUDPClient(void)
{
    
    
}

















