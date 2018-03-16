//
//  redisclient.c
//  Redis_Mysql
//
//  Created by admindyn on 2018/3/13.
//  Copyright © 2018年 admindyn. All rights reserved.
//


#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <malloc/malloc.h>
#include "mysqlclient.h"
#include <stdbool.h>
#include "datastruct.h"
#include "hiredis.h"
#include "redisclient.h"

redisContext* conn ;

extern char* targetDB ;
extern KVS* kv;

void connectRedis(char* host,int port)
{
    
    
    
    struct timeval timeout = { 1, 500000 };    /* 超时时限，1.5s */
    
    conn = redisConnectWithTimeout(host, port, timeout);
    if (conn == NULL || conn->err) {
        if (conn) {
            printf("conn redis error: [%s]", conn->errstr);
            redisFree(conn);
        } else {
            printf("can't allocate redis context\n");
        }
        
       
    }
    
   
    
}


int get_keys_by_hash(char* hashtable,void* val,size_t* elements,size_t len)
{
    if (hashtable==NULL || val==NULL || len<=0) {
        printf("param err\n");
        return 0;
    }
     return base_array(val, elements, len, "HKEYS %s", hashtable);
    
}

int base_array(char** res,size_t*elements,size_t rlen,const char* format,...)
{
    /*HKEYS as_db 返回的是数组  处理 返回的所有key*/
    int ret = RET_ERR;
    connectRedis(AS_REDIS_IP, AS_REDIS_PORT);
    if (conn == NULL) {
        printf("redis connected error\n");
         goto JRET;
    }
    
    va_list args;
    
    va_start(args, format);
    
    redisReply* r = redisvCommand(conn, format, args);
    
     va_end(args);
    
     if (r == NULL) {
         printf("redis conn error\n");
         goto DISCONN;
     }
    if (r->type == REDIS_REPLY_ERROR) {
      printf(" error %s\n",r->str);
         goto FREERLY;
     
    }
     ret = RET_OK;
    switch (r->type) {
        case REDIS_REPLY_ARRAY:
            if (res) {
                //(void)memset(res, 0, rlen);
                *elements = r->elements;
                for (int i=0;i<r->elements;i++) {
                    //    printf("%s\n",reply->element[i]->str);
                    strcpy(((char *)res+i*rlen), r->element[i]->str);
                }
                //(void)memcpy(((char **)res)[i], reply->element[i]->str, 16);
            }
            break;
        case REDIS_REPLY_NIL:
            ret = RET_NIL;
            printf("NO reply!!!\n");
            break;
        case REDIS_REPLY_STATUS:
            if (strcasecmp(r->str,"ok") != 0) {
                ret = RET_ERR;
             
                 printf("reply status err, [%s]", r->str);
            }
            break;
    }
    
    
FREERLY:
    freeReplyObject(r);
DISCONN:
    redisFree(conn);
JRET:
    return ret;
    
}


int get_binary_by_hash(char *hashtable, char *field, void *val, size_t len)
{
    return get_valstr_by_hash(hashtable, field, val ,len);
}

int get_valstr_by_hash(char *hashtable, char *field, char *val, size_t len)
{
    if (hashtable==NULL || field==NULL || val==NULL || len<=0) {
        printf("param err, hash[%s]/field[%s]/len[%d]", hashtable?hashtable:"NULL", field?field:"NULL", (int)len);
        return RET_ERR;
    }
    return base(val, len, "HGET %s %s", hashtable, field);
}


