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



void redisTest(void);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
  
    mysqlConnect("127.0.0.1", 3306, "root", "asd1453NMDmysql","JfinalDB");
    
    
    
    findTargetDb(AS_DEVICE_DB);
    
    
    

    
  
    
 
    
  
    
   
 

    
    return 0;
}

void redisTest(void)
{
    
    struct st t;
    t.a = 1;
    t.b = 2;
    t.c = 'a';
    t.d = 4;
    
    
    redisContext* conn = redisConnect("127.0.0.1", 6379);
    
    if (conn == NULL || conn->err) {
        if (conn) {
            printf("Error %s",conn->errstr);
        }else
        {
            
            printf("can not allocate");
        }
    }
    
    
//   redisReply* reply;
    
    
    const char *v[4];
    size_t vlen[4];
    v[0] = "zadd";
    
    /*
     必须引入 #include <string.h> 否则 有很多警告 虽然不影响程序运行
     Implicitly declaring library function 'strlen' with type 'unsigned long (const char *)'
     */
    vlen[0] = strlen("zadd");
    
    v[1] = "d";
    vlen[1] = strlen("d");
    
    
    v[2] = "1921683121";
    vlen[2] = strlen("1921683121");
    
    v[3] = (const char *)&t;
    vlen[3] = sizeof(struct st);
    int hh = sizeof(v);
    int bbb= sizeof(v[0]);
    redisReply *r = (redisReply *)redisCommandArgv(conn, hh/bbb , v, vlen);
    if (!r) {
        printf("empty reply\n");
        exit(1);
    }
    
    printf("reply: %s\n", r->str);
    
    freeReplyObject(r);
    
    
    r = (redisReply *)redisCommand(conn, "zrange d 0 -1");
    if (!r) {
        printf("empty reply\n");
        exit(1);
    }
    
    printf("reply length: %lu\n", r->elements);
    
    struct st *p = (struct st *)malloc(sizeof(struct st));
    if (!p) {
        printf("malloc fail\n");
        exit(-1);
    }
    
    for (size_t i = 0; i < r->elements; i++) {
        printf("element length: %ld\n", r->element[i]->len);
        if (r->element[i]->len != sizeof(struct st)) {
            printf("reply len error\n");
            exit(-1);
        }
        /*
         必须引入 #include <string.h> 否则 有很多警告 虽然不影响程序运行
         Implicitly declaring library function 'strlen' with type 'unsigned long (const char *)'
         */
        memcpy(p, r->element[i]->str,r->element[i]->len);
        printf("%d",p->a);
        
    }
    
}
