//
//  SocketConnLink.c
//  NServerDuplicate
//
//  Created by admindyn on 2018/5/30.
//  Copyright © 2018年 admindyn. All rights reserved.
//



#include <errno.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>          /* for socket/bind/listen() */
#ifdef __APPLE__
//苹果操作系统!
#include <sys/fcntl.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#if TARGET_IPHONE_SIMULATOR

// 苹果下的iOS 模拟器操作系统



#elif TARGET_OS_IPHONE
// 苹果下的iOS操作系统

#elif TARGET_OS_MAC
// 苹果下的MAC 操作系统


#else

// 苹果下的其他 操作系统

#endif

#elif __linux__
//linux操作系统!
/* for socket/bind/listen() */
#include <linux/tcp.h>          /* for TCP_NODELAY */
#include <pthread.h>

#else
//其他操作系统 可能是 UNIX 或者 Windows


#endif
#include "event.h"
#include "ev.h"
#include "SocketConnLink.h"

SOCKET_CLIENT_T* clientHead;

static struct ev_loop *loop = NULL;  /* libev消息队列，用于注册监听插口fd及定时器 */
static SOCKET_CONN_T *conn = NULL;       /* 维护socket连接 */

/*socket 系统级 原生 结构体*/

static struct msghdr msg;            /* 报文信息结构体 */
static struct iovec iovec;           /* 报文缓存向量 */

static ev_idle idle;                 /* 空闲事件观测器 */
static int count = 0;


void* error_JUSTRET(void)
{
    return NULL;
}
void* error_close(int fd)
{
    printf("close udp\n");
    close(fd);
    return NULL;
}
void* error_free(SOCKET_CONN_T* conn)
{
    printf("free udp\n");
    free_conn(conn);
    return NULL;
}

void idle_main(void)
{
    count++;
    if (count / 30000000) {
        printf("in IDLE\n");
        count = 0;
    }
}
/* IDLE事件观测器的回调函数 */
static void idle_cb (EV_P_ ev_idle *w, int revents)
{
    (void)idle_main();
}

void readyKeyLoopStart(void)
{
/* 这里忽略了 该异常信号的 处理 SIG_ ignore*/
    
    
    signal(SIGPIPE, SIG_IGN);
    
    /* 初始化事件循环 */
    loop = EV_DEFAULT;
    
    /* 预分配链接结构; magic 100: 预分配结构数量 */
    int conn_num = 100;
    conn = (SOCKET_CONN_T*)malloc(conn_num * sizeof(SOCKET_CONN_T));
    (void)memset(conn, 0, conn_num * sizeof(SOCKET_CONN_T));
    for (int i=0; i<conn_num-1; i++) {
        conn[i].next = &conn[i+1];
    }
    conn[conn_num-1].next = NULL;
    
}
void start_event_loop(void)
{
    /* 注册idle事件 这里必须用 否则程序 不能够保活*/
    ev_idle_init (&idle, idle_cb);
    ev_idle_start (EV_A_ &idle);
   
    /*
     初始化 loop 结束后，调用这个函数开始 loop。如果 flags == 0，直至 loop 没有活跃的时间或者是调用了 ev_bread 之后停止。
     */
    
    /* 开启libev事件循环
     
     使用函数ev_run(loop, int flags)。
     
     这里解释一下flags的作用，用于设置ev_loop的运行方式：
     
     通常设置为0，表示该ev_loop在所有watcher结束后停止，也可以手动break
     */
    ev_run(EV_A_ 0);
}

SOCKET_CONN_T* get_socket_conn()
{
    
        //__typeof__(conn) tmp_st = conn;
        SOCKET_CONN_T* tmp_st = conn;
    
        if (conn) {
            
            conn = conn->next;
            
            tmp_st->next = NULL;
            
        } else {
           
            tmp_st = malloc(sizeof(*tmp_st));
            
            if (tmp_st) {
                
                (void)memset(tmp_st, 0, sizeof(*tmp_st));
                
            } else {
                
                printf("Socket 连接队列 初始化失败\n");
                
            }
        }
        return  tmp_st;
    
    
}

