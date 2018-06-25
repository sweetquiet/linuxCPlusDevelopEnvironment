//
//  mysqlclient.c
//  Redis_Mysql
//
//  Created by admindyn on 2018/3/13.
//  Copyright © 2018年 admindyn. All rights reserved.
//s
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <mysql.h>
#include "redisclient.h"
#include "SQL.h"
#include "datastruct.h"
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

void fetchMysql1(char* query)
{
    query = sql;
    //查询数据
    mysql_query(mysql, query);
    MYSQL_RES* res; //一个结果集结构体
    MYSQL_ROW row;  //char** 二维数组，存放一条条记录
    //获取结果集
    res = mysql_store_result(mysql);
    //显示数据
   
    int count = 0;
    
    while ((row = mysql_fetch_row(res)))
    {/*
      '0000000000000000'
      '4101012412c12525'
      '4101012412c13be2'
      */
        
        if (count==5000) {
            printf("5000睡眠20秒 %d \n",count);
#define sleeptest
            /*
             使用sleep 要导入 函数库
             #include <unistd.h>
             */
            sleep(10);
        }
        if (count==10000) {
            printf("10000睡眠20秒 %d \n",count);
            sleep(10);
        }
        if (count==15000) {
            printf("15000睡眠20秒 %d \n",count);
            sleep(10);
        }
        if (count==20000) {
            printf("20000睡眠20秒 %d \n",count);
            sleep(10);
        }
        
        count++;
        if (strcmp(row[0], "0000000000000000")==0) {
            printf("跳过0000000000000000\n");
            continue;
        }
        if (strcmp(row[0], "4101012412c12525")==0) {
             printf("跳过4101012412c12525\n");
            continue;
        }
        if (strcmp(row[0], "4101012412c13be2")==0) {
            
             printf("跳过4101012412c13be2\n");
            continue;
        }
        AS_MOTE_INFO *device = malloc(sizeof(AS_MOTE_INFO));
        memset(device, 0, sizeof(AS_MOTE_INFO));
        int valnum = 0;
        do {
            printf("字段序号%d-:%s\n",valnum,row[valnum]);
            

            
          
        
            

            switch (valnum) {
                case 0:
                    {
                        char* p =row[valnum];
                        char des[36]={'0','x'};
                        strcat(des, p);
                        printf("%s\n",des);
                            int zijiexu = sizeof(device->deveui)-1;
                        int vnum =0;
                        do {
                            char val[4]={'0','x'};
                            snprintf(val, 3, "%s",p);
                            printf("%s-",val);
                            long v =strtol(val, NULL, 16);
                            device->deveui[zijiexu] =(uint8_t)v;
                            zijiexu--;
                            printf("%ld-",v);
                            vnum++;
                            p=p+2;
                        } while (*p!='\0');
                        printf("\n");
                        printf("获得deveui:");
                        for (int i=0;i<sizeof(device->deveui); i++) {
                            printf("%.2x",device->deveui[i]);
                        }
                        printf("\n");
                    }
                    break;
                    
                case 1:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->classmode =(uint32_t)v;
                        printf("%ld-",v);
                        vnum++;
                        size_t len = strlen(p);
                        p=p+ len;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得classmode:");
                   
                    printf("%.2x",device->classmode);
                    
                    printf("\n");
                }
                    break;
                case 4:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                        int zijiexu = sizeof(device->appeui)-1;
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->appeui[zijiexu] =(uint8_t)v;
                        printf("%ld-",v);
                        zijiexu--;
                        vnum++;
                        p=p+2;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得appeui:");
                    
                    for (int i=0;i<sizeof(device->appeui); i++) {
                        printf("%.2x",device->appeui[i]);
                    }
                    
                    printf("\n");
                }
                    break;
                case 6:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                        int zijiexu = sizeof(device->appskey)-1;
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->appskey[zijiexu] =v;
                        printf("%ld-",v);
                        zijiexu--;
                        vnum++;
                        p=p+2;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得appskey:");
                    
                    for (int i=0;i<sizeof(device->appskey); i++) {
                        printf("%.2x",device->appskey[i]);
                    }
                    printf("\n");
                }
                    break;
                case 9:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int vnum =0;
                        int zijiexu = sizeof(device->netid)-1;
                    int chaval = sizeof(device->netid)-((int)strlen(p)/2);
                    do {
                        
                        if (chaval==0) {
                            char val[4]={'0','x'};
                            snprintf(val, 3, "%s",p);
                            printf("%s-",val);
                            long v =strtol(val, NULL, 16);
                            device->netid[zijiexu] =v;
                            printf("%ld-",v);
                            vnum++;
                            zijiexu--;
                            p=p+2;
                        }
                        if (chaval>0) {
                            for (int k=0; k<chaval; k++) {
                                device->netid[zijiexu] =0x00;
                                printf("补:%d-",0x00);
                                zijiexu--;
                                vnum++;
                                
                            }
                            chaval = 0;
                        
                        }
                       
                    } while (*p!='\0');
                    
                    printf("\n");
                    printf("获得netid:");
                    
                    for (int i=0;i<sizeof(device->netid); i++) {
                        printf("%.2x",device->netid[i]);
                    }
                    
                    printf("\n");
                }
                    break;
                    
                case 11:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->rx1droffset = (uint32_t)v;
                        printf("%ld-",v);
                        vnum++;
                        size_t len = strlen(p);
                        p=p + len;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得rx1droffset:");
                    
                  
                    printf("%.2x",device->rx1droffset);
                    
                    printf("\n");
                }
                    break;
                case 12:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->rx2dr = (uint32_t)v;
                        printf("%ld-",v);
                        vnum++;
                        size_t len = strlen(p);
                        p=p+ len;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得rx2dr:");
                    
                  
                    printf("%.2x",device->rx2dr);
                   
                    printf("\n");
                }
                    break;
                case 13:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->rxdelay =(uint32_t)v;
                        printf("%ld-",v);
                        vnum++;
                        size_t len = strlen(p);
                        p=p+ len;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得rxdelay:");
                    
                    
                    printf("%.2x",device->rxdelay);
                    
                    printf("\n");
                }
                    break;
                    
                case 14:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->rx2_freq =(uint32_t)v;
                        printf("%ld-",v);
                        vnum++;
                        size_t len = strlen(p);
                        p=p+ len;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得rx2_freq:");
                    
                  
                    printf("%.2x",device->rx2_freq);
                    
                    printf("\n");
                }
                    break;
                case 15:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->down_seqnum = (uint32_t)v;
                        printf("%ld-",v);
                        vnum++;
                        size_t len = strlen(p);
                        p= p+ len;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得down_seqnum:");
                    
                 
                        printf("%.2x",device->down_seqnum);
                  
                    printf("\n");
                }
                    break;
                case 16:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->up_seqnum =(uint32_t)v;
                        printf("%ld-",v);
                        vnum++;
                        size_t len = strlen(p);
                        p=p+ len;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得up_seqnum:");
                    
                   
                printf("%.2x",device->up_seqnum);
                    
                    printf("\n");
                }
                    break;
                case 17:
                {
                    char* p =row[valnum];
                    strcpy(device->systime, p);
                    printf("\n");
                    printf("获得systime:");
                    
                   
                    printf("%s",device->systime);
                    
                    printf("\n");
                }
                    break;
                case 20:
                {
                    char* p =row[valnum];
                    strcpy(device->standard, p);
                    printf("\n");
                    printf("获得standard:");
                    
                    
                    printf("%s",device->standard);
                    
                    printf("\n");
                }
                    break;
                case 21:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                        int zijiexu = sizeof(device->devaddr)-1;
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->devaddr[zijiexu] = (uint8_t)v;
                        printf("%ld-",v);
                        zijiexu--;
                        vnum++;
                        p=p+2;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得devaddr:");
                    
                    for (int i=0;i<sizeof(device->devaddr); i++) {
                        printf("%.2x",device->devaddr[i]);
                    }
                    
                    
                    printf("\n");
                }
                    break;
                    
                default:
                    break;
            }
           
          
            

            
           valnum++;
        } while (valnum<38);
         printf("---\n--");
        printf("########################---数据记录分割线--############");
         printf("---\n--");
