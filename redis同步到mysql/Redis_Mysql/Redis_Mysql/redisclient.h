//
//  redisclient.h
//  Redis_Mysql
//
//  Created by admindyn on 2018/3/13.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef redisclient_h
#define redisclient_h

#include "hiredis.h"
#include <stdio.h>

void connectRedis(char* host,int port);

void findTargetDb(char* table);


int handleDBReply(redisReply*reply);

/*#####as#####*/

/*
 先获取 某张hash表下的 所有 设备 key
 
 返回的是 所有key 组成的数组
 
 
 redis 命令: HKEYS as_db
 */

int get_keys_by_hash(char* hashtable,void* val,size_t* elements,size_t len);

int base_array(char** res,size_t*elements,size_t rlen,const char* format,...);

 /*
  再获取 指定hash表下 指定键值key 下 对应的存储的binary 存储的是二进制
  key 下 对应的是一个 结构体

  该结构体 是真正的数据表结构 字段 加 值
  */
int get_binary_by_hash(char *hashtable, char *field, void *val, size_t len);
/*
 在 redis 下 不管hash 表 键值对 存储的是什么
 只要不是 整型  其他的存储的结构体 等 redis 都认为是
 */


int get_valstr_by_hash(char *hashtable, char *field, char *val, size_t len);

int base(char *res, size_t rlen, const char *format, ...);



#endif /* redisclient_h */
