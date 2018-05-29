//
//  main.c
//  FIFOServer
//
//  Created by admindyn on 2018/5/29.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <stdio.h>
/*
 PIPE 管道 是两个有亲缘关系的进程
 
 父进程 与 子进程 间通信
 
 
 FIFO 是两个无亲缘关系的进程间通信
 因此 有FIFO 服务端  与 客户端 区分
 
 同时 FIFO 是一个单向数据流的 半双工的 因此
 
 
 
 */
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>


#define FIFO_CLT_FMT "/tmp/fifo_client_%lx"
#define FIFO_SERVER_PATH "/tmp/fifo_server"
#define MAX_BUFFER_SIZE 100
#define PATH_LEN 21

/*
 PATH_LEN
 "/tmp/fifo_client_4375"
 
 按照我们的设计标准 21 个字节
 */
void do_sig(int signo)
{
    
    if (signo == SIGCHLD) {
        while (waitpid(-1, NULL, WNOHANG)>0) {
            
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    
    /*
     int mkfifo(const char *pathname, mode_t mode);
     这里pathname是路径名,mode是sys/stat.h里面定义的创建文件的权限.
     */
    
    int ret;
    
    int fdr,fdw = 0;
    
 
   
    char clientPath[PATH_LEN] ={'\0'};
    char buf[MAX_BUFFER_SIZE]={'\0'};
    
  
   
    size_t nread = 0;
    
    /*
     创建FIFO 若存在则不算错误
     
     若想修改其属性 需要先打开得到的fd
     
     然后使用fcntl 来获取属性
     
     然后设置属性
     */
    
    /*第一参数为 文件路径 第二参数为 打开文件的权限模式 0666 0777*/
    /*
     先检查FIFO 文件是否存在 如果不存在 创建它*/
    if (access(FIFO_SERVER_PATH, F_OK)==-1) {
        if ((ret = mkfifo(FIFO_SERVER_PATH, 0666))==-1&&(errno != EEXIST)) {
        fprintf(stderr, "Could not create fifo %s\n", FIFO_SERVER_PATH);
            return -1;
        }
    }
    
    /*
     以只读阻塞的方式打开有名管道
     
     首先启动读管道程序：读管道进程在建立管道之后就开始循环地从管道里读出内容，如果没有数据可读，则一直阻塞到写管道进程向管道写入数据
     
     考虑 建立非阻塞的FIFO读写
     O_NONBLOCK
     
     非阻塞
     */
    
    /*
     a. 不使用O_NONBLOCK标志时，只读open要阻塞到某个其它进程为写而打开它为止
     
     b. 不使用O_NONBLOCK标志时，只写open要阻塞到某个其它进程为读而打开它为止
     c. 如果在open的时候指定O_NONBLOCK标志，当只读open时，没有进程为写而打开FIFO的话，会返回-1，只写open时，没有进程为读而打开FIFO的话也会返回-1表示失败
     */
    
    fdr = open(FIFO_SERVER_PATH, O_RDONLY|O_NONBLOCK);
    if (fdr == -1) {
        printf("open server fifo file error\n");
        return -1;
    }
    
    int loop = 1;
    int cpathOK = 0 ;
    while (loop) {
        memset(buf, 0, sizeof(buf));
        if (cpathOK == 0) {
            memset(clientPath, 0, sizeof(clientPath));
            
            /*读取第一条信息 read client fifo path from FIFO_PATH_SERVER
             注意 这里 启动server后 由于 管道还没有数据 这里 读到的就是0 继续往下执行
             
             所以注意代码容错
             
             
             */
            
            
            
            if ((nread = read(fdr, clientPath, PATH_LEN))>0) {
                if (strlen(clientPath)>0) {
                    cpathOK = 1;
                    printf("Read client Fifo path %s from FIFO \n",clientPath);
                    
                    sleep(2);
                }else
                {
                   continue;
                }
              
            }else
            {
                
                continue;
            }
        }
      
        /*
         如果对方客户端 关闭fifo 连接
         虽然文件fifo还在 但是这里获取权限 已经报错了
         
         还有 clientpath 获取数据这里 客户端 服务端 对于clientpath 读写字节一定要精确
         同样 如果 path_len 多于 本身字符串长度 这里也是权限报错
         */
        if (access(clientPath, F_OK) == -1) { // client fifo ok, but no permission
            printf("access fail\n");
            
            sleep(10);
            
            continue;
        }
        
        fdw = open(clientPath, O_WRONLY|O_NONBLOCK);
        
        if (fdw == -1) {
            printf("open client fifo file error\n");
            continue;
        }
        size_t n ;
        /* read from server FIFO anserwer to client */
        if ((n = read(fdr, buf, MAX_BUFFER_SIZE))>0) {
            
            printf("read server words:%s\n",buf);
            
            if (strncmp("quit", buf, 4)==0) {
                close(fdw);
                /*
                 只是close 管道 还必须通过unlink 删除
                 */
                unlink(FIFO_SERVER_PATH);
                break;
            }
            
            buf[n] = '\0';
            /*
             anserwer to client
             */
            write(fdw, buf, strlen(buf));
        }
        
    }
    
   
    
    exit(0);
  
    
    
    
    
    
    
    
    
    
    return 0;
}
