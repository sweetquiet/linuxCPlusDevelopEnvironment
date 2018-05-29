//
//  main.c
//  FIFOClient
//
//  Created by admindyn on 2018/5/29.
//  Copyright © 2018年 admindyn. All rights reserved.
//

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
    char buf_path[PATH_LEN]={'\0'};
    char messageContent[MAX_BUFFER_SIZE]  = "we are fifo client message ";
    char quitMes[4] = "quit";
    char buf[MAX_BUFFER_SIZE]  = {'\0'};
  

    snprintf(clientPath, PATH_LEN, FIFO_CLT_FMT, (long)getpid());
    snprintf(buf_path, PATH_LEN, "%s\n", clientPath);
    
    /*
     先检查FIFO 文件是否存在 如果不存在 创建它*/
    if (access(clientPath, F_OK)==-1) {
        if ((ret = mkfifo(clientPath, 0777))==-1&&(errno != EEXIST)) {
            fprintf(stderr, "Could not create fifo %s", clientPath);
            return -1;
        }
    }
    /*
    1、 client open server for write
     */
    
    if ((fdw = open(FIFO_SERVER_PATH, O_WRONLY|O_NONBLOCK))<0) {
        printf("open server fifo write fail\n");
    }
    int l = 1;
    while (l) {
        if (write(fdw, buf_path, PATH_LEN)!=PATH_LEN) {
            printf("只写client的fifo 路径 给服务器  fail\n");
            continue;
        }else
        {
            printf("只写client的fifo 路径 给服务器  success\n");
        }
        if (write(fdw, messageContent, MAX_BUFFER_SIZE)<0) {
            printf("发送消息给服务器失败\n");
              continue;
        }else
        {
            printf("发送消息给服务器成功\n");
        }
        l = 0;
    }
    
   
    
   
    
    
    /*
     2、 client open client wait message answer
     */
    

        
        if ((fdr = open(clientPath, O_RDONLY|O_NONBLOCK))<0) {
            printf("open client answer path fail\n");
         
        }
    int loop = 1;
    while (loop) {
        size_t n = 0;
        if ((n=read(fdr,buf , MAX_BUFFER_SIZE))>0) {
           
            if (strlen(buf)>0) {
                buf[n] = '\0';
                loop = 0;
                printf("server answer:%s \n",buf);
                if (write(fdw,quitMes,4)<0) {
                    printf("发送关闭消息给服务器失败\n");
                    continue;
                }else
                {
                    printf("发送关闭消息给服务器成功\n");
                }
            }else
            {
                printf("server no answering\n");
                
                
            }
            
            
        }
    }
    
    close(fdr);
    unlink(clientPath);
  
    
    
   
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}
