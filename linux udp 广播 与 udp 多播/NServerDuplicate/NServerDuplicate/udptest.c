//
//  udptest.c
//  NServerDuplicate
//
//  Created by admindyn on 2018/5/30.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include "udptest.h"

/*广播*/

#define BUFLEN 255 //广播
/*多播*/

#define MCAST_PORT 8888


#define MCAST_ADDR "224.0.0.100" //多播地址

/*
 一个局部连接多播地址 路由器不进行转发
 */

#define MCAST_DATA "BROADCAST TEST DATA" //多播内容

#define MCAST_INTERVAL 5 //多播时间间隔

#define BUFF_SIZE 256 //接收缓冲区大小


void  testUDPGuangBoServer(void)
{
    struct sockaddr_in  localAddr;
    
    int sockfd;
    
    int socklen, n;
    
    /*
     创建UDP数据包socket描述符
     */
    
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    
    if (sockfd<0) {
        printf("socket creating err \n");
        return;
    }
    
    printf("IP address checking 1!\n");
    
    socklen = sizeof(struct sockaddr_in);
    
  
    
   

    
    /*
     设置udp服务器本机IP地址 与 端口 我们可以接受符合端口的所有包
     */
    
    memset(&localAddr,0,socklen);
    
    localAddr.sin_family=AF_INET;
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localAddr.sin_port = htons(8904);
    
    /*
     设置IPPROTO_IP 以便获取UDP包中的信息
     */
    
    int opt = 1;
    setsockopt(sockfd, IPPROTO_IP, IP_PKTINFO, &opt, sizeof(opt));
   
    
    printf("IP Address checking 2\n");
    /*
     这里为控制数据申请一个空间
     */
    char cmbuf[100];
    
    /*
     初始化msg_iovec字段  一边获取UDP包数据域
     */
    
    char buffer[BUFLEN+1];
    
    struct iovec iov[1];
    
    iov[0].iov_base = buffer;
    iov[0].iov_len = sizeof(buffer);
    
    
    /*
     初始化struct msghdr 以便获取UDP包中目标IP地址与 源地址
     */
    
    
    struct msghdr  mesg  = { .msg_name = &localAddr,.msg_namelen = sizeof(localAddr),.msg_control = cmbuf,.msg_controllen = sizeof(cmbuf),.msg_iov = iov,.msg_iovlen=1};
    
    /*
     将本机地址信息与sockfd绑定起来
     */
    
    if (bind(sockfd, (struct sockaddr*)&localAddr, socklen)<0) {
        printf("bind server ip fail\n");
        return;
    }
    
 
    printf("start recieve message\n");
    
    for (; ; ) {
        
        
        
        printf("Waiting For Message..!\n");
        
        
        n= recvmsg(sockfd, &mesg, 0);
        
        //判断socket 是否有发生错误
        
        if (n<0) {
            printf("receive udp pkt err \n");
            
            return;
        }else
        {
            
            cmbuf[n] = 0;
            printf("Receive:%d Byte ;The Message Is : %s\n",n,buffer);
        }
        /*
         初始化 cmsghdr 一边处理mes 中的附属数据 通过遍历附属数据对象 找出我们感兴趣的信息
         */
        
        
        struct  cmsghdr * cmesg;
        
        for (cmesg = CMSG_FIRSTHDR(&mesg); cmesg!=NULL; cmesg = CMSG_NXTHDR(&mesg, cmesg)) {
            /*
             忽略我们不需要的控制头
             */
            
            if (cmesg->cmsg_level != IPPROTO_IP|| cmesg->cmsg_type!=IP_PKTINFO) {
                continue;
            }
            
            struct in_pktinfo*pi = CMSG_DATA(cmesg);
            
            /*
             将地址信息转换后输出
             */
            /*
             用来保存转换后的源IP地址 目标主机地址
             */
            char dst[100],ipi[100];
            if ((inet_ntop(AF_INET, &(pi->ipi_spec_dst), dst, sizeof(dst)))!=NULL) {
                printf("路由目的IP地址IPdst=%s \n",dst);
            }
            
            if ((inet_ntop(AF_INET, &(pi->ipi_addr), ipi, sizeof(ipi))!=NULL)) {
                printf("头标识目的地址ipiaddr;%s\n",ipi);
            }
        }
        
        printf("Send some Message To Server\n");
        
         struct sockaddr_in  destinationAddr;
        
        memset(&destinationAddr,0,socklen);
        
        /*
         设置目标主机IP 和端口号 这里我们使用广播方式
         */
        
        destinationAddr.sin_family = AF_INET;
        destinationAddr.sin_port = htons(8903);
        /*
         广播UDP与单播UDP的区别就是IP地址不同，广播使用广播地址255.255.255.255，将消息发送到在同一广播网络上的每个主机。值得强调的是：本地广播信息是不会被路由器转发
         */
        destinationAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
        
        
        if (sendto(sockfd, "HELLO", strlen(buffer), 0, (struct sockaddr*)&destinationAddr, socklen)) {
            printf("send to err\n");
            return;
        }
    }
    
    
    
    
    
    
    
    
}