#define  redisstore1
        
        char * deveui = row[0];
        
        printf("mysql1存储到redis-deveui:%s",deveui);
        store_binary_by_hash(AS_DEVICE_DB,deveui ,device, sizeof(AS_MOTE_INFO));
        
        free(device);
        printf("---\n--");
      

     
    }
    //释放结果集
    mysql_free_result(res);
    
    
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
void fetchMysql2(char* query)
{
    query = sql;
    //查询数据
    mysql_query(mysql, query);
    MYSQL_RES* res; //一个结果集结构体
    MYSQL_ROW row;  //char** 二维数组，存放一条条记录
    //获取结果集
    res = mysql_store_result(mysql);
    //显示数据
    
    int count = 0;

    printf("-----mysqlfetching-----\n");
    
    while ((row = mysql_fetch_row(res)))
    {/*
      '0000000000000000'
      '4101012412c12525'
      '4101012412c13be2'
      */
        
        if (count==5000) {
            printf("5000睡眠20秒 %d \n",count);
#define sleeptest
            /*
             使用sleep 要导入 函数库
             #include <unistd.h>
             */
            sleep(10);
        }
        if (count==10000) {
            printf("10000睡眠20秒 %d \n",count);
            sleep(10);
        }
        if (count==15000) {
            printf("15000睡眠20秒 %d \n",count);
            sleep(10);
        }
        if (count==20000) {
            printf("20000睡眠20秒 %d \n",count);
            sleep(10);
        }
        
        count++;
        if (strcmp(row[0], "0000000000000000")==0) {
            printf("跳过0000000000000000\n");
            continue;
        }
        if (strcmp(row[0], "4101012412c12525")==0) {
            printf("跳过4101012412c12525\n");
            continue;
        }
        if (strcmp(row[0], "4101012412c13be2")==0) {
            
            printf("跳过4101012412c13be2\n");
            continue;
        }
        NS_MOTE_INFO *device = malloc(sizeof(NS_MOTE_INFO));
        memset(device, 0, sizeof(NS_MOTE_INFO));
        int valnum = 0;
        
        do {
            printf("字段序号%d-:%s\n",valnum,row[valnum]);
            
            
            
            
            
            
            
            switch (valnum) {
                case 0:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int zijiexu = sizeof(device->deveui)-1;
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->deveui[zijiexu] =(uint8_t)v;
                        printf("%ld-",v);
                        vnum++;
                        zijiexu--;
                        p=p+2;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得deveui:");
                    for (int i=0;i<sizeof(device->deveui); i++) {
                        printf("%.2x",device->deveui[i]);
                    }
                    printf("\n");
                }
                    break;
                    
                case 1:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->classmode =(uint32_t)v;
                        printf("%ld-",v);
                        vnum++;
                        size_t len = strlen(p);
                        p=p+ len;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得classmode:");
                    
                    printf("%.2x",device->classmode);
                    
                    printf("\n");
                }
                    break;
                case 4:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int zijiexu = sizeof(device->appeui)-1;
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->appeui[zijiexu] =(uint8_t)v;
                        printf("%ld-",v);
                        vnum++;
                        zijiexu--;
                        p=p+2;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得appeui:");
                    
                    for (int i=0;i<sizeof(device->appeui); i++) {
                        printf("%.2x",device->appeui[i]);
                    }
                    
                    printf("\n");
                }
                    break;
                case 6:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                     int zijiexu = sizeof(device->apps_key)-1;
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->apps_key[zijiexu] =v;
                        printf("%ld-",v);
                        zijiexu--;
                        vnum++;
                        p=p+2;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得apps_key:");
                    
                    for (int i=0;i<sizeof(device->apps_key); i++) {
                        printf("%.2x",device->apps_key[i]);
                    }
                    printf("\n");
                }
                    break;
                case 7:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int zijiexu = sizeof(device->js_int_key)-1;
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->js_enc_key[zijiexu] =v;
                        device->js_int_key[zijiexu] =v;
                        device->fnwks_key[zijiexu] =v;
                        device->snwks_key[zijiexu] =v;
                        printf("%ld-",v);
                        zijiexu--;
                        vnum++;
                        p=p+2;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得js_enc_key:");
                    
                    for (int i=0;i<sizeof(device->js_enc_key); i++) {
                        printf("%.2x",device->js_enc_key[i]);
                    }
                    printf("\n");
                    printf("获得js_int_key:");
                    
                    for (int i=0;i<sizeof(device->js_int_key); i++) {
                        printf("%.2x",device->js_int_key[i]);
                    }
                    printf("\n");
                    printf("获得fnwks_key:");
                    
                    for (int i=0;i<sizeof(device->fnwks_key); i++) {
                        printf("%.2x",device->fnwks_key[i]);
                    }
                    printf("\n");
                    printf("获得snwks_key:");
                    
                    for (int i=0;i<sizeof(device->snwks_key); i++) {
                        printf("%.2x",device->snwks_key[i]);
                    }
                    printf("\n");
                }
                    break;
                case 9:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                     int zijiexu = sizeof(device->netid)-1;
                    int vnum =0;
                    int chaval = sizeof(device->netid)-((int)strlen(p)/2);
                    do {
                        
                        if (chaval==0) {
                            char val[4]={'0','x'};
                            snprintf(val, 3, "%s",p);
                            printf("%s-",val);
                            long v =strtol(val, NULL, 16);
                            device->netid[zijiexu] =v;
                            printf("%ld-",v);
                            zijiexu--;
                            vnum++;
                            p=p+2;
                        }
                        if (chaval>0) {
                            for (int k=0; k<chaval; k++) {
                                device->netid[zijiexu] =0x00;
                                printf("补:%d-",0x00);
                                vnum++;
                                zijiexu--;
                                
                            }
                            chaval = 0;
                            
                        }
                        
                    } while (*p!='\0');
                    
                    printf("\n");
                    printf("获得netid:");
                    
                    for (int i=0;i<sizeof(device->netid); i++) {
                        printf("%.2x",device->netid[i]);
                    }
                    
                    printf("\n");
                }
                    break;
                    
                case 11:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->rx1droffset = (uint32_t)v;
                        printf("%ld-",v);
                        vnum++;
                        size_t len = strlen(p);
                        p=p + len;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得rx1droffset:");
                    
                    
                    printf("%.2x",device->rx1droffset);
                    
                    printf("\n");
                }
                    break;
                case 12:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->rx2dr = (uint32_t)v;
                        printf("%ld-",v);
                        vnum++;
                        size_t len = strlen(p);
                        p=p+ len;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得rx2dr:");
                    
                    
                    printf("%.2x",device->rx2dr);
                    
                    printf("\n");
                }
                    break;
                case 13:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->rxdelay =(uint32_t)v;
                        printf("%ld-",v);
                        vnum++;
                        size_t len = strlen(p);
                        p=p+ len;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得rxdelay:");
                    
                    
                    printf("%.2x",device->rxdelay);
                    
                    printf("\n");
                }
                    break;
                    
                case 14:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->rx2_freq =(uint32_t)v;
                        printf("%ld-",v);
                        vnum++;
                        size_t len = strlen(p);
                        p=p+ len;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得rx2_freq:");
                    
                    
                    printf("%.2x",device->rx2_freq);
                    
                    printf("\n");
                }
                    break;
                    
                case 37:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->rxdelay_join =(uint32_t)v;
                        printf("%ld-",v);
                        vnum++;
                        size_t len = strlen(p);
                        p=p+ len;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得rxdelay_join:");
                    
                    
                    printf("%.2x",device->rxdelay_join);
                    
                    printf("\n");
                }
                    break;
              
               
                case 20:
                {
                    char* p =row[valnum];
                    strcpy(device->standard, p);
                    printf("\n");
                    printf("获得standard:");
                    
                    
                    printf("%s",device->standard);
                    
                    printf("\n");
                }
                    break;
                case 21:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int  zijiexu = sizeof(device->devaddr)-1;
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->devaddr[zijiexu] = (uint8_t)v;
                        printf("%ld-",v);
                        vnum++;
                        zijiexu--;
                        p=p+2;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得devaddr:");
                    
                    for (int i=0;i<sizeof(device->devaddr); i++) {
                        printf("%.2x",device->devaddr[i]);
                    }
                    
                    
                    printf("\n");
                }
                    break;
                    /*---*/
                case 5:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                     int  zijiexu = sizeof(device->nwkkey)-1;
                    int vnum =0;
                    do {
                        char val[4]={'0','x'};
                        snprintf(val, 3, "%s",p);
                        printf("%s-",val);
                        long v =strtol(val, NULL, 16);
                        device->nwkkey[zijiexu] = (uint8_t)v;
                        printf("%ld-",v);
                        vnum++;
                        zijiexu--;
                        p=p+2;
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得nwkkey:");
                    
                    for (int i=0;i<sizeof(device->nwkkey); i++) {
                        printf("%.2x",device->nwkkey[i]);
                    }
                    
                    
                    printf("\n");
                }
                    break;
                case 8:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                     int  zijiexu = sizeof(device->devnonce)-1;
                    int vnum =0;
                    int chaval = sizeof(device->devnonce)-((int)strlen(p)/2);
                    do {
                        
                        if (chaval==0) {
                            char val[4]={'0','x'};
                            snprintf(val, 3, "%s",p);
                            printf("%s-",val);
                            long v =strtol(val, NULL, 16);
                            device->devnonce[zijiexu] =v;
                            printf("%ld-",v);
                            vnum++;
                            zijiexu--;
                            p=p+2;
                        }
                        if (chaval>0) {
                            for (int k=0; k<chaval; k++) {
                                device->devnonce[zijiexu] =0x00;
                                printf("补:%d-",0x00);
                                vnum++;
                                zijiexu--;
                                
                            }
                            chaval = 0;
                            
                        }
                        
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得devnonce:");
                    
                    for (int i=0;i<sizeof(device->devnonce); i++) {
                        printf("%.2x",device->devnonce[i]);
                    }
                    printf("\n");
                }
                    break;
                    
                case 22:
                {
                    char* p =row[valnum];
                    char des[36]={'0','x'};
                    strcat(des, p);
                    printf("%s\n",des);
                    int  zijiexu = sizeof(device->appnonce)-1;
                    int vnum =0;
                    int chaval = sizeof(device->appnonce)-((int)strlen(p)/2);
                    do {
                        
                        if (chaval==0) {
                            char val[4]={'0','x'};
                            snprintf(val, 3, "%s",p);
                            printf("%s-",val);
                            long v =strtol(val, NULL, 16);
                            device->appnonce[zijiexu] =v;
                            printf("%ld-",v);
                            vnum++;
                            zijiexu--;
                            p=p+2;
                        }
                        if (chaval>0) {
                            for (int k=0; k<chaval; k++) {
                                device->appnonce[zijiexu] =0x00;
                                printf("补:%d-",0x00);
                                vnum++;
                                zijiexu--;
                                
                            }
                            chaval = 0;
                            
                        }
                        
                    } while (*p!='\0');
                    printf("\n");
                    printf("获得appnonce:");
                    
                    for (int i=0;i<sizeof(device->appnonce); i++) {
                        printf("%.2x",device->appnonce[i]);
                    }
                    printf("\n");
                }
                    break;
                    
                    
                    
                default:
                    break;
            }
            
            
            
            
            
            valnum++;
        } while (valnum<38);
        printf("########################---数据记录分割线--###########################");
        printf("---\n--");
