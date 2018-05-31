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
   /*
    广播 服务器 其实不需要专门的广播服务器
   
    */
    
   // testUDPGuangBoServer();
    
    
    /*
     多播服务端
     */
    
  //  testUDPDuoBoServer();
    
   
    testNServerUDPServer();
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}