void  testUDPGuangBoClient(void)
{
    
    struct sockaddr_in  destinationAddr;
    
    int sockfd;
    
    int socklen;
    size_t n;
    
    
    
    /*
     创建UDP数据包socket描述符
     */
    
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    
    if (sockfd<0) {
        printf("socket creating err \n");
        return;
    }
    
    socklen = sizeof(struct sockaddr_in);
    
    memset(&destinationAddr,0,socklen);
    
    /*
     设置目标主机IP 和端口号 这里我们使用广播方式
     */
    
    destinationAddr.sin_family = AF_INET;
    destinationAddr.sin_port = htons(8904);
    /*
     广播UDP与单播UDP的区别就是IP地址不同，广播使用广播地址255.255.255.255，将消息发送到在同一广播网络上的每个主机。值得强调的是：本地广播信息是不会被路由器转发
     */
    destinationAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    
    int opt = -1;
    int nb = 0;
    
    /*
     设置为广播方式
     */
    
    nb = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (char*)&opt, sizeof(opt));
    
    if (nb == -1) {
        printf("set socket error\n");
        return;
    }
    
    /*
     发消息給目标主机
     */
    printf("send to destination start \n");
    n = sendto(sockfd, "HELLO", strlen("HELLO"), 0, (struct sockaddr*)&destinationAddr, socklen);
    if (n==-1) {
        printf("send  udp pkt to err\n");
        return;
    }
    
    printf("send to end;send: %d\n",n);
    
}
/*
 linux多播编程步骤：
 1>建立一个socket;
 2>设置多播的参数，例如超时时间TTL，本地回环许可LOOP等
 3>加入多播组
 4>发送和接收数据
 5>从多播组离开
 */
void testUDPDuoBoServer(void)
{
    
    int sock;
    
    struct sockaddr_in local_addr;
    
    int err = -1;
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    if (sock == -1) {
        printf("sock error\n");
        return;
    }
    
    /*
     初始化地址
     */
    
    local_addr.sin_family = AF_INET;
    
    
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    local_addr.sin_port = htons(MCAST_PORT);
    
    /*
     TCP 服务器 绑定的ip 都是INADDR_ANY
     
     UDP 服务器 绑定的ip 也可以是INADDR_ANY
     */
    
    /*绑定socket*/
    
    err = bind(sock, (struct sockaddr*)&local_addr, sizeof(local_addr));
    
    if (err<0) {
        printf("bind error\n");
        return;
    }
    /*设置回环许可*/
    
    int loop = 1;
    
    err = setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop));
    
    if (err<0) {
        printf("set sock error");
        return;
    }
    
    struct ip_mreq mreq;/*加入多播组*/
    
    mreq.imr_multiaddr.s_addr = inet_addr(MCAST_ADDR);; //多播地址
    
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);//网络接口为默认
    
    err = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    if (err<0) {
        printf("set socket error\n");
        return;
    }
    
    int times = 0;
    
    socklen_t addr_len = 0;
    
    char buff[BUFF_SIZE];
    
    int n = 0;
    
    /*循环接受多播组的消息 5次后退出*/
    
    for (times = 0;times<5 ; times++) {
        addr_len = sizeof(local_addr);
        memset(buff, 0, BUFF_SIZE);
        n = recvfrom(sock , buff, BUFF_SIZE, 0, (struct sockaddr*)&local_addr, &addr_len);
        if (n==-1) {
            printf("recieve error\n");
            return;
        }
        printf("RECV message :%s\n",buff);
        
        sleep(MCAST_INTERVAL);
        
        //
    }
    
    /*
     退出广播组
     
     */
    
    err = setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
    
    close(sock);
    
    
    
    
}

void testUDPDuoBoClient(void)
{
    
    int sock;
    
    struct sockaddr_in mcast_addr;
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    if (sock == -1) {
        printf("create udp socket fail\n");
        return;
    }
    memset(&mcast_addr, 0, sizeof(mcast_addr));
    
    mcast_addr.sin_family= AF_INET;
    
    mcast_addr.sin_addr.s_addr = inet_addr(MCAST_ADDR);
    
    mcast_addr.sin_port = htons(MCAST_PORT);
    
    while (1) {
        //向局部多播地址发送多播内容
        
        int n = sendto(sock, MCAST_DATA, sizeof(MCAST_DATA), 0, &mcast_addr, sizeof(mcast_addr));
        
        if (n<0) {
            printf("send error\n");
            
            return;
        }else
        {
            printf("send message is going...\n");
            
        
            sleep(MCAST_INTERVAL);
            return;
        }
    }
    
    
    
    
    
    
    
    
    
    
    
}

/*
 
 　bind操作首先检查用户指定的端口是否可用，然后为socket的一些成员设置正确的值，并添加到哈希表myudp_hash中。然后，协议栈每次收到UDP数据，就会检查该数据报的源和目的地址，还有源和目的端口，在myudp_hash中找到匹配的socket，把该数据报放入该 socket的接收队列，以备用户读取。在这个程序中，bind操作把socket绑定到地址224.0.0.88:8888上， 该操作产生的直接结果就是，对于socket本身，下列值受影响：
 struct inet_sock{
 .rcv_saddr = 224.0.0.88;
 .saddr = 0.0.0.0;
 .sport = 8888;
 .daddr = 0.0.0.0;
 .dport = 0;
 }
 这五个数据表示，该套接字在发送数据包时，本地使用端口8888，本地可以使用任意一个网络设备接口，发往的目的地址不指定。在接收数据时，只接收发往IP地址224.0.0.88的端口为8888的数据。
 
 */