void free_conn(SOCKET_CONN_T*cn)
{
    if (NULL == cn) {
        printf("pointer NULL\n");
        return;
    }
    
    DestroyLinkQueue(cn->queue);
    
    do {
        
        cn->next = conn;
        conn = cn;
        
    } while(0);
    
}


/*
 启动 udp socket 服务器
 */
void* InitUDPSocketServerQueue(char* ip,unsigned short port,socketIO_callback readCallBack,socketIO_callback writeCallBack)
{
    struct sockaddr_in serverIP;
    
    SOCKET_CONN_T* tmp_conn = NULL;
    
    int fd;

    do {
        tmp_conn = get_socket_conn();
        if (tmp_conn == NULL) {
            
            return  error_JUSTRET();
        }
        tmp_conn->readCallBack = readCallBack;
        tmp_conn->writeCallBack = writeCallBack;
        tmp_conn->readFd.data = tmp_conn;
        tmp_conn->writeFd.data = tmp_conn;
        
        (void)memset(&serverIP, 0, sizeof(struct sockaddr_in));
        
        serverIP.sin_family = AF_INET;
        serverIP.sin_port = htons(port);
        if(inet_pton(AF_INET, ip, &serverIP.sin_addr) <= 0) {
           return error_free(tmp_conn);
        }
    } while(0);
    
#ifdef __APPLE__
    //苹果操作系统!
    /*
     socket 详解
     http://blog.csdn.net/ttyttytty12/article/details/8141910
     */
    fd = socket(AF_INET, SOCK_DGRAM , 0);
    //int flags = fcntl (fd, F_GETFL, 0);
    //fcntl (fd, F_SETFL, flags | FNONBLOCK|FD_CLOEXEC);
#if TARGET_IPHONE_SIMULATOR
    
    // 苹果下的iOS 模拟器操作系统
    
    
    
#elif TARGET_OS_IPHONE
    // 苹果下的iOS操作系统
    
#elif TARGET_OS_MAC
    // 苹果下的MAC 操作系统
    
    
#else
    
    // 苹果下的其他 操作系统
    
#endif
    
#elif __linux__
    //linux操作系统!
    /* for socket/bind/listen() */
    fd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    
#else
    //其他操作系统 可能是 UNIX 或者 Windows
    
    
#endif
    
    
    if (fd == -1) {
        printf("init server socket error\n");
          return error_free(tmp_conn);
       
    }
    
    int flag = 1;
    
 
    /*
     端口复用真正的用处主要在经常会碰到端口尚未完全关闭的情况，这时如果不设置端口复用，则无法完成绑定，因为端口还处于被别的套接口绑定的状态之中
     */
   
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    
    if (bind(fd, (const struct sockaddr *)&serverIP, sizeof(struct sockaddr_in)) == -1) {
        printf("set option server socket error\n");
          return error_close(fd);
    }
    //    printf("[watch] fd = %d\n",fd);
    

    /*
     Libev通过分配和注册watcher对不同类型的事件进行监听
     这些事件的监听是异步进行的，触发任意一个监听的事件，都可以根据我们的设定进行某些操作。
     */
    /*
     第一参数 设置监听者 ev_io
     
     第二参数 设置监听者收到监听激活状态后 调用的函数回调
     
     第三参数 监听者监听的激活源（激活源）
     
     第四参数 监听者监听激活源的那一方面 是读 还是写
     */
    ev_io_init(&tmp_conn->readFd, socket_udp_read, fd, EV_READ);
    
    ev_io_init(&tmp_conn->writeFd, socket_udp_write, fd, EV_WRITE);
    
    /*
     
     */
    ev_io_start(EV_A_  &tmp_conn->readFd);
   // ev_io_start(EV_A_  &tmp_conn->writeFd);
    


    
    return NULL;
}

