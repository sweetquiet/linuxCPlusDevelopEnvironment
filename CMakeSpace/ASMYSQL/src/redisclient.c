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
#include <malloc.h>
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

void checkDevice(AS_MOTE_INFO* de)
{
    
    AS_MOTE_INFO device = *de;
    size_t size = sizeof(device.appskey);

#define malloctest
    /*
     使用malloc 和 free 必须引入 头文件
     
    
     
     #include <stdlib.h>
    
     */
    char* classmode = malloc(size*4);
     /*%lx -> %p*/
    if (classmode==NULL) {
        printf("分配内存出错\n");
    }
    memset(classmode, 0, size*4);
    snprintf(classmode, size*4, "%x",device.classmode);
    

    printf("classmode:%s\n",classmode);
    printf("%x",device.classmode);
    printf("\n");
    
    char* standard = malloc(size*4);
    if (standard==NULL) {
        printf("分配内存出错\n");
    }
    memset(standard, 0, size*4);
    strcpy(standard, device.standard);
    printf("standard:%s\n",standard);
    printf("%s",device.standard);
    printf("\n");
    
    
    
    char* datr = malloc(size*4);
    if (datr==NULL) {
        printf("分配内存出错\n");
    }
    memset(datr, 0, size*4);
    strcpy(datr, device.datr);
    printf("datr:%s\n",datr);
    printf("%s",device.datr);
    printf("\n");
    
  
    
    
    char* codr = malloc(size*4);
    if (codr==NULL) {
        printf("分配内存出错\n");
    }
    memset(codr, 0, size*4);
    strcpy(codr, device.codr);
    printf("codr:%s\n",codr);
    printf("%s",device.codr);
    printf("\n");
    
    char* appeui = malloc(size*4);
    if (appeui==NULL) {
        printf("分配内存出错\n");
    }
    memset(appeui, 0, size*4);
    char valappeui[4];
    int sumvalappeui = sizeof(device.appeui);
    for (int k =sumvalappeui-1; k>=0; k--)
    {
         snprintf(valappeui, 3,"%.2x",device.appeui[k]);
        strcat(appeui,valappeui); printf("%x-",device.appeui[k]);
    }
    printf("\n");
    printf("appeui:%s\n",appeui);
     /*%lx -> %p*/
    printf("appeui:%p\n",device.appeui);
   //  printf("appeui:%lx\n",device.appeui);
    printf("\n");
    
    
    
    
    printf("deveui:\n");
    
   // uint64_t deval2;
    //140734794532484
    uint64_t* deval = (uint64_t*)&device.deveui[0];
     /*%ld -> %p*/
    printf("这个输出的是十六进制地址的整形十进制值:%p",deval);
    printf("\n");
     /*%ld -> %llu*/
    printf("这个输出的是真正指针引用内容的十六进制数的十六进制输出十进制的值%lu",*deval);
    printf("\n");
    char *deveui = malloc(24*sizeof(char));
    if (deveui==NULL) {
        printf("分配内存出错\n");
    }
    
    memset(deveui, 0, 24*sizeof(char));

//    char * deveui2 = malloc(24*sizeof(char));
//    if (deveui2==NULL) {
//        printf("分配内存出错\n");
//    }
//        memset(deveui2, 0, 24*sizeof(char));
    

//    char* temp = deveui2;
//    char tear [24];
//    char* temp2 = tear;
    /*
     snprintf的返回值是欲写入的字符串长度，而不是实际写入的字符串度
     */
    int sum = sizeof(device.deveui);
    char val[4];
    
//    int num = 0;
    printf("正序输出十六进制:\n");
    for (int k =0; k<sum; k++) {
    
        printf("%.2x-",device.deveui[k]);
        /*
         9f26c11224010141
         */
    }
    printf("\n");
    printf("逆序输出十六进制:\n");
#define  deveuitest
    for (int k =sum-1; k>=0; k--) {
   
        /*
         
         
         使用 对字符串操作的函数 要导入
         #include <string.h>
         
         */
        
        snprintf(val, 3,"%.2x",device.deveui[k]);
        
        //size_t vallen =strlen(val);
    
        /*
         第二个参数为 size 如果源字符串格式化字符数大于或者等于这个size
         只将其中的(size-1)个字符复制到str中，并给其后添加一个字符串结束符('\0')
         
         如果小于这个size 则将字符串全部复制到其中 并给其后添加一个字符串结束符('\0')
         */
//    snprintf(temp,vallen+1,"%s",val);
//    snprintf(temp2,vallen+1,"%s",val);
        /*
         
         strcpy
         memset
         strcat
         等这些函数 都依赖头文件
         #include <string.h>
         Implicitly declaring library function 'strcat' with type 'char *(char *, const char *)'
         不引用的话 会警告 不影响程序运行
         */
    strcat(deveui, val);

//        num  =num + (int)strlen(val);
//        temp2 = temp2 + num*sizeof(char);
//        temp = temp + num*sizeof(char);
        printf("%.2x-",device.deveui[k]);
        
    }
    printf("\n");
//    sscanf(deveui, "%llu", &deval2);
//    printf("uint64:%llu",deval2);
    
    printf("\n");
//    char* endStr;
//    long l =strtol(deveui, &endStr, 16);
//    printf("l::%ld",l);
    printf("\n");
    printf("deveui:%s\n",deveui);
    printf("\n");
     /*%lx -> %p*/
    printf("deveui:%p\n",device.deveui);
    printf("\n");
    
    
    
    char* devaddr= malloc(24*sizeof(char));
    if (devaddr==NULL) {
        printf("分配内存出错\n");
    }
    memset(devaddr, 0, 24*sizeof(char));
    char valdevaddr[4];
    int sumvaldevaddr = sizeof(device.devaddr);
    for (int k =sumvaldevaddr-1; k>=0; k--)
    {
        snprintf(valdevaddr, 3,"%.2x",device.devaddr[k]);
        strcat(devaddr,valdevaddr); printf("%x-",device.devaddr[k]);
    }
    printf("devaddr:%s\n",devaddr);
    printf("devaddr:%p\n",device.devaddr);
    printf("\n");
    
 
    
  
    
    char* appkey= malloc(36*sizeof(char));
    if (appkey==NULL) {
        printf("分配内存出错\n");
    }
    memset(appkey, 0, 36*sizeof(char));
    char valappkey[4];
    int sumvalvalappkey = sizeof(device.appkey);
    for (int k =sumvalvalappkey-1; k>=0; k--)
     {
        snprintf(valappkey, 3,"%.2x",device.appkey[k]);
        strcat(appkey,valappkey); printf("%x-",device.appkey[k]);
    }
    printf("\n");
    printf("appkey:%s\n",appkey);
    printf("appkey:%p\n",device.appkey);
    printf("\n");
    
    
   
    
   
    
    char* appskey= malloc(36*sizeof(char));
    if (appskey==NULL) {
        printf("分配内存出错\n");
    }
    memset(appskey, 0, 36*sizeof(char));
    char valappskey[4];
    int sumvalappskey = sizeof(device.appskey);
    for (int k =sumvalappskey-1; k>=0; k--) {
        snprintf(valappskey, 3,"%.2x",device.appskey[k]);
        strcat(appskey,valappskey); printf("%x-",device.appskey[k]);
    }
  
    printf("\n");
    printf("appskey:%s\n",appskey);
    printf("appskey:%p\n",device.appskey);
    printf("\n");
    
    
   
    
    
   
    char* nwkskey= malloc(36*sizeof(char));
    if (nwkskey==NULL) {
        printf("分配内存出错\n");
    }
    memset(nwkskey, 0, 36*sizeof(char));
    char valnwkskey[4];
    int sumvalnwkskey = sizeof(device.nwkskey);
    for (int k =sumvalnwkskey-1; k>=0; k--) {
        snprintf(valnwkskey, 3,"%.2x",device.nwkskey[k]);
        strcat(nwkskey,valnwkskey); printf("%x-",device.nwkskey[k]);
    }
    
   
    printf("\n");
    printf("nwkskey:%s\n",nwkskey);
    printf("nwkskey:%p\n",device.nwkskey);
    printf("\n");
    

    
   
    char* devnonce= malloc(24*sizeof(char));
    if (devnonce==NULL) {
        printf("分配内存出错\n");
    }
    memset(devnonce, 0, 24*sizeof(char));
    char valdevnonce[4];
    int sumvaldevnonce = sizeof(device.devnonce);
    for (int k =sumvaldevnonce-1; k>=0; k--) {
        snprintf(valdevnonce, 3,"%.2x",device.devnonce[k]);
        strcat(devnonce,valdevnonce); printf("%x-",device.devnonce[k]);
    }
    
   
    printf("\n");
    printf("devnonce:%s\n",devnonce);
    printf("devnonce:%p\n",device.devnonce);
    printf("\n");
    
    
    
    
    char* place_holder2= malloc(24*sizeof(char));
    if (place_holder2==NULL) {
        printf("分配内存出错\n");
    }
    memset(place_holder2, 0, 24*sizeof(char));
    char valplace_holder2[4];
    int sumvalplace_holder2 = sizeof(device.__place_holder2);
    for (int k =sumvalplace_holder2-1; k>=0; k--) {
        snprintf(valplace_holder2, 3,"%.2x",device.__place_holder2[k]);
    strcat(place_holder2,valplace_holder2); printf("%x-",device.__place_holder2[k]);
    }
    
printf("place_holder2:%s\n",place_holder2);
printf("place_holder2:%p\n",device.__place_holder2);
    printf("\n");
    
    
    
  
    

    char* place_holder1= malloc(24*sizeof(char));
    if (place_holder1==NULL) {
        printf("分配内存出错\n");
    }
    memset(place_holder1, 0, 24*sizeof(char));
    char valplace_holder1[24];
    int sumvalplace_holder1 = 1;
    for (int k =sumvalplace_holder1-1; k>=0; k--) {
        snprintf(valplace_holder1, 24,"%x",device.__place_holder1);
    strcat(place_holder1,valplace_holder1); printf("%x-",device.__place_holder1);
    }
    
    printf("\n");
    printf("place_holder1:%s\n",place_holder1);
 printf("place_holder1:%x\n",device.__place_holder1);
    printf("\n");
    
    
  
    
   
    char* place_holder= malloc(24*sizeof(char));
    if (place_holder==NULL) {
        printf("分配内存出错\n");
    }
    memset(place_holder, 0, 24*sizeof(char));
    char valplace_holder[24];
    int sumvalplace_holder = 1;
    for (int k =sumvalplace_holder-1; k>=0; k--) {
        snprintf(valplace_holder, 24,"%x",device.__place_holder);
        strcat(place_holder,valplace_holder); printf("%x-",device.__place_holder);
    }
    printf("\n");
    printf("place_holder:%s\n",place_holder);
    printf("place_holder:%x\n",device.__place_holder);
    printf("\n");
    
   
    
   
    
    char* appnonce= malloc(24*sizeof(char));
    if (appnonce==NULL) {
        printf("分配内存出错\n");
    }
    memset(appnonce, 0, 24*sizeof(char));
    char valappnonce[4];
    int sumvalappnonce = sizeof(device.appnonce);
    for (int k =sumvalappnonce-1; k>=0; k--) {
        snprintf(valappnonce, 3,"%.2x",device.appnonce[k]);
        strcat(appnonce,valappnonce); printf("%x-",device.appnonce[k]);
    }
    
 printf("\n");
    printf("appnonce:%s\n",appnonce);
    /*%lx -> %p*/
    printf("appnonce %p\n",device.appnonce);
    printf("\n");
    
   
    
    
    
    
    char* netid= malloc(24*sizeof(char));
    if (netid==NULL) {
        printf("分配内存出错\n");
    }
    memset(netid, 0, 24*sizeof(char));
    char valnetid[4];
    int sumvalnetid = sizeof(device.netid);
    for (int k =sumvalnetid-1; k>=0; k--) {
        snprintf(valnetid, 3,"%.2x",device.netid[k]);
        strcat(netid,valnetid); printf("%x-",device.netid[k]);
    }
printf("\n");
    printf("netid:%s\n",netid);
    printf("netid:%p\n",device.netid);
    printf("\n");
    

    
   
    
    char* rx1droffset= malloc(24*sizeof(char));
    if (rx1droffset==NULL) {
        printf("分配内存出错\n");
    }
    memset(rx1droffset, 0, 24*sizeof(char));
    char valrx1droffset[24];
    int sumvalrx1droffset = 1;
    for (int k =sumvalrx1droffset-1; k>=0; k--) {
    snprintf(valrx1droffset, 24,"%x",device.rx1droffset);
    strcat(rx1droffset,valrx1droffset); printf("%x-",device.rx1droffset);
    }
    printf("rx1droffset:%s\n",rx1droffset);
    printf("rx1droffset:%x\n",device.rx1droffset);
    printf("\n");
    
    
   
    
    
   
    
    char* rx2dr= malloc(24*sizeof(char));
    if (rx2dr==NULL) {
        printf("分配内存出错\n");
    }
    memset(rx2dr, 0, 24*sizeof(char));
    char valrx2dr[24];
    int sumvalrx2dr = 1;
    for (int k =sumvalrx2dr-1; k>=0; k--) {
        snprintf(valrx2dr, 24,"%x",device.rx2dr);
        strcat(rx2dr,valrx2dr); printf("%x-",device.rx2dr);
    }
    printf("\n");
    printf("rx2dr:%s\n",rx2dr);
    printf("rx2dr:%x\n",device.rx2dr);
    printf("\n");
    
    
   
    
    
    
    char* rxdelay= malloc(24*sizeof(char));
    if (rxdelay==NULL) {
        printf("分配内存出错\n");
    }
    memset(rxdelay, 0, 24*sizeof(char));
    char valrxdelay[24];
    int sumvalrxdelay = 1;
    for (int k =sumvalrxdelay-1; k>=0; k--) {
        snprintf(valrxdelay, 24,"%x",device.rxdelay);
        strcat(rxdelay,valrxdelay); printf("%x-",device.rxdelay);
    }
    printf("\n");
    printf("rxdelay:%s\n",rxdelay);
    printf("rxdelay:%x\n",device.rxdelay);
    printf("\n");
    
 
    
    
    char* rx2_freq= malloc(24*sizeof(char));
    if (rx2_freq==NULL) {
        printf("分配内存出错\n");
    }
    memset(rx2_freq, 0, 24*sizeof(char));
    char valrx2_freq[24];
    int sumvalrx2_freq = 1;
    for (int k =sumvalrx2_freq-1; k>=0; k--) {
        snprintf(valrx2_freq, 24,"%x",device.rx2_freq);
        strcat(rx2_freq,valrx2_freq); printf("%x-",device.rx2_freq);
    }
    printf("\n");
    printf("rx2_freq:%s\n",rx2_freq);
    printf("rx2_freq:%x\n",device.rx2_freq);
    printf("\n");
    
    
   
    char* down_seqnum= malloc(24*sizeof(char));
    if (down_seqnum==NULL) {
        printf("分配内存出错\n");
    }
    memset(down_seqnum, 0, 24*sizeof(char));
    char valdown_seqnum[24];
    int sumvaldown_seqnum = 1;
    for (int k =sumvaldown_seqnum-1; k>=0; k--) {
        snprintf(valdown_seqnum, 24,"%x",device.down_seqnum);
        strcat(down_seqnum,valdown_seqnum); printf("%x-",device.down_seqnum);
    }
    printf("\n");
    printf("down_seqnum:%s\n",down_seqnum);
    printf("down_seqnum:%x\n",device.down_seqnum);
    printf("\n");
    

    
    
   
    char* up_seqnum= malloc(24*sizeof(char));
    if (up_seqnum==NULL) {
        printf("分配内存出错\n");
    }
    memset(up_seqnum, 0, 24*sizeof(char));
    char valup_seqnum[24];
    int sumvalup_seqnum = 1;
    for (int k =sumvalup_seqnum-1; k>=0; k--) {
        snprintf(valup_seqnum, 24,"%x",device.up_seqnum);
        strcat(up_seqnum,valup_seqnum); printf("%x-",device.up_seqnum);
    }
    printf("\n");
    printf("up_seqnum:%s\n",up_seqnum);
    printf("up_seqnum:%x\n",device.up_seqnum);
    printf("\n");
    
    
    

    
    char* systime = malloc(36*sizeof(char));
    if (systime==NULL) {
        printf("分配内存出错\n");
    }
    memset(systime, 0, 36*sizeof(char));
    strcpy(systime, device.systime);
    printf("\n");
    printf("systime:%s\n",systime);
    printf("%s",device.systime);
    printf("\n");
    
    //
    
  
   
    
    
    char sql[8192];
    
   #define sql1
    
    snprintf(sql, sizeof(sql),"insert into AS_MOTE_INFO (deveui,classmode,place_holder,place_holder2,appeui,appkey,appskey,nwkskey,devnonce,netid,place_holder1,rx1droffset,rx2dr,rxdelay,rx2_freq,down_seqnum,up_seqnum,systime,datr,codr,standard,devaddr,appnonce) values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')",
             deveui,classmode,place_holder,place_holder2,appeui,appkey,appskey,nwkskey,devnonce,netid,place_holder1,rx1droffset,rx2dr,rxdelay,rx2_freq,down_seqnum,up_seqnum,systime,datr,codr,standard,devaddr,appnonce);
    
    insertMysql(sql);
    
   
    
    
//    if (deveui2!=NULL) {
//        free(deveui2);
//    }
    if (classmode!=NULL) {
        free(classmode);
    }
    if (standard!=NULL) {
        free(standard);
    }
    if (codr!=NULL) {
        free(codr);
    }
    if (appeui!=NULL) {
        free(appeui);
    }
    if (deveui!=NULL) {
        free(deveui);
    }
    if (devaddr!=NULL) {
        free(devaddr);
    }
    if (appkey!=NULL) {
        free(appkey);
    }
    if (appskey!=NULL) {
        free(appskey);
    }
    if (nwkskey!=NULL) {
        free(nwkskey);
    }
    if (devnonce!=NULL) {
        free(devnonce);
    }
    if (place_holder2!=NULL) {
        free(place_holder2);
    }
    
    
    if (place_holder!=NULL) {
        free(place_holder);
    }
    
    if (place_holder1!=NULL) {
        free(place_holder1);
    }
    if (appnonce!=NULL) {
        free(appnonce);
    }
    if (netid!=NULL) {
        free(netid);
    }
    if (rx1droffset!=NULL) {
        free(rx1droffset);
    }
    if (rx2dr!=NULL) {
        free(rx2dr);
    }
    if (rxdelay!=NULL) {
        free(rxdelay);
    }
    
    if (rx2_freq!=NULL) {
        free(rx2_freq);
    }
    if (down_seqnum!=NULL) {
        free(down_seqnum);
    }
    if (up_seqnum!=NULL) {
        free(up_seqnum);
    }
    if (systime!=NULL) {
        free(systime);
    }
    
    
    
    
    
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

void checkDevice2(NS_MOTE_INFO* de)
{
    
    NS_MOTE_INFO device = *de;
    size_t size = sizeof(device.nwkskey);
    
    
    char* classmode = malloc(size*4);
    /*%lx -> %p*/
    if (classmode==NULL) {
        printf("分配内存出错\n");
    }
    memset(classmode, 0, size*4);
    snprintf(classmode, size*4, "%x",device.classmode);
    
    
    printf("classmode:%s\n",classmode);
    printf("%x",device.classmode);
    printf("\n");
    
    char* standard = malloc(size*4);
    if (standard==NULL) {
        printf("分配内存出错\n");
    }
    memset(standard, 0, size*4);
    strcpy(standard, device.standard);
    printf("standard:%s\n",standard);
    printf("%s",device.standard);
    printf("\n");
    
    
    
  
    
    
    
    
   
    
    char* appeui = malloc(size*4);
    if (appeui==NULL) {
        printf("分配内存出错\n");
    }
    memset(appeui, 0, size*4);
    char valappeui[4];
    int sumvalappeui = sizeof(device.appeui);
    for (int k =sumvalappeui-1; k>=0; k--)
    {
        snprintf(valappeui, 3,"%.2x",device.appeui[k]);
        strcat(appeui,valappeui); printf("%x-",device.appeui[k]);
    }
    printf("\n");
    printf("appeui:%s\n",appeui);
    /*%lx -> %p*/
    printf("appeui:%p\n",device.appeui);
   // printf("appeui:%lx\n",device.appeui);
    printf("\n");
    
    
    
    
    printf("deveui:\n");
    
   // uint64_t deval2;
    //140734794532484
    uint64_t* deval = (uint64_t*)&device.deveui[0];
    /*%ld -> %p*/
    printf("这个输出的是十六进制地址的整形十进制值:%p",deval);
    printf("\n");
    /*%ld -> %llu*/
    printf("这个输出的是真正指针引用内容的十六进制数的十六进制输出十进制的值%lu",*deval);
    printf("\n");
    char *deveui = malloc(24*sizeof(char));
    if (deveui==NULL) {
        printf("分配内存出错\n");
    }
    
    memset(deveui, 0, 24*sizeof(char));
    
    //    char * deveui2 = malloc(24*sizeof(char));
    //    if (deveui2==NULL) {
    //        printf("分配内存出错\n");
    //    }
    //        memset(deveui2, 0, 24*sizeof(char));
    
    
    //    char* temp = deveui2;
    //    char tear [24];
    //    char* temp2 = tear;
    /*
     snprintf的返回值是欲写入的字符串长度，而不是实际写入的字符串度
     */
    int sum = sizeof(device.deveui);
    char val[4];
    
    //int num = 0;
    printf("正序输出十六进制:\n");
    for (int k =0; k<sum; k++) {
        
        printf("%.2x-",device.deveui[k]);
        /*
         9f26c11224010141
         */
    }
    printf("\n");
    printf("逆序输出十六进制:\n");
    for (int k =sum-1; k>=0; k--) {
        
        snprintf(val, 3,"%.2x",device.deveui[k]);
        
       // size_t vallen =strlen(val);
        
        /*
         第二个参数为 size 如果源字符串格式化字符数大于或者等于这个size
         只将其中的(size-1)个字符复制到str中，并给其后添加一个字符串结束符('\0')
         
         如果小于这个size 则将字符串全部复制到其中 并给其后添加一个字符串结束符('\0')
         */
        //    snprintf(temp,vallen+1,"%s",val);
        //    snprintf(temp2,vallen+1,"%s",val);
        strcat(deveui, val);
        
        //        num  =num + (int)strlen(val);
        //        temp2 = temp2 + num*sizeof(char);
        //        temp = temp + num*sizeof(char);
        printf("%.2x-",device.deveui[k]);
        
    }
    printf("\n");
    //    sscanf(deveui, "%llu", &deval2);
    //    printf("uint64:%llu",deval2);
    
    printf("\n");
    //    char* endStr;
    //    long l =strtol(deveui, &endStr, 16);
    //    printf("l::%ld",l);
    printf("\n");
    printf("deveui:%s\n",deveui);
    printf("\n");
    /*%lx -> %p*/
    printf("deveui:%p\n",device.deveui);
    printf("\n");
    
    
    
    char* devaddr= malloc(24*sizeof(char));
    if (devaddr==NULL) {
        printf("分配内存出错\n");
    }
    memset(devaddr, 0, 24*sizeof(char));
    char valdevaddr[4];
    int sumvaldevaddr = sizeof(device.devaddr);
    for (int k =sumvaldevaddr-1; k>=0; k--)
    {
        snprintf(valdevaddr, 3,"%.2x",device.devaddr[k]);
        strcat(devaddr,valdevaddr); printf("%x-",device.devaddr[k]);
    }
    printf("devaddr:%s\n",devaddr);
    printf("devaddr:%p\n",device.devaddr);
    printf("\n");
    
    
    
    
    
   
    
    
    
    
    
    
   
    
    
    
    
    char* nwkskey= malloc(36*sizeof(char));
    if (nwkskey==NULL) {
        printf("分配内存出错\n");
    }
    memset(nwkskey, 0, 36*sizeof(char));
    char valnwkskey[4];
    int sumvalnwkskey = sizeof(device.nwkskey);
    for (int k =sumvalnwkskey-1; k>=0; k--) {
        snprintf(valnwkskey, 3,"%.2x",device.nwkskey[k]);
        strcat(nwkskey,valnwkskey); printf("%x-",device.nwkskey[k]);
    }
    
    
    printf("\n");
    printf("nwkskey:%s\n",nwkskey);
    printf("nwkskey:%p\n",device.nwkskey);
    printf("\n");
    
    
    
    
    char* devnonce= malloc(24*sizeof(char));
    if (devnonce==NULL) {
        printf("分配内存出错\n");
    }
    memset(devnonce, 0, 24*sizeof(char));
    char valdevnonce[4];
    int sumvaldevnonce = sizeof(device.devnonce);
    for (int k =sumvaldevnonce-1; k>=0; k--) {
        snprintf(valdevnonce, 3,"%.2x",device.devnonce[k]);
        strcat(devnonce,valdevnonce); printf("%x-",device.devnonce[k]);
    }
    
    
    printf("\n");
    printf("devnonce:%s\n",devnonce);
    printf("devnonce:%p\n",device.devnonce);
    printf("\n");
    
    
    
    
    char* place_holder2= malloc(24*sizeof(char));
    if (place_holder2==NULL) {
        printf("分配内存出错\n");
    }
    memset(place_holder2, 0, 24*sizeof(char));
    char valplace_holder2[4];
    int sumvalplace_holder2 = sizeof(device.__place_holder2);
    for (int k =sumvalplace_holder2-1; k>=0; k--) {
        snprintf(valplace_holder2, 3,"%.2x",device.__place_holder2[k]);
        strcat(place_holder2,valplace_holder2); printf("%x-",device.__place_holder2[k]);
    }
    
    printf("place_holder2:%s\n",place_holder2);
    printf("place_holder2:%p\n",device.__place_holder2);
    printf("\n");
    
    
    
    
    
    
   
    
    
    
    
    char* place_holder= malloc(24*sizeof(char));
    if (place_holder==NULL) {
        printf("分配内存出错\n");
    }
    memset(place_holder, 0, 24*sizeof(char));
    char valplace_holder[24];
    int sumvalplace_holder = 1;
    for (int k =sumvalplace_holder-1; k>=0; k--) {
        snprintf(valplace_holder, 24,"%x",device.__place_holder);
        strcat(place_holder,valplace_holder); printf("%x-",device.__place_holder);
    }
    printf("\n");
    printf("place_holder:%s\n",place_holder);
    printf("place_holder:%x\n",device.__place_holder);
    printf("\n");
    
    
    
    
   
    
    
    
    
    
    char* netid= malloc(24*sizeof(char));
    if (netid==NULL) {
        printf("分配内存出错\n");
    }
    memset(netid, 0, 24*sizeof(char));
    char valnetid[4];
    int sumvalnetid = sizeof(device.netid);
    for (int k =sumvalnetid-1; k>=0; k--) {
        snprintf(valnetid, 3,"%.2x",device.netid[k]);
        strcat(netid,valnetid); printf("%x-",device.netid[k]);
    }
    printf("\n");
    printf("netid:%s\n",netid);
    printf("netid:%p\n",device.netid);
    printf("\n");
    
    
    
    
    
    char* rx1droffset= malloc(24*sizeof(char));
    if (rx1droffset==NULL) {
        printf("分配内存出错\n");
    }
    memset(rx1droffset, 0, 24*sizeof(char));
    char valrx1droffset[24];
    int sumvalrx1droffset = 1;
    for (int k =sumvalrx1droffset-1; k>=0; k--) {
        snprintf(valrx1droffset, 24,"%x",device.rx1droffset);
        strcat(rx1droffset,valrx1droffset); printf("%x-",device.rx1droffset);
    }
    printf("rx1droffset:%s\n",rx1droffset);
    printf("rx1droffset:%x\n",device.rx1droffset);
    printf("\n");
    
    
    
    
    
    
    
    char* rx2dr= malloc(24*sizeof(char));
    if (rx2dr==NULL) {
        printf("分配内存出错\n");
    }
    memset(rx2dr, 0, 24*sizeof(char));
    char valrx2dr[24];
    int sumvalrx2dr = 1;
    for (int k =sumvalrx2dr-1; k>=0; k--) {
        snprintf(valrx2dr, 24,"%x",device.rx2dr);
        strcat(rx2dr,valrx2dr); printf("%x-",device.rx2dr);
    }
    printf("\n");
    printf("rx2dr:%s\n",rx2dr);
    printf("rx2dr:%x\n",device.rx2dr);
    printf("\n");
    
    
    
    
    
    
    char* rxdelay= malloc(24*sizeof(char));
    if (rxdelay==NULL) {
        printf("分配内存出错\n");
    }
    memset(rxdelay, 0, 24*sizeof(char));
    char valrxdelay[24];
    int sumvalrxdelay = 1;
    for (int k =sumvalrxdelay-1; k>=0; k--) {
        snprintf(valrxdelay, 24,"%x",device.rxdelay);
        strcat(rxdelay,valrxdelay); printf("%x-",device.rxdelay);
    }
    printf("\n");
    printf("rxdelay:%s\n",rxdelay);
    printf("rxdelay:%x\n",device.rxdelay);
    printf("\n");
    
    
    
    
    char* rx2_freq= malloc(24*sizeof(char));
    if (rx2_freq==NULL) {
        printf("分配内存出错\n");
    }
    memset(rx2_freq, 0, 24*sizeof(char));
    char valrx2_freq[24];
    int sumvalrx2_freq = 1;
    for (int k =sumvalrx2_freq-1; k>=0; k--) {
        snprintf(valrx2_freq, 24,"%x",device.rx2_freq);
        strcat(rx2_freq,valrx2_freq); printf("%x-",device.rx2_freq);
    }
    printf("\n");
    printf("rx2_freq:%s\n",rx2_freq);
    printf("rx2_freq:%x\n",device.rx2_freq);
    printf("\n");
    
    
    
    
    
    
    char* rxdelay_join= malloc(24*sizeof(char));
    if (rxdelay_join==NULL) {
        printf("分配内存出错\n");
    }
    memset(rxdelay_join, 0, 24*sizeof(char));
    char valrxdelay_join[24];
    int sumvalrxdelay_join = 1;
    for (int k =sumvalrxdelay_join-1; k>=0; k--) {
        snprintf(valrxdelay_join, 24,"%x",device.rxdelay_join);
        strcat(rxdelay_join,valrxdelay_join); printf("%x-",device.rxdelay_join);
    }
    printf("\n");
    printf("rxdelay_join:%s\n",rxdelay_join);
    printf("rxdelay_join:%x\n",device.rxdelay_join);
    printf("\n");
   
    
    
    
    char sql[8192];
    
#define sql2
    
    snprintf(sql, sizeof(sql),"insert into NS_MOTE_INFO (deveui,classmode,place_holder,place_holder2,appeui,nwkskey,devnonce,netid,rx1droffset,rx2dr,rxdelay,rx2_freq,standard,rxdelay_join,devaddr) values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')",deveui,classmode,place_holder,place_holder2,appeui,nwkskey,devnonce,netid,rx1droffset,rx2dr,rxdelay,rx2_freq,standard,rxdelay_join,devaddr);
    
    insertMysql(sql);
    
    
    
    
    //    if (deveui2!=NULL) {
    //        free(deveui2);
    //    }
    if (classmode!=NULL) {
        free(classmode);
    }
    if (standard!=NULL) {
        free(standard);
    }
  
    if (appeui!=NULL) {
        free(appeui);
    }
    if (deveui!=NULL) {
        free(deveui);
    }
    if (devaddr!=NULL) {
        free(devaddr);
    }
   
    if (nwkskey!=NULL) {
        free(nwkskey);
    }
    if (devnonce!=NULL) {
        free(devnonce);
    }
    if (place_holder2!=NULL) {
        free(place_holder2);
    }
    
    
    if (place_holder!=NULL) {
        free(place_holder);
    }
    
   
    if (netid!=NULL) {
        free(netid);
    }
    if (rx1droffset!=NULL) {
        free(rx1droffset);
    }
    if (rx2dr!=NULL) {
        free(rx2dr);
    }
    if (rxdelay!=NULL) {
        free(rxdelay);
    }
    
    if (rx2_freq!=NULL) {
        free(rx2_freq);
    }
   
    if (rxdelay_join!=NULL) {
        free(rxdelay_join);
    }
    
    
    
    
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
           
            
            checkDevice(&device);

            
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
            
            
            checkDevice2(&device);
            
            
        }
    }
    
    return RET_OK;
    
    
}


void findTargetDb(char* table)
{
    connectRedis(AS_REDIS_IP, AS_REDIS_PORT);
    
    targetDB = table;
    
    redisReply* r = (redisReply *)redisCommand(conn, "keys *");
    int ret = handleDBReply(r);
    freeReplyObject(r);
    
    if (ret == RET_OK) {
#if AS
     findKeysInTargetDB(targetDB);
#else
      findKeysInTargetDB2(targetDB);
#endif
        
    }
    
    
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

