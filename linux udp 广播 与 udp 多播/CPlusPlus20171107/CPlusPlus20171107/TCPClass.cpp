//
//  TCPClass.cpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/8.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#include "define.h"
#include "TCPClass.hpp"


int  MyRecv(int iSock,char * pchBuf,size_t tCount){
    size_t tBytesRead=0;
    int iThisRead;
    while (tBytesRead<tCount) {
        do {
            iThisRead=read(iSock, pchBuf, tCount-tBytesRead);
        } while ((iThisRead<0)&&(errno==EINTR));
        /*
         上面 的 do while  当读取数据发生错误 并且 是由于连接发生终端引起的 就循环
         其他情况皆认为 正常 往下进行
         */
        /*
         假如  连接 未中断 但是 读依旧错误 小于0 直接 return 错误值
         */
        if (iThisRead<0) {
            return iThisRead;
        }else if (iThisRead==0){
            /*
             假如  连接 未中断 但是 读未 错误 但是等于0 直接 return 0
             因为 读取结束
             */
            return iThisRead;
        }
        /*
         假如  连接 未中断 但是 读未 错误 但是大于0
         因为 读取部分 数据  未完成读取 统计读取的
         tBytesRead
         */
        tBytesRead+=iThisRead;
        /*
         同时 由于读写未结束 偏移读的缓冲区指针
         */
        pchBuf+=iThisRead;
        
    }
    
    return iThisRead;
    
    

}