void socket_udp_read(EV_P_ ev_io *w, int revents)
{
    if (w->active ==0) {
        printf("监听者acrive未被激活\n");
    }
    if (w->pending ==0) {
        printf("监听者pending未被激活\n");
    }
    
    SOCKET_CONN_T *tmp_conn = (SOCKET_CONN_T *)w->data;
    
    if (w->events&EV_READ) {
        printf("监听read事件\n");
    }
    if (w->events&EV_WRITE) {
        printf("监听write事件\n");
    }
    if ((w->events & ~(EV__IOFDSET | EV_READ | EV_WRITE))) {
        printf("libev: ev_io_start called with illegal event mask\n");
    }
    if (revents & EV_ERROR) {
        printf("socket libev read udp error\n");
        return;
    }
   /*
    assert(表达式);
    如果表达式的值为假，整个程序将退出，
    */

    
    common_intnet_generic_read(tmp_conn, true, false);
}
void socket_udpClient_read(EV_P_ ev_io *w, int revents)
{
    SOCKET_CONN_T*tmp_conn = (SOCKET_CONN_T *)w->data;
    struct sockaddr_in sip;
    
    if (revents & EV_ERROR) {
        printf("socket libev read  udp client  error\n");
        return;
    }
    
    /* 做为UDP客户端时，收到的远端IP地址可能不是对应的服务器IP地址；因此
     此处先保存此链接的服务器IP地址，接收数据报文后再恢复。
     
     做为UDP服务器时，不存在此问题，必须保存远端IP地址，以便回应时使用 */
    /* FIXME：如果收到的报文非原链接的服务器IP地址，报文应该直接丢弃!!! */
    (void)memcpy(&sip, &tmp_conn->ip, sizeof(struct sockaddr_in));
    common_intnet_generic_read(tmp_conn, true, false);
    (void)memcpy(&tmp_conn->ip, &sip, sizeof(struct sockaddr_in));
}

void socket_udp_write(EV_P_ ev_io *w, int revents)
{
    SOCKET_CONN_T *tmp_conn = (SOCKET_CONN_T *)w->data;
    
    if (revents & EV_ERROR) {
        printf("socket libev udp write error\n");
        return;
    }
    
    common_intnet_generic_write(tmp_conn, true);
    
}

/*
 启动 tcp socket 服务器
 
 */