int base(char *res, size_t rlen, const char *format, ...)
{
  
  
    int ret = RET_ERR;
    
    /* 连接redis服务器，默认阻塞式(发送命令并等待结果回传) */
    connectRedis(AS_REDIS_IP, AS_REDIS_PORT);
    /*
     这里貌似 每次向 redis 发送命令 必须重新建立连接 很容易超时 连接断开
     造成 错误
     */
    if (conn == NULL) {
        goto JRET;
    }
    
    /* 存储数据 */
    
    va_list args;
    
    va_start(args, format);
    
    redisReply* r = redisvCommand(conn, format, args);
    
    va_end(args);
    if (r == NULL) {
        printf("redis connect error\n");
        goto DISCONN;
    } else if (r->type == REDIS_REPLY_ERROR) {
        printf("%s", r->str);
        goto FREERLY;
    }
    
    /* 处理返回数据 */
    ret = RET_OK;
    switch (r->type) {
        case REDIS_REPLY_STRING:
            if (res) {
                (void)memset(res, 0, rlen);
                /*
                 这里将redis 取出的数据 memcpy到我们的可操作指针中
                 */
                printf("redis 获取数据%s\n",r->str);
                (void)memcpy(res, r->str, (r->len > rlen?rlen:r->len));
            }
            break;
        case REDIS_REPLY_INTEGER:
            if (res) {
                *(long long *)res = r->integer;
            }
            break;
        case REDIS_REPLY_NIL:
            if (res) {
                snprintf(res, rlen, "%s", "\0");
            }
            ret = RET_NIL;
            printf("NO reply!!! \n");
            break;
        case REDIS_REPLY_STATUS:
            if (strcasecmp(r->str,"ok") != 0) {
                ret = RET_ERR;
                printf("reply status err, [%s]", r->str);
            }
            break;
    }
    
FREERLY:
    /*
     释放返回的对象
     */
    freeReplyObject(r);
DISCONN:
    /*
     释放本次连接
     */
    redisFree(conn);
JRET:
    return ret;
}


int store_binary_by_hash(char *hash, char *field, void *val, size_t len)
{
    if (hash==NULL || field==NULL || val==NULL || len<=0) {
       printf("param err, hash[%s]/field[%s]/len[%d]", hash?hash:"NULL", field?field:"NULL", (int)len);
        return RET_ERR;
    }
    return base(NULL, -1, "HSET %s %s %b", hash, field, val, len);
}
void logDeviceData(AS_MOTE_INFO* de)
{
    
    AS_MOTE_INFO device = *de;
    
   
    char* session_id= malloc(24*sizeof(char));
    if (session_id==NULL) {
        printf("分配内存出错\n");
    }
    memset(session_id, 0, 24*sizeof(char));
    char valsession_id[24];
    int sumvalsession_id = 1;
    for (int k =sumvalsession_id-1; k>=0; k--) {
        snprintf(valsession_id, 24,"%x",device.moteq.datadn[0].session_id);
        strcat(session_id,valsession_id); printf("%x-",device.moteq.datadn[0].session_id);
    }
    printf("\n");
    printf("session_id:%s\n",session_id);
    printf("session_id:%x\n",device.moteq.datadn[0].session_id);
    printf("\n");
    
    
    char* token= malloc(24*sizeof(char));
    if (token==NULL) {
        printf("分配内存出错\n");
    }
    memset(token, 0, 24*sizeof(char));
    char valtoken[24];
    int sumvaltoken = 1;
    for (int k =sumvaltoken-1; k>=0; k--) {
        snprintf(valtoken, 24,"%x",device.moteq.datadn[0].token);
        strcat(token,valtoken); printf("%x-",device.moteq.datadn[0].token);
    }
    printf("\n");
    printf("token:%s\n",token);
    printf("token:%x\n",device.moteq.datadn[0].token);
    printf("\n");
    
    char* seqno= malloc(24*sizeof(char));
    if (seqno==NULL) {
        printf("分配内存出错\n");
    }
    memset(seqno, 0, 24*sizeof(char));
    char valseqno[24];
    int sumvalseqno = 1;
    for (int k =sumvalseqno-1; k>=0; k--) {
        snprintf(valseqno, 24,"%x",device.moteq.datadn[0].seqno);
        strcat(seqno,valseqno); printf("%x-",device.moteq.datadn[0].seqno);
    }
    printf("\n");
    printf("seqno:%s\n",seqno);
    printf("seqno:%x\n",device.moteq.datadn[0].seqno);
    printf("\n");
    
    
    
    char* port= malloc(24*sizeof(char));
    if (port==NULL) {
        printf("分配内存出错\n");
    }
    memset(port, 0, 24*sizeof(char));
    char valport[24];
    int sumvalport = 1;
    for (int k =sumvalport-1; k>=0; k--) {
        snprintf(valport, 24,"%x",device.moteq.datadn[0].port);
        strcat(port,valport); printf("%x-",device.moteq.datadn[0].port);
    }
    printf("\n");
    printf("port:%s\n",port);
    
    printf("port:%x\n",device.moteq.datadn[0].port);
    printf("\n");
    
    
    
    
    char* size= malloc(24*sizeof(char));
    if (size==NULL) {
        printf("分配内存出错\n");
    }
    memset(size, 0, 24*sizeof(char));
    char valsize[24];
    int sumvalsize = 1;
    for (int k =sumvalsize-1; k>=0; k--) {
        snprintf(valsize, 24,"%x",device.moteq.datadn[0].size);
        strcat(size,valsize); printf("%x-",device.moteq.datadn[0].size);
    }
    printf("\n");
    printf("size:%s\n",size);
    printf("size:%x\n",device.moteq.datadn[0].size);
    printf("\n");
    
  
   
    char* payload= malloc(260*sizeof(char));
    if (payload==NULL) {
        printf("分配内存出错\n");
    }
    memset(payload, 0, 260*sizeof(char));
    char valpayload[260];
    int sumvalpayload = sizeof(device.moteq.datadn[0].size);
    for (int k =sumvalpayload-1; k>=0; k--) {
        snprintf(valpayload, 24,"%x",device.moteq.datadn[0].payload[k]);
        strcat(port,valport); printf("%x-",device.moteq.datadn[0].payload[k]);
    }
    printf("\n");
    printf("payload:%s\n",payload);
    printf("payload:%p\n",device.moteq.datadn[0].payload);
    printf("\n");
   
   
    
    
}


