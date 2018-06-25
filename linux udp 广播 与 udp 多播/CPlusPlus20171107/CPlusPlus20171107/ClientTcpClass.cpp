//
//  ClientTcpClass.cpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/8.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#include "define.h"
#include "ClientTcpClass.hpp"

int  mySend(int isock,char * pchBuf,size_t tlen){
    
    int iThisSend;
    
    unsigned int iSended=0;
    
    if (tlen==0) {
        return 0;
    }
    
    while (iSended<tlen) {
        do{
            iThisSend=send(isock, pchBuf, tlen-iSended, 0);
        }while ((iThisSend<0)&&(errno==EINTR));
        if (iThisSend<0) {
            return iSended;
        }
        iSended +=iThisSend;
        pchBuf +=iThisSend;
    }
    
    return tlen;

}


ClientTcpClass::ClientTcpClass(){

    this->serverIP="127.0.0.1";
    /*
     客户端 根据ip地址类型 socket类型 协议类型创建socket 0表示 自动根据 前面的socket类型选择使用的协议
     */
    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0))<0) {
          printf("create socket error:%s (errno:%d)\n",strerror(errno),errno);
        return;
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    
    servaddr.sin_family=AF_INET;
    /*服务端 需要指明服务器的ip地址*/
//    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(6666);
    /*以上是 建立套接字 服务端与客户端代码都一样*/
   
    /*客户端 也需要指明服务器的ip地址 在这里*/
    
     /*客户端比服务端多了 在这里绑定套接字 （这个函数是将字符串转换到网络地址）AF_INET 一般的IP地址 AF_INET6 IPV6地址*/
    if (inet_pton(AF_INET,serverIP,&servaddr.sin_addr)<=0) {
        printf("inet_pton error for:%s\n",serverIP);
        return ;
    }
    /*服务端 是 建立套接字  绑定套接字 监听套接字 循环接受*/
     /*服务端 是 建立套接字  绑定套接字 连接套接字 发送数据包*/
    /*
     sockfd=socket(AF_INET, SOCK_STREAM,0)
     在调用socket()函数时生成一个socket文件描符，此时并未分配ip和端口，对于客户端来说在connect()以后
     才固定ip和端口，此时可以调用getsockname()来获得客户端自己的ip和端口号。
     而服务器端调用socket()时一样，当服务器调用bind（）时绑定了服务器要监听的ip和端口号，之后对这对ip和
     端口进行监听listen（），当有客户端请求连接(connect())时,服务器调用accept()接受客户端连接请求，就在
     此时又分配了ip和端口用于服务器与客户端进行通信，每调用一次accept（）就分配一对ip和端口用于通信，而
     之前的监听描述符（用的ip和端口）一直用于监听使用，服务器可以调用getpeername（）获得客户端的ip和
     端口号
     
     以上是在做客户端与客户端直接通信时所了解到的
     */
    /*
     在实际编程的时候，经常需要将sockaddr_in强制转换成sockaddr类型。
     */
    /*
     connect 第一个参数为 套接字 第二个参数为服务器的socket地址 第三个为socket地址长度
     */
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0) {
        printf("connect error:%s(errno:%d)\n",strerror(errno),errno);
        return;
    }
     memset(&addrMyself,0,sizeof(addrMyself));
    /*
     在实际编程的时候，经常需要将sockaddr_in强制转换成sockaddr类型。
     */
    socklen_t  len=sizeof(addrMyself);
    int ret=getpeername(sockfd, (struct sockaddr*)&addrMyself, &len);
    if (ret==0) {
        printf("获取本机IP地址成功\n");
    }
    
    
    /*
     建立套接字  绑定套接字 连接套接字 后 我们设置套接字配置
     
     */
    struct timeval stTimeValStruct;
    stTimeValStruct.tv_sec=2;
    stTimeValStruct.tv_usec=0;
    /*设置 socket的 发送和 接受 数据的超时时间*/
    if (setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &stTimeValStruct, sizeof(stTimeValStruct))) {
        printf("setsockopt error:%s(errno:%d)\n",strerror(errno),errno);
        return;
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &stTimeValStruct, sizeof(stTimeValStruct))) {
        printf("setsockopt error:%s(errno:%d)\n",strerror(errno),errno);
        return;
    }
    /*下面是发送数据包*/
    printf("send msg to server:\n");
    if (readAndWrite) {
        
        /*
         下面是 测试 直接发送 简单数据 不封包
         */
        /*write函数 将 要发送的内容 写入套接字 成功时返回写的字节数 ，失败时返回-1 返回值大于0 表示写了部分 或 全部数据*/
        /*第一个 参数 套接字 第二个参数 缓冲区 第三个缓冲区长度*/
        ssize_t writeLen;
        char sendMsg[10]={'0','1','2','3','4','5','6','7','8','\0'};
        writeLen=write(sockfd, sendMsg, sizeof(sendMsg));
        
        
        if (writeLen<0) {
            printf("write error:%s(errno:%d)\n",strerror(errno),errno);
            close(sockfd);
            return;
        }else{
            
            printf("write success,writelen:%d,sendMsg:%s\n",writeLen,sendMsg);
        }
        
        char readMsg[10]={0};
        
        int readLen = read(sockfd, readMsg, sizeof(readMsg));
        
        if (readLen<0) {
            printf("read error:%s(errno:%d)\n",strerror(errno),errno);
            close(sockfd);
            return;
        }else{
            readMsg[9]='\0';
            
            printf("read success,readlen :%d,readmsg:%s",readLen,readMsg);
        }
        
        close(sockfd);

    }