void* InitTCPSocketServerQueue(char* ip,unsigned short port,socketIO_callback readCallBack,socketIO_callback writeCallBack)
{
    struct sockaddr_in serverIP;
    
    SOCKET_CONN_T* tmp_conn = NULL;
    
    int fd;
    
    do {
        tmp_conn = get_socket_conn();
        if (tmp_conn == NULL) {
            return error_JUSTRET();
        }
        tmp_conn->readCallBack = readCallBack;
        tmp_conn->writeCallBack = writeCallBack;
        /*
         这里的 data 是 我们要使用 libev io 监听
         io 必须要持有的 data 数据指针 这里指向连接本身
         */
        tmp_conn->readFd.data = tmp_conn;
        tmp_conn->writeFd.data = tmp_conn;
        
        (void)memset(&serverIP, 0, sizeof(struct sockaddr_in));
        
        serverIP.sin_family = AF_INET;
        serverIP.sin_port = htons(port);
        if(inet_pton(AF_INET, ip, &serverIP.sin_addr) <= 0) {
           return error_free(tmp_conn);
        }
    } while(0);
    
    
    
#ifdef __APPLE__
    //苹果操作系统!
    
    fd = socket(AF_INET, SOCK_STREAM , 0);
    /*
     watcher 负责检测文件描述符（以下简称fd）是否可写入数据或者是读出数据。最好是将fd设置为非阻塞的。
     　ioctl:提供对连接到fd的设备驱动程序的属性和操作的访问。
     
     　　而fcntl：用来设置和修改描述符的的属性。
     
     　　两种方法都可以用来设置socket阻塞与非阻塞模式。
     SOCK_NONBLOCK   Set the O_NONBLOCK file status flag on the new open file description.  Using this flag saves extra calls to fcntl(2) to  achieve  the  same
     result.
     
     SOCK_CLOEXEC    Set  the  close-on-exec (FD_CLOEXEC) flag on the new file descriptor.  See the description of the O_CLOEXEC flag in open(2) for reasons why
     this may be useful.
     */
/* 获取和设置文件阻塞flags*/
    
    int flags = fcntl (fd, F_GETFL, 0);
    fcntl (fd, F_SETFL, flags | FNONBLOCK|FD_CLOEXEC);
#if TARGET_IPHONE_SIMULATOR
    
    // 苹果下的iOS 模拟器操作系统
    
#elif TARGET_OS_IPHONE
    // 苹果下的iOS操作系统
    
#elif TARGET_OS_MAC
    // 苹果下的MAC 操作系统
    
#else
    
    // 苹果下的其他 操作系统
#endif
    
#elif __linux__
    //linux操作系统!
    /* for socket/bind/listen() */
    fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    
#else
    //其他操作系统 可能是 UNIX 或者 Windows
    
    
#endif
    if (fd == -1) {
        printf("tcp socket init error\n");
        return error_close(fd);
    }
    
    int flag = 1;                  /* 设置地址重用，非阻塞模式 */
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag)) == -1) {
        printf("set tcp socket option error\n");
        return error_close(fd);
    }
    
    if (bind(fd, (const struct sockaddr *)&serverIP, sizeof(struct sockaddr_in)) == -1) {
        printf("bind tcp server ip fail\n");
         return error_close(fd);
    }

    if (listen(fd, 512) == -1) {   /* magic 512: linux系统推荐值 */
        printf("listen tcp server fail\n");
         return error_close(fd);
    }
    
    /*
     Libev通过分配和注册watcher对不同类型的事件进行监听
     这些事件的监听是异步进行的，触发任意一个监听的事件，都可以根据我们的设定进行某些操作。
     */
    /*
     第一参数 设置监听者 ev_io
     
     第二参数 设置监听者收到监听激活状态后 调用的函数回调
     
     第三参数 监听者监听的激活源（激活源）
     
     第四参数 监听者监听激活源的那一方面 是读 还是写
     */
    /*
     每次TCP 三次握手后 才调用到这里
     
     监听套接字 只要进程活着 监听套接字 就一直活着
     
     一旦监听到 新的客户端要连接
     
     就被激活
     
     然后调用 accept 函数
     */
    
    ev_io_init(&tmp_conn->readFd, socket_tcp_accept, fd, EV_READ);
    
    ev_io_start(EV_A_  &tmp_conn->readFd);
    

    
    return NULL;
    
}

