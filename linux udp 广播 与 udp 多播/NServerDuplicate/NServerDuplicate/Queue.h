//
//  Queue.h
//  NServerDuplicate
//
//  Created by admindyn on 2018/5/30.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef Queue_h
#define Queue_h

#include <stdio.h>


#define Queuelen 256

#define QueueSize 32

#define DataType TMDATA

#define MSG_MAX_LEN  8192         /* 缓存报文的最大长度 */

typedef struct st_timer_data {
    int seq;
    void *ptr;
    uint8_t devaddr[4];
    uint8_t deveui[8];
}TMDATA;

/*
 报文缓存
 */
typedef struct st_pkt_t {
    
    char buff[MSG_MAX_LEN];
    int len;
    /*读取时 接收长度 ；发送时 已发送长度*/
}PKT;

typedef struct SocketDataNode_T{
    
    PKT pkt;
    
    struct SocketDataNode_T* next;
    
}SocketDataNode_T,*SocketDataNode_T_Ptr;

typedef struct SocketDataNode_QUEUE_t{
    
    SocketDataNode_T_Ptr front,rear;
    
    
}SocketDataNode_QUEUE_T;


SocketDataNode_QUEUE_T * InitQueue(void);

int EnQueue(SocketDataNode_QUEUE_T* queue,PKT* x);

int DeQueue(SocketDataNode_QUEUE_T* queue,PKT * x);

void ClearLinkQueue(SocketDataNode_QUEUE_T* queue);

void DestroyLinkQueue(SocketDataNode_QUEUE_T* queue);


















#endif /* Queue_h */
