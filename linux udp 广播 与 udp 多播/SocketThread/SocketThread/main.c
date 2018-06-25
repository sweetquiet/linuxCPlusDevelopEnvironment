//
//  main.c
//  SocketThread
//
//  Created by admindyn on 2018/6/25.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <sys/socket.h>
#include <arpa/inet.h>
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
#include <stdio.h>

int testServerThread(void);

int testClientThread(int argc,char* argv[]);

void* thread_run(void* arg)
{
    
    char buf[1024];
    int fd = (int)arg;
    
    printf("create a new thread...\n");
    
    while (1) {
        ssize_t _s = read(fd, buf, sizeof(buf));
        if (_s>0) {
            buf[_s-1] = '\0';
            printf("client mesg:%s\n",buf);
            char* mes = "server ok";
            /*
             这里应该传入9 个字节
             传入9 10 都没有问题
             传入小于9 客户端接受的信息就少一些字节 但是程序不报错
             */
            write(fd,mes , 9);
        }else if (_s == 0)
        {
            printf("client 主动断开了连接 \n");
            
            break;
        }else
        {
              printf("client  connect error1 \n");
            break;
        }
    }
    printf("client close -loopend \n");
    close(fd);
    
    pthread_exit(0);
    
}



int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
   
    
    
    
   // char* arr [3] ={"SocketThread","127.0.0.1","8080"};
    
   // testClientThread(3,arr);
    
    testServerThread();
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}



int testServerThread(void)
{
    printf("1、创建 socket；\n2、将socket 和 Server的IP、端口号进行绑定；\n3、设置为监听状态；\n4、每建立一个链接，就开启一个新的线程，在线程内部与对应的Client端进行通信\n");
    
    int sock = socket(AF_INET,SOCK_STREAM,0);
    
    if (sock<0) {
        perror("sock create error");
        return  -1;
    }
    
    struct sockaddr_in local;
    
    local.sin_family = AF_INET;
    local.sin_port = htons(8080);
    //local.sin_addr.s_addr = htonl(INADDR_ANY);
    
    local.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    //
    int opt = 1;
    printf("使用SO_REUSEADDR 解决socket服务端 timewait socket 资源不能尽快释放 端口被占用的问题\n");
   /*
    解决socket服务端 timewait socket 资源不能尽快释放 端口被占用的问题
    socket 服务端timewait 多 使用SO_REUSEADDR 使用setsockopt()设置socket描述符的
    */
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    if (bind(sock,(struct sockaddr*)&local,sizeof(local))<0) {
        perror("socket bind");
        
        close(sock);
        return 2;
    }
    
    if (listen(sock, 5)<0) {
        perror("socket listen");
        
        return 3;
    }
    
    printf("bind and listen success,wait accept..\n"
           );
    struct sockaddr_in client_sock;
    ssize_t len = sizeof(client_sock);
    
    while (1) {
        int fd_new = accept(sock, (struct sockaddr*)&client_sock, &len);
        
        if (fd_new<0) {
            perror("socket accept");
            
            close(sock);
            
            return 3;
        }
        
        
        pthread_t id;
        
        if (pthread_create(&id, NULL, thread_run, (void*)fd_new)<0) {
            perror("pthread_create");
            
            close(sock);
            
            return  4;
        }
        
        pthread_detach(id);
    }
    
    
    close(sock);
}

int testClientThread(int argc,char* argv[])
{
    
    if(argc !=3)
    {
        printf("Usage : server [IP] [PORT] \n");
        return 1;
    }
    
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0)
    {
        perror("scok");
        return -1;
    }
    
    struct sockaddr_in server_sock;
    server_sock.sin_family = AF_INET;
    server_sock.sin_port = htons(atoi(argv[2]));
    server_sock.sin_addr.s_addr = inet_addr(argv[1]);
    
    int ret = connect(sock,(struct sockaddr*)&server_sock,sizeof(server_sock));
    if(ret < 0)
    {
        perror("connect");
        close(sock);
        return 2;
    }
    printf("connect success...\n");
    char buf[1024];
    while(1)
    {
        printf("please enter :");
        fflush(stdout);
        ssize_t _s = read(0,buf,sizeof(buf));
        if(_s > 0)
        {
            buf[_s] ='\0';
        }
        else if(_s == 0)
        {
            
            break;
        }
        else
        {
            break;
        }
        write(sock,buf,strlen(buf));
        
        printf("please wait...\n");
        read(sock,buf,sizeof(buf));
        printf("server # :%s",buf);
    }
    return 0;
    
    
}
