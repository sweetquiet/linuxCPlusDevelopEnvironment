//
//  main.c
//  Mysql_Redis
//
//  Created by admindyn on 2018/3/16.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include "mysqlclient.h"
#include "redisclient.h"
#include "hiredis.h"
#include <stdbool.h>
#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include "datastruct.h"

char* targetDB = "NS_MOTE_DB";

KVS* kv;

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
       mysqlConnect("192.168.5.224", 3306, "manthink", "MTa@123456","mtaserver");
#if AS
    fetchMysql1("");
#else
     fetchMysql2("");
#endif
    
   
    
    
    
    
    
    
    
    return 0;
}
