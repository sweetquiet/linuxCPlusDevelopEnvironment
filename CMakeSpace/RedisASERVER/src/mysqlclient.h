//
//  mysqlclient.h
//  Redis_Mysql
//
//  Created by admindyn on 2018/3/13.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef mysqlclient_h
#define mysqlclient_h

#include <stdio.h>


void mysqlConnect(char* host,int port,char* username,char* pasd,char* dbname);

void insertMysql(char* query);

void closeMysqlConnect(void);

void fetchMysql1(char* query);

void fetchMysql2(char* query);





#endif /* mysqlclient_h */
