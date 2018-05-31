//
//  main.c
//  NServerDuplicate
//
//  Created by admindyn on 2018/5/30.
//  Copyright © 2018年 admindyn. All rights reserved.
//
#include "udptest.h"
#include "testnserver.h"
#include <stdio.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    /*广播客户端 不需要有专门的广播服务器*/
  // testUDPGuangBoClient();
    
   /*多播客户端*/
    
   // testUDPDuoBoClient();
    
    
    
    /*NServer UDP 测试*/
    
    testUDP_NServer_Client();
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}