void socket_tcp_accept(EV_P_ ev_io *w, int revents)
{
    SOCKET_CONN_T *tmp_conn;
    
    int fd;
    
    if (revents & EV_ERROR) {
        printf("Recieve Error\n");
        return;
    }
    
    tmp_conn = get_socket_conn();
    
    if (tmp_conn == NULL) {
        printf("get connect error\n");
        return;
    }
    
    int len = sizeof(tmp_conn->ip);
    
    /*
     ev_io *w
     
     该结构体 有一个fd指针 保存这上一级函数
     
     要求监听的 IO 文件描述符 这里就是上一级的
     
     socket监听描述符
     
     accept 返回不同于之前的 监听套接字
     
     返回的是 连接套接字 我们后续的端与端之间的传输 使用该套接字
     
     */
    
    
    fd = accept(w->fd, (struct sockaddr*)&tmp_conn->ip, (socklen_t *)&len);
    
    
    if (fd == -1) {
        printf("accept error\n");
        free_conn(tmp_conn);
        return;
    }
    

    /* 继承回调函数指针 */
    tmp_conn->readCallBack = ((SOCKET_CONN_T*)(w->data))->readCallBack;
    
    tmp_conn->writeCallBack = ((SOCKET_CONN_T*)(w->data))->writeCallBack;
    
    tmp_conn->readFd.data = tmp_conn;
    
    tmp_conn->writeFd.data = tmp_conn;
    
    tmp_conn->queue = InitQueue();
    
    if (tmp_conn->queue == NULL) {
        return;
    }

    add_socket_client_conn(&tmp_conn->pkt);
    
    ev_io_init(&tmp_conn->readFd, socket_tcp_read, fd, EV_READ);
    
    ev_io_init(&tmp_conn->writeFd, socket_tcp_write, fd, EV_WRITE);
    
    printf("accept write fd is %d, read fd is %d\n", tmp_conn->writeFd.fd, tmp_conn->readFd.fd);
    
    ev_io_start(EV_A_  &tmp_conn->readFd);
    
}

void socket_tcp_read(EV_P_ ev_io *w, int revents)
{
    SOCKET_CONN_T *tmp_conn = (SOCKET_CONN_T *)w->data;
    
    if (revents & EV_ERROR) {
        printf("receive libev read error\n");
        return;
    }
    
    common_intnet_generic_read(tmp_conn, false, true);
    
}

void socket_tcp_write(EV_P_ ev_io *w, int revents)
{
    SOCKET_CONN_T *tmp_conn = (SOCKET_CONN_T *)w->data;
    
    if (revents & EV_ERROR) {
         printf("receive libev write error\n");
        return;
    }
    
    common_intnet_generic_write(tmp_conn, false);
    
}
/*
 Socket 读写 消息头
 */
void common_intnet_generic_read(SOCKET_CONN_T*conn,bool store_remote_addr,bool close_conn_when_fin)
{
    /* 做为UDP客户端时，收到的远端IP地址可能不是对应的服务器IP地址；因此
     此处先保存此链接的服务器IP地址，接收数据报文后再恢复。
     
     做为UDP服务器时，不存在此问题，必须保存远端IP地址，以便回应时使用 */
    /* FIXME：如果收到的报文非原链接的服务器IP地址，报文应该直接丢弃!!! */
    
    
    /*
     接收数据前初始化
     */
    
    if (store_remote_addr) {
        /*
         protocol address,
         TCP或连接型UDP应该设置为NULL
         recvmsg时由函数填充发送端地址
         sendmsg时手工填充接收目的地址
         */
        msg.msg_name = &conn->ip;
        msg.msg_namelen = sizeof(struct sockaddr_in);
    }else
    {
        /*
         protocol address,
         TCP或连接型UDP应该设置为NULL
         recvmsg时由函数填充发送端地址
         sendmsg时手工填充接收目的地址
         */
        msg.msg_name = NULL;
        msg.msg_namelen = 0;
    }
    
    /*
     读写IO的 起始指针 这里读写就直接将数据填充到了pkt buff地址
     pkt 内存 在程序启动时 先建立了socket连接的链表
     
     而socket连接的链表中每个节点 是一个socket连接的维护信息
     
     每个socket连接 又维护一个 socket 报文的 队列
     */
    iovec.iov_base = conn->pkt.buff;
    
    /*
     读写IO的 缓冲长度 一次读取的长度
     */
    iovec.iov_len = MSG_MAX_LEN;
    
    msg.msg_iov = &iovec;
    msg.msg_iovlen = 1;
    msg.msg_control = NULL;
    msg.msg_controllen = 0;
/*
 接收数据
 */
    
    int len;
    
    len = recvmsg(conn->readFd.fd, &msg, 0);
    
    if (len<0) {
        if (errno == EAGAIN||errno ==EINTR||errno == EWOULDBLOCK) {
            printf("recvmsg read error\n");
        }
        return;
    }else if(len == 0)
    {
        printf("recv FIN！！！！\n");
        if (close_conn_when_fin) {
            delete_socket_client_conn(conn);
        clear_socket_conn_resources(conn);
            
        }
        return;
    }
    
    conn->pkt.len = len;
    conn->readCallBack(&conn->pkt);
    
}
void delete_socket_client_conn(SOCKET_CONN_T* conn)
{
    SOCKET_CLIENT_T* client_current = clientHead;
    SOCKET_CLIENT_T* client_prev_pass = NULL;
    
    while ((SOCKET_CONN_T*)client_current->pkt != conn) {
        if (client_current->next ==NULL) {
            return;
        }
        client_prev_pass = client_current;
        client_current = client_current->next;
    }
    /*
     client 连接删除 修正 链表
     */
    client_prev_pass->next = client_current->next;
    free(client_current);
}