int findKeysInTargetDB(char* table)
{
    int strlen = 64;
    AS_MOTE_INFO device;
    char str[81920][strlen];
    
    int mote_num;
    
    if (RET_ERR == get_keys_by_hash(table, (char**)str, (size_t*)&mote_num, strlen)) {
        printf("get mote keys by database failed!\n");
        return RET_ERR;
    }
    int ret;
    int i;
    
    for (i=0;i<mote_num;i++) {
        printf("device:%s i::%d\n",str[i],i);
        
        if (i==5000) {
            printf("5000睡眠20秒\n");
#define sleeptest
            /*
             使用sleep 要导入 函数库
             #include <unistd.h>
             */
            sleep(20);
        }
        if (i==10000) {
            printf("10000睡眠20秒\n");
            sleep(20);
        }
        if (i==15000) {
            printf("15000睡眠20秒\n");
            sleep(20);
        }
        if (i==20000) {
            printf("20000睡眠20秒\n");
            sleep(20);
        }
        
        ret = get_binary_by_hash(table, str[i], &device, sizeof(device));
        
        if (RET_ERR == ret) {
            printf("get mote  %s dn by database failed!", str[i]);
            continue;
            
        } else if (RET_NIL == ret) {
             printf("mote %s has no dn data", str[i]);
          
            continue;
        } else {
           
            
            

            
        }
    }
    
    return RET_OK;
    
    
}

int findKeysInTargetDB2(char* table)
{
    int strlen = 64;
    NS_MOTE_INFO device;
    char str[81920][strlen];
    
    int mote_num;
    
    if (RET_ERR == get_keys_by_hash(table, (char**)str, (size_t*)&mote_num, strlen)) {
        printf("get mote keys by database failed!\n");
        return RET_ERR;
    }
    int ret;
    int i;
    
    for (i=0;i<mote_num;i++) {
        printf("device:%s i::%d\n",str[i],i);
        
        if (i==5000) {
            printf("5000睡眠20秒\n");
            sleep(20);
        }
        if (i==10000) {
            printf("10000睡眠20秒\n");
            sleep(20);
        }
        if (i==15000) {
            printf("15000睡眠20秒\n");
            sleep(20);
        }
        if (i==20000) {
            printf("20000睡眠20秒\n");
            sleep(20);
        }
        
        ret = get_binary_by_hash(table, str[i], &device, sizeof(device));
        
        if (RET_ERR == ret) {
            printf("get mote  %s dn by database failed!", str[i]);
            continue;
            
        } else if (RET_NIL == ret) {
            printf("mote %s has no dn data", str[i]);
            
            continue;
        } else {
            
            
            
            
            
        }
    }
    
    return RET_OK;
    
    
}


