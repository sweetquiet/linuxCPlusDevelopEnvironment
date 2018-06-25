//
//  main.c
//  Redis_Mysql
//
//  Created by admindyn on 2018/3/13.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <string.h>
#include "mysqlclient.h"
#include "redisclient.h"
#include "read.h"
#include "hiredis.h"
#include <stdbool.h>
#include <mysql.h>
#include <stdio.h>
#include "datastruct.h"


char* targetDB = "as_info_db";
KVS* kv;

typedef struct st {
    int a;
    int b;
    char c;
    int d;
}st;





int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
  
     mysqlConnect("", 3306, "", "","");
    
    
    
    findTargetDb(AS_DEVICE_DB);
    
    
    

    
  
    
 
    
  
    
   
 

    
    return 0;
}