void clear_socket_conn_resources(SOCKET_CONN_T*conn)
{
    
    if (conn == NULL) {
        printf("should NOT null\n");
        return;
    }
    
    close(conn->readFd.fd);
    close(conn->readFd.fd);
    
    ev_io_stop(EV_A_ &conn->readFd);
    
    ev_io_stop(EV_A_ &conn->writeFd);
}


void common_intnet_generic_write(SOCKET_CONN_T* conn,bool set_remote_addr)
{
    /* 做为UDP客户端时，收到的远端IP地址可能不是对应的服务器IP地址；因此
     此处先保存此链接的服务器IP地址，接收数据报文后再恢复。
     
     做为UDP服务器时，不存在此问题，必须保存远端IP地址，以便回应时使用 */
    /* FIXME：如果收到的报文非原链接的服务器IP地址，报文应该直接丢弃!!! */
    
    /*发送数据前初始化*/
    if (set_remote_addr) {
        /*
         protocol address,
         TCP或连接型UDP应该设置为NULL
         recvmsg时由函数填充发送端地址
         sendmsg时手工填充接收目的地址
         */
        msg.msg_name = &conn->ip;
        msg.msg_namelen = sizeof(struct sockaddr_in);
    }else
    {
        /*
         protocol address,
         TCP或连接型UDP应该设置为NULL
         recvmsg时由函数填充发送端地址
         sendmsg时手工填充接收目的地址
         */
        msg.msg_name = NULL;
        msg.msg_namelen = 0;
    }
    /*
     读写IO的 起始指针
     */
    iovec.iov_base = conn->pkt.buff;
    /*
     读写IO的 缓冲长度 一次读取的长度
     */
    iovec.iov_len = conn->pkt.len;
    
    msg.msg_iov = &iovec;
    msg.msg_iovlen = 1;
    
    msg.msg_control = NULL;
    msg.msg_controllen = 0;
    
    /*发送数据 尝试3 次*/
    
    int count = 0;
    do {
        
        int len =0;
        
        len = sendmsg(conn->writeFd.fd, &msg, MSG_DONTWAIT);
        if (len<0) {
            printf("send len < 0 \n");
            break;
        }else
        {
            /*
             读写IO的 起始指针
             */
            iovec.iov_base = conn->pkt.buff + len;
            /*
             读写IO的 缓冲长度 一次读取的长度
             */
            iovec.iov_len = conn->pkt.len -len;
        }
        
        
    } while ((iovec.iov_len>0)&&(count++<3));
    if (count>=3) {
        printf("write socket count %d \n",count);
    }
    /*
     关闭写事件
     */
    ev_io_stop(EV_A_ &conn->writeFd);
    
    /*
     写成功后调用用户注册的回调
     */
    
    if (conn->writeCallBack) {
        conn->writeCallBack(&conn->pkt);
    }
    
    
}

/*
 Tcp Client socket
 */

