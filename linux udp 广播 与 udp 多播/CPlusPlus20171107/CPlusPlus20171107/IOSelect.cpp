//
//  IOSelect.cpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/9.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#include "IOSelect.hpp"
/*
 字符设备驱动
 系统将设备分为3类：字符设备、块设备、网络设备
 字符设备：是指只能一个字节一个字节读写的设备，不能随机读取设备内存中的某一数据，读取数据需要按照先后数据。字符设备是面向流的设备，常见的字符设备有鼠标、键盘、串口、控制台和LED设备等。
 块设备：是指可以从设备的任意位置读取一定长度数据的设备。块设备包括硬盘、磁盘、U盘和SD卡等。
 　　每一个字符设备或块设备都在/dev目录下对应一个设备文件。linux用户程序通过设备文件（或称设备节点）来使用驱动程序操作字符设备和块设备。
 网络设备: 套接字
 
 */
IOSelect::IOSelect()
{
    int keyboard;
    
    int ret,i;
    
    char c;
    
    fd_set readfd;
    
    struct timeval timeout;
    /*
     open函数用来打开或创建一个文件，若成功返回文件描述符，否则返回-1。
     pathname是要打开或创建文件的名字。
     oflag参数是下列一个或多个常量执行按位或运算的结果杀
     O_RDONLY　　只读打开
     O_WRONLY　 只写打开
     O_RDWR 读写打开
     上面三个常量必须指定一个并且只能指定一个，下面一些常量则是可选的：
     O_APPEND　　将写入追加到文件的尾端
     O_CREAT 若文件不存在，则创建它。使用该选项时，需要第三个参数mode，用来指定新文件的访问权限位
     O_EXCL 如果同时指定了O_CREAT，而文件已经存在，则会出错
     O_TRUNC 如果此文件存在，而且为只写或读写模式成功打开，则将其长度截短为0
     O_NOCTTY 如果pathname指的是终端设备，则不将该设备分配作为此进程的控制终端
     O_NONBLOCK 如果pathname指的是一个FIFO文件、块设备文件或字符设备文件，则此选项将文件的本次打开操作和后续的I/O操作设置为非阻塞模式
     */
    keyboard=open("/dev/tty", O_RDONLY|O_NONBLOCK);
    /*
     如果keyboard 小于等于0就表示 打开失败
     */
   assert(keyboard>0);
    
    while (1) {
        timeout.tv_sec=1;
        timeout.tv_usec=0;
        __DARWIN_FD_ZERO(&readfd);
        
        __DARWIN_FD_SET(keyboard, &readfd);
        
        
        ret= select(keyboard+1, &readfd, NULL, NULL, &timeout);
        
        if (ret==-1) {
            //ret
            printf("select error");
        }else if(ret){
        
            if (__DARWIN_FD_ISSET(keyboard, &readfd)) {
                
                i=read(keyboard, &c, 1);
                
                if ('\n'==c)
                    continue;
                printf("hehethe input is %c\n",c);
                if ('q'==c)
                    break;
                
            }
        }else if (ret==0){
            printf("time out\n");
        }
    }

}

IOSelect::~IOSelect(){


}
