//
//  SocketConnLink.h
//  NServerDuplicate
//
//  Created by admindyn on 2018/5/30.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef SocketConnLink_h
#define SocketConnLink_h

/*
 设计：
 1) 支持UDP、TCP监听接口，watch_tcp/watch_udp()
 2) 支持UDP、TCP客户端，alloc_tcp/alloc_udp()
 3) 支持服务器应答、支持客户端主动发送，send_pkt()
 4) 所有的报文处理必须无阻塞操作，延时操控可通过定时器实现
 5) UDP服务器收取的报文不支持延时应答
 6) TCP、UDP的读取通道维持打开，注意可重入性；
 7) 而发送通道，每调用一次send_pkt()打开一次；
 */

#include "ev.h"
#include "Queue.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MESGLIST_MAX_NUM 64

typedef void (*socketIO_callback)(PKT* pkt);
/*
 维护socket连接的信息
 */

typedef struct SOCKET_CONN_t{
    PKT pkt;
    
    SocketDataNode_QUEUE_T* queue;
    
    ev_io readFd;
    ev_io writeFd;
    
    socketIO_callback readCallBack;
    
    socketIO_callback writeCallBack;
    
    struct sockaddr_in ip;
    
    struct SOCKET_CONN_t* next;
    
    
}SOCKET_CONN_T;


typedef struct SOCKET_CLIENT_t{
    
    char clientID[32];
    uint8_t messageList[MESGLIST_MAX_NUM][8];
    int num;
    PKT* pkt;
    struct SOCKET_CLIENT_t* next;
    
    
}SOCKET_CLIENT_T;



SOCKET_CONN_T* get_socket_conn(void);



/*
 作为 socket udp 服务器
 */
void* InitUDPSocketServerQueue(char* ip,unsigned short port,socketIO_callback readCallBack,socketIO_callback writeCallBack);

void socket_udp_read(EV_P_ ev_io *w, int revents);

void socket_udp_write(EV_P_ ev_io *w, int revents);

/*
 作为 socket tcp 服务器
 */

void* InitTCPSocketServerQueue(char* ip,unsigned short port,socketIO_callback readCallBack,socketIO_callback writeCallBack);

void socket_tcp_accept(EV_P_ ev_io *w, int revents);

void add_socket_client_conn(PKT*pkt);

void socket_tcp_read(EV_P_ ev_io *w, int revents);

void socket_tcp_write(EV_P_ ev_io *w, int revents);

void common_intnet_generic_read(SOCKET_CONN_T*conn,bool store_remote_addr,bool close_conn_when_fin);

void common_intnet_generic_write(SOCKET_CONN_T* conn,bool set_remote_addr);


void delete_socket_client_conn(SOCKET_CONN_T* conn);

void clear_socket_conn_resources(SOCKET_CONN_T*conn);

/*
 客户端 socket
 */

PKT *Init_TCP_Client(char *ip, unsigned short port, socketIO_callback rcb, socketIO_callback wcb);
PKT *Init_UDP_Client(char *ip, unsigned short port, socketIO_callback rcb, socketIO_callback wcb);



/*
 发送数据包
 */

int send_tcp_pkt(PKT*pkt);

/*
 关闭连接服务
 */

int close_tcp_server(PKT* pkt);






















#endif /* SocketConnLink_h */
