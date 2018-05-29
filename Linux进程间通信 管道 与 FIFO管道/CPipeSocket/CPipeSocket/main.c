//
//  main.c
//  CPipeSocket
//
//  Created by admindyn on 2018/5/29.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    /* 当对端read插口关闭时，write()会触发SIGPIPE信号； 如果屏蔽掉，
     则会返回错误EPIPE，被错误判断捕捉；如果不屏蔽，则默认导致进
     程退出 */
    signal(SIGPIPE, SIG_IGN);
    
    size_t result = -1;
    
    int fd[2];
    size_t nbytes;
    
    pid_t pid;
    
    
    char string[] = "hello world ,my pipe!";
    
    char readbuffer[100];
    
    int* write_fd = &fd[1];
    int* read_fd = &fd[0];
    
    result = pipe(fd);
    /*
     filedes[0]用于读出数据，读取时必须关闭写入端，即close(filedes[1]);
     
     filedes[1]用于写入数据，写入时必须关闭读取端，即close(filedes[0])。
     
     管道利用fork机制建立 最开始的时候 还没有执行到fork
     就一个进程 该进程也是有管道的 只是管道的 读 与 写 都指向进程自己
     
     当fork执行后 复制了一个新进程 该新进程也复制了父进程的管道 也是指向自己
     
     那么 子父进程需要通过管道 通信 时 各自关闭 一个输入连接 一个输出连接
     
     这样子父进程的管道通信就建立了
     */
    
    if (-1 == result) {
        printf("fail to create pipe\n");
        
        return -1;
    }
    /*
     fork（）函数通过系统调用创建一个与原来进程几乎完全相同的进程，也就是两个进程可以做完全相同的事，但如果初始参数或者传入的变量不同，两个进程也可以做不同的事。
     一个进程调用fork（）函数后，系统先给新的进程分配资源，例如存储数据和代码的空间。然后把原来的进程的所有值都复制到新的新进程中，只有少数值与原来的进程的值不同。相当于克隆了一个自己
     */
    int count = 0;
    printf("cache 缓冲区");
    pid = fork();
    /*
     管道 是基于fork的
     
     fork 两个进程 进程的环境一样 都copy存在了环境一样
     的pipe管道
     
     */
    
  
    
    if (-1 == pid) {
        printf("fail to fork\n");
        
        return -1;
    }
    
    if (0==pid) {
        
        
        /*
         子进程 关闭自己的 管道读取 文件描述符
         */
        close(*read_fd);
        printf(" PID %d 引用一位网友的话来解释fpid的值为什么在父子进程中不同。“其实就相当于链表，进程形成了链表，父进程的fpid(p 意味point)指向子进程的进程id, 因为子进程没有子进程，所以其fpid为0. \n",pid);
        
        printf("子进程:the child process pid is :ppid %d pid%d fpid %d \n",getppid(),getpid(),pid);
        printf("在子进程中，fork函数返回0 id:%d \n",pid);
        /*
         管道的读写 就是内存复制 strcopy 读写
         */
        int stop = 0;
        while (stop==0) {
            /*
             子进程 负责 向管道写入
             */
            count++;
            char* str;
            if (count>10) {
                stop=1;
                char strC[]="--stop!";
                str=strC;
            }else
            {
                str = string;
            }
            
            result = write(*write_fd, str, strlen(str));
            
            printf("子进程:the parent process write %zu bytes data :%s \n",result,str);
          
        }
        
        printf("子进程:count %d\n",count);
     
    }else{
        /*
         主进程 关闭自己的 管道写入 文件描述符
         */
        close(*write_fd);
        printf(" PID %d 引用一位网友的话来解释fpid的值为什么在父子进程中不同。“其实就相当于链表，进程形成了链表，父进程的fpid(p 意味point)指向子进程的进程id, 因为子进程没有子进程，所以其fpid为0. \n",pid);
        
        printf("主进程:the parent process pid is :ppid %d pid%d fpid %d \n",getppid(),getpid(),pid);
        
        printf("每次fork 会累加(父进程同级的进程数加1)主进程 在父进程中，fork返回新创建子进程的进程ID id:%d \n",pid);
        /*
         管道的读写 就是内存复制 strcopy 读写
         */
        int stop = 0;
        while (stop == 0) {
            /*
             主进程 负责 从管道读取
             */
           
            nbytes = read(*read_fd, readbuffer, sizeof(readbuffer));
            
            printf("主进程:the parent process receive %zu bytes data :%s \n",nbytes,readbuffer);
            if (nbytes == 0) {
                stop = 1;
            }
            count++;
        }
      /*
       信号是进程间唯一的异步通信机制
       
       SIGPIPE 向无人读到的管道写 触发信号
       
       SIGUSR2 用户定义信号
       
       SIGKILL 杀死进程信号 不能被捕获或忽略
       
       SIGABRT 程序调用abort 时 触发
       
       SIGQUIT 从键盘来的中断信号ctrl_c进程时触发
       
       SIGINT 中断 用户键入CTRL_C时触发发送
       
       SIGHUP 在控制终端上发生的结束信号
       
       SIGTERM Kill 发出的软件结束信号  触发
       */
      
        printf("主进程统计结果:count %d\n",count);
    }
    
    printf("主进程统计结果:count %d\n",count);
    
    
    printf("创建新进程成功后，系统中出现两个基本完全相同的进程，这两个进程执行没有固定的先后顺序，哪个进程先执行要看系统的进程调度策略。每个进程都有一个独特（互不相同）的进程标识符（process ID），可以通过getpid（）函数获得，还有一个记录父进程pid的变量，可以通过getppid（）函数获得变量的值。\n");
    
    
    
    
    
    
    
    
    return 0;
}