#pragma mark-数据包 封装 - socket 建立 -与 lora串口通信一个道理
    if (!fengZhuangBao) {
        fgets(sendline, 4096, stdin);
        
        if (send(sockfd, sendline, strlen(sendline), 0)<0) {
            printf("send msg error:%s(errno:%d)\n",strerror(errno),errno);
            return;
        }
        
        close(sockfd);
    }else{
        if (fengZhuangJieGouTi) {
            Pkg mypkg;
            
            mypkg.head.num=1;
            mypkg.head.index=10001;
            mypkg.content.sex='m';
            mypkg.content.score=10;
            char* temp="guangzhou and shanghai";
            /*这里为什么要这样 复制 是为了担心 用户传入的字符串大小 超过 我们预定的内存大小吧*/
            strncpy(mypkg.content.address, temp, sizeof(mypkg.content.address));
            
            mypkg.content.age=18;
            int structLen =sizeof(mypkg);
            
            printf("结构体structLen:%d\n",structLen);
            int iStructLen=0;
            char * pBuff2 = new char[1000];
            *(int*)(pBuff2+iStructLen)=htonl(structLen);
            iStructLen+=sizeof(int);
            //
            *(int*)(pBuff2+iStructLen)=htonl(mypkg.head.num);
            iStructLen+=sizeof(int);
            //
            *(int*)(pBuff2+iStructLen)=htonl(mypkg.head.index);
            iStructLen+=sizeof(int);
            //
            memcpy(pBuff2+iStructLen, &mypkg.content.sex, sizeof(char));
            iStructLen+=sizeof(char);
            //
            *(int*)(pBuff2+iStructLen)=htonl(mypkg.content.score);
            iStructLen+=sizeof(int);
            //
            memcpy(pBuff2+iStructLen, mypkg.content.address, sizeof(mypkg.content.address));
            
            iStructLen+=sizeof(mypkg.content.address);
            
            //
            *(int*)(pBuff2+iStructLen)=htonl(mypkg.content.age);
            iStructLen+=sizeof(int);
            
            int writeStructLen=mySend(sockfd, pBuff2, iStructLen);
            
            if (writeStructLen<0) {
                printf("write failed\n");
                close(sockfd);
            }else{
                printf("write success,writeLen:%d,iStructLen:%d,pbuff2:%s\n",writeStructLen,iStructLen,pBuff2);
            }
            close(sockfd);

        }
        
        if (fengZhuangBao) {
            if (!fengZhuangJieGouTi) {
                ssize_t writeLen;
                char sendMsg[10]={'0','1','2','3','4','5','6','7','8','\0'};
                
                int tLen = strlen(sendMsg);
                int iLen=0;
                
                char * pBuff = new char[100];
                
                *(int*)(pBuff+iLen)=htonl(tLen);
                
                iLen+=sizeof(int);
                /*内存拷贝函数 从源src所指的内存地址的起始位置开始拷贝n个字节到目标地址dest所指的内存地址的起始位置中*/
                memcpy(pBuff+iLen, sendMsg, tLen);
                
                iLen+=tLen;
                /*封包  将 要发送的数据 封包到 pBuff 实际我们发送的数据包 是 pBuff*/
                
                writeLen=mySend(sockfd, pBuff, iLen);
                /*
                 上面的是 封包 收发数据
                 */
            }
        }
       
    
    }
    
}


ClientTcpClass::~ClientTcpClass(){

}
