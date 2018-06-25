//
//  PollNETIO.cpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/9.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#include "PollNETIO.hpp"
#define IPADDRESS "127.0.0.1"
#define PORT 7777
#define MAXLINE 1024
#define LISTEND 5
#define OPEN_MAX 1000
#define INFTIM -1

void  handle_connection(struct pollfd* clientfds,int num)
{
    int i,n;
    /*
     处理 多个连接上的客户端 发来的包
     */
    char buf[MAXLINE];
    memset(buf, 0, MAXLINE);
    
    int readlen=0;
    printf("accept 7");
    for (i=1; i<=num; i++) {
        if (clientfds[i].fd<0) {
            continue;
        }
        printf("accept 8");
        /*测试客户端描述符是否准备好*/
        
        if (clientfds[i].revents&POLLIN) {
            
            /*接受客户端发来的消息*/
            printf("accept 9");
            readlen=read(clientfds[i].fd, buf, MAXLINE);
            
            
            if (readlen==0) {
                close(clientfds[i].fd);
                clientfds[1].fd=-1;
                continue;
            }
            printf("read msg is :");
            write(STDOUT_FILENO, buf, readlen);
            /*想客户端发送buf*/
            write(clientfds[i].fd, buf, readlen);
            
            
            
        }
    }

}

PollNETIO::PollNETIO(){


}

void PollNETIO::testServer()
{
    int listenfd= bind_and_listen();
    if (listenfd<0) {
        return;
    }
    do_poll(serverfd);
}

int PollNETIO::bind_and_listen()
{
    

    struct sockaddr_in my_addr;/*本机地址信息*/
    
    unsigned int sin_size;
    
    
    if ((serverfd=socket(AF_INET, SOCK_STREAM, 0))==-1) {
        perror("socket");
        return -1;
    }
    printf("socket ok\n");
    
    my_addr.sin_family=AF_INET;
    my_addr.sin_port=htons(PORT);
    my_addr.sin_addr.s_addr=INADDR_ANY;
    
    bzero(&(my_addr.sin_zero), 0);
    
    if (bind(serverfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr))==-1) {
        perror("bind");
        return -2;
    }
    printf("bind ok\n");
    if (listen(serverfd, LISTEND)==-1) {
        perror("listen");
        return -3;
    }
    printf("listen ok\n");
    return serverfd;
    
}

void PollNETIO::do_poll(int listenfd)
{
    int connfd,sockfd;
    struct sockaddr_in cliaddr;
    
    socklen_t cliaddrlen;
    
    struct pollfd clientfds[OPEN_MAX];
    
    int maxi;
    
    int i;
    
    int nready;
    
    
    /*
     添加监听描述符
     */
    clientfds[0].fd=listenfd;
    clientfds[0].events=POLLIN;
    
    
    /*初始化客户端连接描述符*/
    
    for (i=1; i<OPEN_MAX; i++) {
        clientfds[i].fd=-1;
       
        
        /*for循环结束*/
    }
     maxi = 0;
    /*for循环结束*/
    
        /*while循环处理
         这里需要注意 下面的 循环 都是从1 开始循环的  因为 之前的0 用来存储监听描述符了
         */
        while (1) {
            /*获取可用描述符的个数*/
             printf("accept 1");
            //监测event，一个对象，等待5000毫秒后超时,-1为无限等待
            nready=poll(clientfds, maxi+1, INFTIM);
            
            if (nready==-1) {
                printf("accept 1 error:");
                perror("poll error:");
                exit(1);
            }
             printf("accept 1 Ok");
          
            if(nready==0){
                printf("Time out!\n");
                continue;
            }
              /*测试监听描述符是否准备好 clientfds 索引为0*/
            if (clientfds[0].revents&POLLIN) {
                cliaddrlen = sizeof(cliaddr);
                printf("accept 2");
                /*接受新的连接*/
                if ((connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&cliaddrlen))==-1) {
                    if (errno==EINTR) {
                        continue;
                    }else{
                        perror("accept error");
                        exit(1);
                    }
                }
                printf("accept3 OK");
                ///connfd
                fprintf(stdout, "accept a new client:%s:%d\n",inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
                  printf("accept 4");
                /*将新的连接描述符添加到数组*/
                for (i=1; i<OPEN_MAX; i++) {
                    printf("accept 5");
                    if (clientfds[i].fd<0) {
                        printf("accept 6");
                        clientfds[i].fd=connfd;
                        break;
                    }
                }
                
                  /*上面检查是否将新的连接描述符添加到数组*/
                if (i==OPEN_MAX) {
                    fprintf(stderr, "too many clients\n");
                    exit(1);
                }
                
                /*
                 将新的描述符添加到读描述符集合中
                 */
                
                clientfds[i].events=POLLIN;
                /*
                 记录客户连接套接字的个数
                 */
                
                maxi=(i>maxi?i:maxi);
                if (--nready<=0) {
                    continue;
                }
                
                //处理客户连接
                handle_connection(clientfds, maxi);
                
            }
             /*while循环结束*/
        }
        /*while循环结束*/
        
   
}

PollNETIO::~PollNETIO()
{
    

}



