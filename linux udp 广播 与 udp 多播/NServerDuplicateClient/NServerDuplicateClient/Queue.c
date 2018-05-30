//
//  Queue.c
//  NServerDuplicate
//
//  Created by admindyn on 2018/5/30.
//  Copyright © 2018年 admindyn. All rights reserved.
//



#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"


SocketDataNode_QUEUE_T* InitQueue(void)
{
    /*
     初始化队列结构体 指针
     
     队列结构体 只保留 整个队列链表的 整个报文链表的 头指针 和 尾指针
     
     
     */
    SocketDataNode_QUEUE_T* lp = (SocketDataNode_QUEUE_T*)malloc(sizeof(SocketDataNode_QUEUE_T));
    
    if (lp == NULL) {
        printf("Init queue pointer is null");
        
        return NULL;
    }
    
    
    lp->front = lp->rear =(SocketDataNode_T*)malloc(sizeof(SocketDataNode_T));
    if (lp->front == NULL) {
        printf("init queque front pointer is NULL");
        
        return NULL;
    }
    
    lp->front->next = NULL;
    
    return lp;
    
    
}


void DestroyLinkQueue(SocketDataNode_QUEUE_T* queue)
{
    if (queue != NULL) {
    
    ClearLinkQueue(queue);
        free(queue);
        
        
    }
    
    
}
void ClearLinkQueue(SocketDataNode_QUEUE_T* queue)
{
    SocketDataNode_T* dataNode;
    
    while (queue->front) {
        /*
         从队列不断取出数据包节点
         
         数包节点next 不断取出 给到 队列的队首front
         
         loop
         */
        dataNode = queue->front;
        
        queue->front = dataNode->next;
        
        free(dataNode);
    }
    queue->rear = NULL;
    
}

int EmptyLinkQueue(SocketDataNode_QUEUE_T* queue)
{
    if (queue == NULL) {
        return  -1;
    }
    
    return (queue->front == queue->rear ? 1:0);
    
    
}

int EnQueue(SocketDataNode_QUEUE_T* queue,PKT* x)
{
    
    SocketDataNode_T* node_new;
    if (queue == NULL) {
        printf("queue pointer is null");
        return -1;
    }
    
    node_new = (SocketDataNode_T*)malloc(sizeof(SocketDataNode_T));
    if (node_new == NULL) {
        
        printf("malloc failed");
        return  -1;
    }
    /*
     这里节点 数据缓存 每次传来的报文数据
     
     要内存copy 到上面 malloc 的结构体空间
     
     这样才不怕其他操作 导致 报文数据释放
     */
    memcpy(&node_new->pkt, x, sizeof(node_new->pkt));
    
    node_new->next = NULL;
    
    if (queue->front->next ==NULL) {
        /*
         如果队首头节点没数据
         
         将新初始化的数据节点 给到队首
         
         同时队尾也要指向该数据节点指针
         */
        queue->front->next = node_new;
        queue->rear= node_new;
    }else
    {
        /*
         如果队首有数据了
         
         那对不起 不修改队首
         
         直接往队尾 数据节点 next 追加
         
         */
        queue->rear->next = node_new;
        queue->rear = node_new;
    }
    
    return 0;
    
    
}

int DeQueue(SocketDataNode_QUEUE_T* queue,PKT * x)
{
    SocketDataNode_T* dataNode;
    
    if (queue==NULL) {
        printf("queue pointer is null");
        return -1;
    }
    if (queue->front->next == NULL) {
        printf("queue is empty");
        return -1;
    }
    
    dataNode = queue->front->next;
    queue->front->next = dataNode->next;
    
    memcpy(x, &dataNode->pkt, sizeof(dataNode->pkt));
    
    free(dataNode);
    
    return 0;
    
}
