#define  redisstore2
        printf("\n");
        printf("nwksenc_key:");
        for (int m =0; m<sizeof(device->nwksenc_key); m++) {
            device->nwksenc_key[m]= 0x00;
        }
        for (int m =0; m<sizeof(device->nwksenc_key); m++) {
            printf("%.2x",device->nwksenc_key[m]);
        }
        printf("\n");
        
        printf("\n");
        printf("multi_key:");
        for (int m =0; m<sizeof(device->multi_key); m++) {
            device->multi_key[m]= 0x00;
        }
        for (int m =0; m<sizeof(device->multi_key); m++) {
            printf("%.2x",device->multi_key[m]);
        }
        printf("\n");
       
       
        printf("\n");
        printf("multiaddr:");
        for (int m =0; m<sizeof(device->multiaddr); m++) {
            device->multiaddr[m]= 0x00;
        }
        for (int m =0; m<sizeof(device->multiaddr); m++) {
            printf("%.2x",device->multiaddr[m]);
        }
        printf("\n");
        
        device->beacon_dr=0x00;
        
       device->beacon_rx_slot=0x00;
        
        device->beacon_freq=0x00;
        device->classb_multi_dr=0x00;
         device->classb_multi_slot=0x00;
         device->classb_multi_freq=0x00;
        
        strcpy(device->reserve, "");
        printf("\n");
        printf("reverve:%s",device->reserve);
        printf("\n");
        
        
       
        time_t timep;
        
        time(&timep);
        
        strcpy(device->join_time,ctime(&timep));
        
        printf("time:%s\n", device->join_time);
        strcpy(device->lorawan_version,"1.0.2");
        
        printf("version:%s\n", device->lorawan_version);
        printf("\n");
        char * deveui = row[0];
        
        printf("mysql2存储到redis-deveui:%s",deveui);
    store_binary_by_hash(AS_DEVICE_DB,deveui ,device, sizeof(NS_MOTE_INFO));
        
        free(device);
        printf("---\n--");
        
        
        
    }
    //释放结果集
    mysql_free_result(res);
    
    
}
