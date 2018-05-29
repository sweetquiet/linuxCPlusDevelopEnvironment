//
//  main.c
//  CPthread
//
//  Created by admindyn on 2018/5/29.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5 //线程数
int sum = 0; //定义全局变量，让所有线程同时写，这样就需要锁机制
pthread_mutex_t sum_mutex; //互斥锁
void* say_hello(void* args);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    pthread_t tids[NUM_THREADS];
    pthread_attr_t attr; //线程属性结构体，创建线程时加入的参数
    pthread_attr_init( &attr ); //初始化
    pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );
    /*是设置你想要指定线程属性参数，这个参数表明这个线程是可以join连接的，join功能表示主程序可以等线程结束后再去做某事，实现
                                                                    
    */
    pthread_mutex_init( &sum_mutex, NULL ); //对锁进行初始化
    for (int i =0; i<NUM_THREADS; ++i) {
        char content[100] = {'\0'};
        
        snprintf(content, 100, "%s%d \n","testThread",i);
        /*
         第一参数 线程ID
         第二参数 线程配置属性
         第三参数 线程调用的主函数
         第四参数 线程调用主函数需要的参数
         */
        int ret = pthread_create(&tids[i], &attr, say_hello, content);
        
        if (ret!=0) {
            printf("pthread_create error \n");
        }
        
        
        
    }
    
    /*
     主线程 不直接退出 要等待 子线程都运行完了 才能退出
     
     如果不调用这句 主线程直接退出 不等待子线程完成 那还有什么意义
     */
    
    pthread_attr_destroy( &attr ); //释放内存
    
    for (int i=0; i<20; i++) {
        printf("主线程任务 %d \n",i);
        sleep(2);
    }

    
    /*等待线程结束*/
      void *status;
     for (int i =0; i<NUM_THREADS; ++i)
     {
         /*
          如果没有pthread_join主线程会很快结束从而使整个进程结束，从而使创建的线程没有机会开始执行就结束了。加入pthread_join后，主线程会一直等待直到等待的线程结束自己才结束，使创建的线程有机会执行。
          */
    pthread_join(tids[i],&status);
         
         
     }
    
    
    printf("主线程2\n");
    
    
    
    
    
    return 0;
}
void* say_hello(void* args)
{
    printf("子线程 mes:%s \n",(char*)args);
    pthread_mutex_lock(&sum_mutex);
    printf("before sum in thread %s \n",args);
    sum++;
    printf("after sum in thread %s \n",args);
    sleep(3);
    
    printf("sum:%d\n",sum);
    
    pthread_mutex_unlock(&sum_mutex);
    
    pthread_exit(0);
    
    
    return NULL;
   
}