int init_client_conn(void)
{
    SOCKET_CLIENT_T *client_new;
    
    client_new = (SOCKET_CLIENT_T *)malloc(sizeof(SOCKET_CLIENT_T));
    if (NULL == client_new) {
        printf("malloc cs client err\n");
        
        return -1;
    }
    memset(client_new->clientID, 0, sizeof(client_new->clientID));
    client_new->num = 0;
    client_new->pkt = NULL;
    client_new->next = NULL;
    clientHead = client_new;
    return 0;
}

void add_socket_client_conn(PKT*pkt)
{
    int num = 0;
    
    SOCKET_CLIENT_T* client_new;
    SOCKET_CLIENT_T* client_rear = clientHead;
    
    client_new = (SOCKET_CLIENT_T*)malloc(sizeof(SOCKET_CLIENT_T));
    
    if (NULL == client_new) {
        printf("malloc client error\n");
        
        return;
    }
    
    client_new->pkt = pkt;
    
    client_new->next = NULL;
    
    while (client_rear->next!=NULL) {
        client_rear = client_rear->next;
        if (++num > 1024) {
            printf("客户端连接数过多\n");
            goto do_free;
        }
    }
    
    client_rear->next = client_new;
    
do_free:
    free(client_new);
    
    
}



#if 0
/*
 成员msg_name与msg_namelen
 这些成员只有当我们的套接口是一个数据报套接口时才需要。msg_name成员指向我们要发送或是接收信息的套接口地址。成员msg_namelen指明了这个套接口地址的长度。
 当调用recvmsg时，msg_name会指向一个将要接收的地址的接收区域。当调用sendmsg时，这会指向一个数据报将要发送到的目的地址。
 注意，msg_name定义为一个(void *)数据类型。我们并不需要将我们的套接口地址转换为(struct sockaddr *)。
 成员msg_iov与msg_iovlen
 这些成员指定了我们的I/O向量数组的位置以及他包含多少项。msg_iov成员指向一个struct iovec数组。我们将会回忆起I/O向量指向我们的缓冲区。成员msg_iov指明了在我们的I/O向量数组中有多少元素。
 成员msg_control与msg_controllen
 这些成员指向了我们附属数据缓冲区并且表明了缓冲区大小。msg_control指向附属数据缓冲区，而msg_controllen指明了缓冲区大小。
 成员msg_flags
 当使用recvmsg时，这个成员用于接收特定的标记位(他并不用于sendmsg)
 
 */

重要的数据结构注解
struct msghdr {
    void *msg_name;         /* protocol address,
                             TCP或连接型UDP应该设置为NULL
                             recvmsg时由函数填充发送端地址
                             sendmsg时手工填充接收目的地址*/
    socklen_t msg_namelen;  /* size of protocol address */
    struct iovec *msg_iov;  /* scatter/gather array */
    int msg_iovlen;         /* # elements in msg_iov */
    void *msg_control;      /* ancillary data (cmsghdr struct) */
    socklen_t msg_controllen;   /* length of ancillary data */
    int msg_flags;          /* flags returned by recvmsg()
                             MSG_EOR         ends a logical record
                             MSG_OOB         带外数据, 被OSI使用
                             MSG_BCAST       是否为广播报文
                             MSG_MCAST       是否为多播报文
                             MSG_TRUNC       用户态buff不足导致截断
                             MSG_CTRUNC      ancillary data被截断
                             MSG_NOTIFICATION    被SCTP使用
                             */
};
struct iovec {
    void *iov_base;         /* starting address of buffer */
    size_t iov_len;         /* size of buffer */
};

recvmsg/sendmsg()的第三个参数flags:
MSG_DONTROUTE   [sendmsg]               直连网络, 不需要查找路由表
MSG_DONTWAIT    [sendmsg + recvmsg]     不阻塞等待IO完成
MSG_PEER        [recvmsg]               查看数据但系统不清空缓存
MSG_WAITALL     [recvmsg]               收到了指定大小的报文后再返回
#endif


















