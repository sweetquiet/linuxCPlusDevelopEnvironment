//
//  mysqlclient.c
//  Redis_Mysql
//
//  Created by admindyn on 2018/3/13.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <mysql.h>
#include "mysqlclient.h"

MYSQL* mysql;

void closeMysqlConnect()
{
    mysql_close(mysql);
    
}

void mysqlConnect(char* host,int port,char* username,char* pasd,char* dbname)
{
    
    MYSQL* temp = mysql_init(mysql);
    mysql = temp;
    if(!temp) {
        printf("Failed to connect to Mysql!\n");
        
    }else {
        printf("Connected to Mysql successfully!\n");
    }
    
    mysql_real_connect(temp, host, username, pasd, dbname, port, NULL, 0);
    
  
}

void insertMysql(char* query)
{
    
   
    int flag =  mysql_query(mysql, query);
    if(flag) {
        printf("Query failed!\n");
        
    }else {
        printf("[%s] made...\n", query);
    }
  /*
   if (-1 == mysql_real_query(mysql,sql,(uint32_t)strlen(sql))) {
   printf("my_real_query err:%d from %s", mysql_errno(mysql), mysql_error(mysql));
   }*/
   
    
    
}