TCPClass::TCPClass()
{
    /*
     服务器 根据ip地址类型 socket类型 协议类型创建socket
     */
    if ((listenfd=socket(AF_INET, SOCK_STREAM, 0))==-1) {
        printf("create socket error:%s (errno:%d)\n",strerror(errno),errno);
        return ;
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(6666);
      /*以上是 建立套接字 服务端与客户端代码都一样*/
    /*下面是绑定套接字到指定的ip地址*/
    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr))==-1 ) {
        printf("bind socket error:%s(errno:%d)\n",strerror(errno),errno);
        
        return ;
    }
    /*监听这个绑定好的套接字 第一个 参数为套接字 第二个参数为 相应的socket可以排队的最大连接数*/
    if (listen(listenfd, 10)==-1) {
        printf("listen socket error%s(errno:%d)\n",strerror(errno),errno);
        
        return;
    }
    
    printf("====waiting for client,s request\n");
    
    if (waiting) {
        /*while循环中 持续接受包*/
        while (1) {
            /*
             在实际编程的时候，经常需要将sockaddr_in强制转换成sockaddr类型。
             */
            /*
             accept 第一个参数为服务器的描述套接字 第二个参数为返回客户端的协议地址 第三个参数为协议地址的长度
             */
            if ((connfd=accept(listenfd, (struct sockaddr*)NULL, NULL))==-1 ) {
                printf("listen socket error%s(errno:%d)\n",strerror(errno),errno);
                continue;
            }
            n = recv(connfd, buff, MAX_LINE, 0);
            
            
            buff[n]='\0';
            printf("recv mesg from client:%s\n",buff);
            
            close(connfd);
            
        }
        close(listenfd);

    }
    if (!fengZhuangBao) {
        
            /*
             下面的是测试 服务器端  提前知道 要传输过来的数据是 123456789
             并且 我们接受数据的缓冲区 明显可以放的下
             
             并且 为了打印 收到的字符串 在缓冲区第九个位置 添加字符串结束符 打印出字符串
             
             
             */
            /*
             在实际编程的时候，经常需要将sockaddr_in强制转换成sockaddr类型。
             */
            socklen_t address_len;
            /*
             accept 第一个参数为服务器的描述套接字 第二个参数为返回客户端的协议地址 第三个参数为协议地址的长度
             */
            if ((connfd=accept(listenfd, (struct sockaddr*)&their_addr, &address_len))==-1) {
                printf("accept socket error:%s,(errno:%d)",strerror(errno),errno);
            }
            char recvMsg[1000];

            ssize_t readLen=read(connfd, recvMsg, sizeof(recvMsg));
            
            if (readLen<0) {
                printf("read error:%s(errno:%d)",strerror(errno),errno);
                return;
            }
            
            recvMsg[9]='\0';
            
            printf("readLen:%d,recvMsg:%s\n",readLen,recvMsg);
            
            sleep(5);
            
            recvMsg[1]='9';
            
            ssize_t writeLen = write(connfd, recvMsg, sizeof(recvMsg));
            
            printf("writeLen:%d,sendMsg:%s",writeLen,recvMsg);
            
            
            
            if (writeLen<0) {
                printf("writeLen error:%s(errno:%d)\n",strerror(errno),errno);
                
                return;
            }
            
            close(connfd);
        
        
    }else{
        /*
         在实际编程的时候，经常需要将sockaddr_in强制转换成sockaddr类型。
         */
        socklen_t address_len;
        /*
         accept 第一个参数为服务器的描述套接字 第二个参数为返回客户端的协议地址 第三个参数为协议地址的长度
         */
        if ((connfd=accept(listenfd, (struct sockaddr*)&their_addr, &address_len))==-1) {
            printf("accept socket error:%s,(errno:%d)",strerror(errno),errno);
        }
          char recvMsg[1000];
        
        ssize_t readLen1=MyRecv(connfd, recvMsg, sizeof(int));
        
        if (readLen1<0) {
            printf("read failed\n");
            
            return;
        }
        int len = (int)ntohl(*(int*)recvMsg);
        printf("len:%d\n",len);
        
        readLen1=MyRecv(connfd, recvMsg, len);
        
        if (readLen1<0) {
            printf("read failed\n");
            
            return;
        }
        
        if (fengZhuangJieGouTi) {
            char* pBuff=recvMsg;
            
            Pkg RecvPkg;
            
            int iLen=0;
            
            memcpy(&RecvPkg.head.num, pBuff+iLen, sizeof(int));
            iLen+=sizeof(int);
            
            RecvPkg.head.num=ntohl(RecvPkg.head.num);
            
            
            
            //
            memcpy(&RecvPkg.head.index,pBuff+iLen, sizeof(int));
            
            iLen+=sizeof(int);
            
            RecvPkg.head.index=ntohl(RecvPkg.head.index);
            //
            
            memcpy(&RecvPkg.content.sex,pBuff+iLen, sizeof(char));
            
            iLen+=sizeof(char);
            
            //
            memcpy(&RecvPkg.content.score,pBuff+iLen, sizeof(int));
            
            iLen+=sizeof(int);
            RecvPkg.content.score=ntohl(RecvPkg.content.score);
            //
            
            memcpy(&RecvPkg.content.address,pBuff+iLen, sizeof(RecvPkg.content.address));
            
            iLen+=sizeof(RecvPkg.content.address);
            
            //
            memcpy(&RecvPkg.content.age,pBuff+iLen, sizeof(int));
            
            iLen+=sizeof(int);
            RecvPkg.content.age=ntohl(RecvPkg.content.age);
            //
            printf("RecvPkg.head.num:%d\n",RecvPkg.head.num);
            printf("RecvPkg.head.index:%d\n",RecvPkg.head.index);
            printf("RecvPkg.content.sex:%c\n",RecvPkg.content.sex);
            printf("RecvPkg.content.sore:%d\n",RecvPkg.content.score);
            printf("RecvPkg.content.address:%s\n",RecvPkg.content.address);
            printf("RecvPkg.content.age:%d\n",RecvPkg.content.age);
            close(connfd);
            /*上面 我们 设置 结构体的数据接收*/
        }
        if (fengZhuangBao) {
            if (!fengZhuangJieGouTi) {
                /*下面是普通字符串的数据接收*/
                
                
                recvMsg[len]='\0';
                printf("recvMsg:%s\n",recvMsg);
                
                close(connfd);
            }
          
        }
       
        /*上面 有一个封包的过程 服务器客户端 都不知道 要传输 与 接受 多大的数据 都是用户随意指定的 数据 因此 先 接受第一个包  会返回 要发送过来的数据的字节大小 然后我们按照这个字节大小
         循环获取数据 直到 结束数据收发为止
         
         */
        
      
        
        
       
    
    
    
    }
   
}



TCPClass::~TCPClass()
{

}
