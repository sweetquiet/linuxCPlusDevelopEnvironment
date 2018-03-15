//
//  datastruct.h
//  Redis_Mysql
//
//  Created by admindyn on 2018/3/13.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef datastruct_h
#define datastruct_h

#include <stdbool.h>
#include <stdio.h>

#define name2str(name) (#name)

typedef struct as_info_t {
    char operation[8];
    char sn[64];
    uint32_t token;
    char name[32];
    char ns_ip[32];
    uint32_t ns_port;
    char mqtt_ip[32];
    uint32_t mqtt_port;
    char mqtt_username[32];
    char mqtt_password[32];
    char config_ip[32];
    uint32_t config_port;
    uint32_t mysql_enable;
    char mysql_user[32];
    char mysql_db[32];
    char mysql_pwd[32];
    char mysql_ip[32];
    uint32_t mysql_port;
    char redis_ip[32];
    uint32_t redis_port;
}as_info_t;


/* 定义通用返回值 */
#define RET_OK      0
#define RET_NIL     2
#define RET_ERR       -1

#define AS 1

/*######AS Device List#########*/

#define AS_REDIS_PORT 6379

#if AS
#define AS_REDIS_IP "192.168.3.237"
#define AS_DEVICE_DB "as_db"
#else
#define AS_REDIS_IP "192.168.3.236"
#define AS_DEVICE_DB "bx_ns_mote_db"
#endif



/*
 1字节     uint8_t
 2字节     uint16_t
 4字节     uint32_t
 8字节     uint64_t
 */

typedef struct st_json_data_down {
    uint32_t classmode;
    uint8_t deveui[8];
    bool confirmed;
    uint8_t __place_holder[3];/* 占位符 */
    uint32_t session_id;
    uint32_t token;
    uint32_t seqno;
    uint8_t port;
    uint8_t __place_holder1[3];/* 占位符 */
    uint32_t size;
    uint8_t payload[256];
}Data_Down_Json;

typedef struct st_as_mote_dnqueue {
    int num;
    Data_Down_Json datadn[48];
}AS_MOTEDN_Q;
typedef struct st_as_mote_info {
    uint32_t classmode;
    char standard[16];
    char datr[16];
    char codr[16];
    uint8_t deveui[8];
    uint8_t appeui[8];
    uint8_t devaddr[4];
    uint8_t appkey[16];
    uint8_t appskey[16];
    uint8_t nwkskey[16];
    uint8_t devnonce[2];
    uint8_t __place_holder2[2];  /* 占位符 */
    uint8_t appnonce[3];
    uint8_t __place_holder;  /* 占位符 */
    uint8_t netid[3];
    uint8_t __place_holder1;  /* 占位符 */
    uint32_t rx1droffset;
    uint32_t rx2dr;
    uint32_t rxdelay;
    uint32_t rx2_freq;
    uint32_t down_seqnum;
    uint32_t up_seqnum;
    char systime[32];
    AS_MOTEDN_Q moteq;
}AS_MOTE_INFO;
/*
 

 
 CREATE TABLE AS_MOTE_INFO (deveui VARCHAR(64) NOT NULL,classmode VARCHAR(64) NULL,place_holder VARCHAR(64) NULL,place_holder2 VARCHAR(64) NULL,appeui VARCHAR(64) NULL,appkey VARCHAR(64) NULL,appskey VARCHAR(64) NULL,nwkskey VARCHAR(64) NULL,devnonce VARCHAR(64) NULL,netid VARCHAR(64) NULL,place_holder1 VARCHAR(64) NULL,rx1droffset VARCHAR(64) NULL,rx2dr VARCHAR(64) NULL,rxdelay VARCHAR(64) NULL,rx2_freq VARCHAR(64) NULL,down_seqnum VARCHAR(64) NULL,up_seqnum VARCHAR(64) NULL,systime VARCHAR(64) NULL,datr VARCHAR(64) NULL,codr VARCHAR(64) NULL,standard VARCHAR(64) NULL,devaddr VARCHAR(64) NULL,appnonce VARCHAR(64) NULL,PRIMARY KEY (`deveui`));
 
 INSERT INTO AS_MOTE_INFO (classmode, standard, confirmed,place_holder,deveui,appeui,devaddr,appkey,appskey,nwkskey,devnonce,place_holder2,netid,appnonce,place_holder1,rx1droffset,rx2dr,rxdelay,rx2_freq,down_seqnum,up_seqnum,systime)
 VALUES (value1, value2, value3,...valueN);
 
 
 
 
 INSERT INTO AS_MOTEDN_Q (classmode, deveui, datr,codr,deveui,session_id,token,seqno,port,place_holder1,size,payload)
 VALUES (value1, value2, value3,...valueN);
 */

typedef struct KVS {
    char* key;
    char* val;
    struct KVS* current;
    struct KVS* next;
}KVS;
/*NS- */
typedef struct st_ns_mote_info {
    uint8_t deveui[8];
    uint8_t appeui[8];
    uint8_t devaddr[4];
    uint8_t nwkskey[16];
    uint8_t netid[3];
    uint8_t __place_holder;  /* 占位符 */
    uint8_t devnonce[2];
    uint8_t __place_holder2[2];  /* 占位符 */
    uint32_t classmode;
    char standard[16];
    uint32_t rx1droffset;
    uint32_t  rx2dr;
    uint32_t rxdelay;
    uint32_t rxdelay_join;
    uint32_t rx2_freq;
}NS_MOTE_INFO;
/*
CREATE TABLE NS_MOTE_INFO (deveui VARCHAR(64) NOT NULL,classmode VARCHAR(64) NULL,place_holder VARCHAR(64) NULL,place_holder2 VARCHAR(64) NULL,appeui VARCHAR(64) NULL,nwkskey VARCHAR(64) NULL,devnonce VARCHAR(64) NULL,netid VARCHAR(64) NULL,rx1droffset VARCHAR(64) NULL,rx2dr VARCHAR(64) NULL,rxdelay VARCHAR(64) NULL,rx2_freq VARCHAR(64) NULL,standard VARCHAR(64) NULL,rxdelay_join VARCHAR(64) NULL,devaddr VARCHAR(64) NULL,PRIMARY KEY (`deveui`));
 */

#endif /* datastruct_h */
