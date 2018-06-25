//
//  SelectNETIO.cpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/9.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#include "SelectNETIO.hpp"

#define DEFAULT_PORT 6666

SelectNETIO::SelectNETIO(){
    int serverfd,acceptfd;/*监听socket ：serverfd 数据传输 socket ： acceptfd*/
    
    struct sockaddr_in my_addr;/*本机地址信息*/
    struct sockaddr_in their_addr;/*客户地址信息*/
    
    unsigned int sin_size ,myport=6666,listnum=10;
    
    if ((serverfd=socket(AF_INET, SOCK_STREAM, 0))==-1) {
        perror("socket");
        return;
    }
    
    printf("socket error\n");
    
    my_addr.sin_family=AF_INET;
    my_addr.sin_port=htons(DEFAULT_PORT);
    my_addr.sin_addr.s_addr=INADDR_ANY;
    /*效果 类似 memset*/
    bzero(&(my_addr.sin_zero), 0);
    
    if (bind(serverfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr))) {
        perror("bind");
        return;
    }
    
    printf("bind ok\n");
    
    if (listen(serverfd, listnum)==-1) {
        perror("listen");
        return;
    }
    
    printf("listen ok\n");
    
    
    fd_set client_fdset;/*监听 文件描述符集合*/
    int maxsock; /*监听 文件描述符集合 中 最大的文件号*/
    
    struct timeval tv; /*超时返回时间*/
    
    int client_sockfd[5]; /*存放活动的 描述文件符*/
    
      /*效果 类似 memset*/
    bzero((void*)client_sockfd, sizeof(client_sockfd));
    
    int conn_amount = 0;
    
    maxsock =serverfd;
    
    char buffer[1024];
    
    int ret=0;
    
    while (1) {
        /*
         FD_ZERO(fd_set *fdset);将指定的文件描述符集清空，在对文件描述符集合进行设置前，必须对其进行初始化，如果不清空，由于在系统分配内存空间后，通常并不作清空处理，所以结果是不可知的。
         FD_SET(fd_set *fdset);用于在文件描述符集合中增加一个新的文件描述符。
         FD_CLR(fd_set *fdset);用于在文件描述符集合中删除一个文件描述符。
         FD_ISSET(int fd,fd_set *fdset);用于测试指定的文件描述符是否在该集合中。
         */
        /*初始化文件描述符集合*/
        
        __DARWIN_FD_ZERO(&client_fdset);
        /*加入服务器的描述符*/
        __DARWIN_FD_SET(serverfd, &client_fdset);
        /*设置超时时间*/
        
        tv.tv_sec=30;//30秒
        tv.tv_usec=0;
        
        /*
         把活动的句柄加入到文件描述符中
         */
        
        for (int i=0; i<5; ++i) {
            /*程序中listen中的参数设置的数 和这里循环次数一致*/
            
            
            if (client_sockfd[i]!=0) {
                __DARWIN_FD_SET(client_sockfd[i], &client_fdset);
            }
        }
        
        printf("put sockfd in fdset!\n");
        
        /*select 函数
         参数maxfd是需要监视的最大的文件描述符值+1；rdset,wrset,exset分别对应于需要检测的可读文件描述符的集合，可写文件描述符的集合及异常文件描述符的集合。struct timeval结构用于描述一段时间长度，如果在这个时间内，需要监视的描述符没有事件发生则函数返回，返回值为0。
         
         */
        
        ret = select(maxsock+1, &client_fdset, NULL, NULL, &tv);
        
        if (ret<0) {
            perror("select error\n");
            /*
             break 跳出当前循环体
             
             continue 跳过当前循环体continue后面的代码，继续执行下一个循环
             
             return 和循环没关系，就是跳出该函数
             */
            break;
        }else if(ret==0){
            printf("time out\n");
            continue;
        }
        
        /*轮询各个文件描述符*/
        
        for (int i=0; i<conn_amount; ++i) {
            /*FD_ISSET 检查client_sockfd是否可读写 >0是可读写*/
            
            if (__DARWIN_FD_ISSET(client_sockfd[i], &client_fdset)) {
                printf("start recv from client[%d]:\n",i);
                ret =recv(client_sockfd[i], buffer, 1024, 0);
                
                if (ret<0) {
                    printf("client[%d] close",i);
                    
                    close(client_sockfd[i]);
                    
                    __DARWIN_FD_CLR(client_sockfd[i], &client_fdset);
                    
                    client_sockfd[i]=0;
                }else{
                
                    printf("recv from client[%d]:%s\n",i,buffer);
                }
                
                
                
            }
        }
        
        /*
         检查 是否 有新的 连接 如果有  接受连接 加入到 client_sockfd中
         */
        
        

        
        if (__DARWIN_FD_ISSET(serverfd, &client_fdset)) {
            /*
             接受连接（循环一开始 已经把第一个监听 套接字 添加到描述符集合了）
             */
            
            struct sockaddr_in client_addr;
            size_t size = sizeof(struct sockaddr_in);
            
            int sock_client = accept(serverfd, (struct sockaddr*)(&client_addr), (unsigned int*)(&size));
            
            if (sock_client<0) {
                perror("accept error\n");
                continue;
            }
            /* 把 连接加入到 文件描述符集合*/
            
            
            if (conn_amount<5) {
                client_sockfd[conn_amount++]=sock_client;
                bzero(buffer, 1024);
                
                strcpy(buffer, "this is server! welcome!\n");
                
                send(sock_client, buffer, 1024, 0);
                
                printf("new connection client[%d] %s:%d",conn_amount,inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
                
                
                bzero(buffer, sizeof(buffer));
                
                ret=recv(sock_client, buffer, 1024, 0);
                
                if (ret<0) {
                    perror("recv error!\n");
                    close(serverfd);
                    return;
                }
                
                printf("recv:%s\n",buffer);
                
                if (sock_client>maxsock) {
                    maxsock=sock_client;
                }else{
                    printf("max connections!!!quit!!\n");
                    break;
                }
            }
            
        }
        
    }
    
    //////////
    
    for (int i=0; i<5; ++i) {
        if (client_sockfd[i]!=0) {
            close(client_sockfd[i]);
        }
    }
    
    close(serverfd);
    
    
}

SelectNETIO::~SelectNETIO()
{
    
    

}