void updateTargetDb(char* table)
{
   connectRedis(AS_REDIS_IP, AS_REDIS_PORT);
    
    targetDB = table;
    

   
    
    
#if AS
    
    AS_MOTE_INFO device;
   
    updateValInHashTable(AS_DEVICE_DB,&device);
#else
      NS_MOTE_INFO device; updateValInHashTable2(AS_DEVICE_DB,&device);
#endif
        
    
    
    
}

void updateValInHashTable(char* hashtab,AS_MOTE_INFO* device)
{
    
    
}

void updateValInHashTable2(char* hashtab,NS_MOTE_INFO* device)
{
    
}

void checkRedisState(int state)
{
    
    switch (state) {
        case REDIS_OK:
        {
            
            
        }
            break;
            
        case REDIS_ERR_IO:
        {
            printf("IO ERR!");
        }
            break;
        case REDIS_ERR_EOF:
        {
            printf("End of file !");
        }
            break;
            
        case REDIS_ERR_PROTOCOL:
        {
            printf("Protocol error !");
        }
            break;
        case REDIS_ERR_OOM:
        {
            printf("Out of memory!");
        }
            break;
            
        default:
            break;
    }
    
    
}

int handleDBReply(redisReply*reply)
{
    int ret = RET_ERR;
    switch (reply->type) {
       
        case REDIS_REPLY_ARRAY:
        {
            size_t count =  reply->elements;
            /*for 循环开始*/
            for (int i =0; i<count; i++) {
                
                redisReply* temp = reply->element[i];
                if (temp == NULL) {
                    
                    printf("element is NULL\n");
                    
                }else
                {
                    
                    switch (temp->type) {
                      
                        case REDIS_REPLY_STRING:
                        {
                            
                            
                            
                            printf("寻找目标 hash表\n");
                            
                            printf("表名: %s\n",reply->element[i]->str);
                            
                            if(strcasecmp(reply->element[i]->str,targetDB) == 0) {
                                
                                printf("%s == %s\n",reply->element[i]->str,targetDB);
                                
                                return  RET_OK;
                                
                                
                            }
                            
                            
                            
                            
                            
                        }
                            break;
                            
                        default:
                            break;
                    }
                    
                }
                
                
            }
            
             return  RET_ERR;
            /*for 循环结束*/
            
        }
            break;
            
        default:
            break;
    }
    
    return  ret;
}



KVS* createKVNode(char* key,char* val)
{
    KVS* node = NULL;
    node = malloc(sizeof(KVS));
    
    if (node == NULL) {
        printf("malloc fail\n");
    }
    
    memset(node, 0, sizeof(KVS));
    
    node->key = key;
    node->val = val;
    
    return  node;
}

void appendKVLINK(char* key,char* val)
{
    if (kv == NULL) {
        kv = malloc(sizeof(KVS));
        memset(kv,0,sizeof(KVS)); //3、清一下
        kv->next=NULL;
        return;
    }
    
    if (kv->next==NULL) {
        kv->next = createKVNode(key, val);
        return;
        
    }else
    {
        
        KVS* temp = kv->next;
        temp = temp->next;
        
        temp->next =createKVNode(key, val);
        
    }
    
    
}

void printKVList()
{
    int count = 0;
    do {
        
        if (kv==NULL) {
            printf("链表没有头指针\n");
        }else
        {
            printf("key:%s val:%s",kv->key,kv->val);
            
            
        }
        count = count + 1;
    } while (kv->next!=NULL);
    
    printf("总的条数:%d\n",count);
    
}

