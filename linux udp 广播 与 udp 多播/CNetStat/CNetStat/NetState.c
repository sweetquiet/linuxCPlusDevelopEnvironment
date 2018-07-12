//
//  NetState.c
//  CNetStat
//
//  Created by admindyn on 2018/7/11.
//  Copyright © 2018年 admindyn. All rights reserved.
//

/*
 ifconfig 命令解析
 在Linux系统中，ifconfig命令是通过ioctl接口与内核通信
 
 当系统管理员输入如下命令来改变接口eth0的MTU大小：
 
 ifconfig eth0 mtu 1250
 
 ifconfig命令首先打开一个socket，然后通过系统管理员输入的参数初始化一个数据结构，并通过ioctl调用将数据传送到内核。SIOCSIFMTU是命令标识符。
 
 struct ifreq data;
 fd = socket(PF_INET, SOCK_DGRAM, 0);
 < ... initialize "data" ...>
 err = ioctl(fd, SIOCSIFMTU, &data);
 
 
 
 */


#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/types.h>
#include <stdio.h>

#ifdef __APPLE__
//苹果操作系统!
#include <sys/fcntl.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>


#include <arpa/inet.h>
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


#include "NetState.h"

/*
 一些宏定义 意义
 
FIOCLEX://对文件设置专用标志，通知内核自动关闭打开的文件
FIONCLEX://与FIOCLEX标志相反，清除专用标志

FIONBIO://将文件操作设置成阻塞/非阻塞
 
FIOASYNC:// 将文件操作设置成同步/异步IO
 
S_ISLNK(m)     (((m) & S_IFMT) == S_IFLNK) //符号连接文件
S_ISREG(m)     (((m) & S_IFMT) == S_IFREG) //普通文件
S_ISDIR(m)      (((m) & S_IFMT) == S_IFDIR)   //目录文件
S_ISCHR(m)     (((m) & S_IFMT) == S_IFCHR) //字符设备文件
S_ISBLK(m)     (((m) & S_IFMT) == S_IFBLK)   //块设备文件
S_ISFIFO(m)    (((m) & S_IFMT) == S_IFIFO)   //管道文件
S_ISSOCK(m)   (((m) & S_IFMT) == S_IFSOCK)       //socket套接字文件

 补充一下基础知识,一个套接字接口在逻辑上有三个要素:网域,类型和规程(协议).
 网域：表明套接字接口用于哪一中网络或这说哪一族网络规程.就是我们通常说的地址族(family),常见的有AF_UNIX/AF_INET/AF_X25/AF_IPX等待.
 类型：表明通讯中所遵循的模式,主要有两种模式:”有连接”和”无连接”,对应到以太网就是SOCK_STREAM和SOCK_DGRAM两种.
 规程：具体的网络协议.通常,网域和类型基本就能够确定使用的规程了.
 */

/*
 网络socket 开发中设置socket 配置项
 */
void testSocketOpt()
{
    /*
     linux 网络socket 的 阻赛与非阻塞模式方式的开启
     
     第一种 使用 int socket(int domain, int type, int protocol);
     在type的参数中设置SOCK_NONBLOCK标志即可，
     linux平台上可以在利用socket()函数创建socket时指定创建的socket是异步的
     
     int s = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
     
     第二种 使用fcntl函数
     fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL, 0) | O_NONBLOCK);
     
     第三种 使用ioctl函数
     ioctl(sockfd, FIONBIO, 1); //1:非阻塞 0:阻塞
     
     
     linux下如果调用fcntl()设置socket为非阻塞模式，不仅要设置O_NONBLOCK模式，还需要在接收和发送数据时，需要使用MSG_DONTWAIT标志，即在recv，recvfrom和send，sendto数据时，将flag设置为MSG_DONTWAIT。是否有要进行这种双重设定的必要，笔者觉得没有这个必要。因为linux man手册上recv()函数的说明中关于MSG_DONTWAIT说明如下：
     
     Enables nonblocking operation; if the operation would block, the call fails with the error EAGAIN or EWOULDBLOCK (this can also be enabled using the O_NONBLOCK flag  with the F_SETFL fcntl(2)).
     
     通过这段话我觉得要么通过设置recv()函数的flags标识位为MSG_DONTWAIT，要么通过fcntl()函数设置O_NONBLOCK标识，而不是要同时设定。

     */
  
    /*
     函数 int    setsockopt(int, int, int, const void *, socklen_t);
     的使用
     
     int flag = 1;
     setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
     第一参数 标识一个套接口的描述字
     第二参数 选项定义的层次；目前仅支持SOL_SOCKET和IPPROTO_TCP层次。
     第三参数 需设置的选项
     第四参数 指针，指向存放选项值的缓冲区
     第五参数 optval缓冲区的长度
     */
    /*
     　1.设置调用closesocket()后,仍可继续重用该socket。调用closesocket()一般不会立即关闭socket，而经历TIME_WAIT的过程。
     　　BOOL bReuseaddr = TRUE;
     　　setsockopt( s, SOL_SOCKET, SO_REUSEADDR, ( const char* )&bReuseaddr, sizeof( BOOL ) );
     　　2. 如果要已经处于连接状态的soket在调用closesocket()后强制关闭，不经历TIME_WAIT的过程：
     　　BOOL bDontLinger = FALSE;
     　　setsockopt( s, SOL_SOCKET, SO_DONTLINGER, ( const char* )&bDontLinger, sizeof( BOOL ) );
     　　3.在send(),recv()过程中有时由于网络状况等原因，收发不能预期进行,可以设置收发时限：
     　　int nNetTimeout = 1000; //1秒
     　　//发送时限
     　　setsockopt( socket, SOL_S0CKET, SO_SNDTIMEO, ( char * )&nNetTimeout, sizeof( int ) );
     　　//接收时限
     　　setsockopt( socket, SOL_S0CKET, SO_RCVTIMEO, ( char * )&nNetTimeout, sizeof( int ) );
     　　4.在send()的时候，返回的是实际发送出去的字节(同步)或发送到socket缓冲区的字节(异步)；系统默认的状态发送和接收一次为8688字节(约
     　　为8.5K)；在实际的过程中如果发送或是接收的数据量比较大，可以设置socket缓冲区，避免send(),recv()不断的循环收发：
     　　// 接收缓冲区
     　　int nRecvBuf = 32 * 1024; //设置为32K
     　　setsockopt( s, SOL_SOCKET, SO_RCVBUF, ( const char* )&nRecvBuf, sizeof( int ) );
     　　//发送缓冲区
     　　int nSendBuf = 32*1024; //设置为32K
     　　setsockopt( s, SOL_SOCKET, SO_SNDBUF, ( const char* )&nSendBuf, sizeof( int ) );
     　　5.在发送数据的时，不执行由系统缓冲区到socket缓冲区的拷贝，以提高程序的性能：
     　　int nZero = 0;
     　　setsockopt( socket, SOL_S0CKET, SO_SNDBUF, ( char * )&nZero, sizeof( nZero ) );
     　　6.在接收数据时，不执行将socket缓冲区的内容拷贝到系统缓冲区：
     　　int nZero = 0;
     　　setsockopt( s, SOL_S0CKET, SO_RCVBUF, ( char * )&nZero, sizeof( int ) );
     　　7.一般在发送UDP数据报的时候，希望该socket发送的数据具有广播特性：
     　　BOOL bBroadcast = TRUE;
     　　setsockopt( s, SOL_SOCKET, SO_BROADCAST, ( const char* )&bBroadcast, sizeof( BOOL ) );
     　　8.在client连接服务器过程中，如果处于非阻塞模式下的socket在connect()的过程中可以设置connect()延时,直到accpet()被调用(此设置只
     　　有在非阻塞的过程中有显著的作用，在阻塞的函数调用中作用不大)
     　　BOOL bConditionalAccept = TRUE;
     　　setsockopt( s, SOL_SOCKET, SO_CONDITIONAL_ACCEPT, ( const char* )&bConditionalAccept, sizeof( BOOL ) );
     　　9.如果在发送数据的过程中send()没有完成，还有数据没发送，而调用了closesocket(),以前一般采取的措施是shutdown(s,SD_BOTH),但是数
     　　据将会丢失。
     　　某些具体程序要求待未发送完的数据发送出去后再关闭socket，可通过设置让程序满足要求：
     　　struct linger {
     　　u_short l_onoff;
     　　u_short l_linger;
     　　};
     　　linger m_sLinger;
     　　m_sLinger.l_onoff = 1; //在调用closesocket()时还有数据未发送完，允许等待
     　　// 若m_sLinger.l_onoff=0;则调用closesocket()后强制关闭
     　　m_sLinger.l_linger = 5; //设置等待时间为5秒
     　　setsockopt( s, SOL_SOCKET, SO_LINGER, ( const char* )&m_sLinger, sizeof( linger ) );
     */
    
}
/*
 当前一些宽带计费网关、防火墙系统均利用Ioctl与内核良好的通信互动特点支持用户对基于内核模块的软件系统的控制
 */
/*
 ioctl这个名称上看,它是设备驱动程序中对设备的I/O通道进行管理的函数。所谓对I/O通道进行管理，就是对设备的一些特性进行控制，例如串口的传输波特率、马达的转速等等, 但实际上ioctl所处理的对象并不限制是真正的I/O设备
 */
/*
 ioctl函数是文件结构中的一个属性分量，就是说如果驱动程序提供了对ioctl的支持，用户就可以在用户程序中使用ioctl函数控制设备的I/O通道或其它一些自己想要控制且设备支持的功能。
 */
int info_list(int all)
{
    
    int len;
    char *ifreq_pointer;
    len = 10 * sizeof(struct ifreq);
    ifreq_pointer = (char *) malloc(len);
   
    struct ifconf get_info;
    get_info.ifc_len = len;
    get_info.ifc_ifcu.ifcu_buf = ifreq_pointer;
    int sockfd;
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
   
    /*
     ioctl
     第一参数  是用户程序打开设备时使用open函数返回的文件描述符
     
     第二参数 是用户程序对设备的控制命令
     
     第三参数 是对应第二参数接收对应命令返回的数据结构的结构指针
     
     
     */
    
    
#pragma mark 命令 SIOCGIFCONF 获取所有网络硬件网卡设备接口的清单 对应返回的数据结构 struct ifconf
    
    
    ioctl(sockfd, SIOCGIFCONF, &get_info);
    
    int count;
    
    count = get_info.ifc_len / sizeof(struct ifreq);
    
    struct sockaddr_in *return_sockaddr;
    
    struct ifreq *result = (struct ifreq *) ifreq_pointer;
    
    
    printf("dev: %s\n",result->ifr_name);
    
 
    
    int i = 0;
    
    if (all == 1)
    {
        for (i=0; i < count; i++)
        {
            printf("%s\n", result->ifr_name);
            get_ipaddr(result->ifr_name);
            get_mac(result->ifr_name);
            get_netmask(result->ifr_name);
            get_broadcast(result->ifr_name);
        }
              
    } else
    {
        struct ifreq tmp;
        
        int s;
        
        if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
        {
        perror("Socket");
        exit(-1);
        }
        
        for (i=0; i < count; i++)
            {
                size_t a = strlen(result->ifr_name);
                
                if (a==0) {
                    
                    result = (struct ifreq *)ifreq_pointer+sizeof(struct ifreq);
                    continue;
                   
                }
                
                if (a<IFNAMSIZ) {
                    
                    strcpy(tmp.ifr_name, result->ifr_name);

#pragma mark 读取设备的活动标志字
                    /*
                     读取 或 设置 设备的 活动标志字. ifr_flags 包含 下列值 的 屏蔽位:
                     
                     IFF_UP    接口正在运行.
                     IFF_BROADCAST    有效的广播地址集.
                     IFF_DEBUG    内部调试标志.
                     IFF_LOOPBACK    这是自环接口.
                     IFF_POINTOPOINT    这是点到点的链路接口.
                     IFF_RUNNING    资源已分配.
                     IFF_NOARP    无arp协议, 没有设置第二层目的地址.
                     IFF_PROMISC    接口为杂凑(promiscuous)模式.
                     IFF_NOTRAILERS    避免使用trailer .
                     IFF_ALLMULTI    接收所有组播(multicast)报文.
                     IFF_MASTER    主负载平衡群(bundle).
                     IFF_SLAVE    从负载平衡群(bundle).
                     IFF_MULTICAST    支持组播(multicast).
                     IFF_PORTSEL    可以通过ifmap选择介质(media)类型.
                     IFF_AUTOMEDIA    自动选择介质.
                     IFF_DYNAMIC    接口关闭时丢弃地址.
                     
                     */
                    
                    if (ioctl(s, SIOCGIFFLAGS, &tmp) < 0)
                    {
                        perror("ioctl");
                        
                    }else
                    {
                        
                        if ((tmp.ifr_ifru.ifru_flags & IFF_UP) == 0)
                        {
                              continue;
                        }
                        
                        printf("%s\n", result->ifr_name);
                        get_ipaddr(result->ifr_name);
                        get_mac(result->ifr_name);
                        get_netmask(result->ifr_name);
                        get_broadcast(result->ifr_name);
                    }
                    
                }else{
                    printf("--buffer overflow\n");
                    
                    
                    if (ioctl(s, SIOCGIFFLAGS, result) < 0)
                    {
                        perror("long ioctl");
                        
                    }else
                    {
                        if ((tmp.ifr_ifru.ifru_flags & IFF_UP) == 0)
                        {
                             continue;
                        }
                        
                        printf("%s\n", result->ifr_name);
                        get_ipaddr(result->ifr_name);
                        get_mac(result->ifr_name);
                        get_netmask(result->ifr_name);
                        get_broadcast(result->ifr_name);
                    }
                   
                }
                
          
                    result = (struct ifreq *)ifreq_pointer+sizeof(struct ifreq);
                
            }
        
        }
   
    exit(0);
}

/**
 *
 * \brief   通过广播socket获取系统eth0当前IP地址
 *
 * \param  interface_name   指定网卡的名字 比如 eth0。
 *
 * \Return  0       成功
 *          else    失败
 */
int get_ipaddr(char *interface_name)
 {
#pragma mark AF_INET 与 PF_INET 没区别
     
         int s;
         if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            {
            perror("Socket");
                    return -1;
            }
    
         struct ifreq ifr;
         strcpy(ifr.ifr_name, interface_name);
    #pragma mark IP地址Get
    
     /*
     获取接口IP地址
     */
     
         if (ioctl(s, SIOCGIFADDR, &ifr) < 0)
             {
                     perror("ioctl");
                    return -1;
            }

        struct sockaddr_in *ptr;
         ptr = (struct sockaddr_in *) &ifr.ifr_ifru.ifru_addr;
    
         printf("    IP:%s\n", inet_ntoa(ptr->sin_addr));
    
         return 0;
}
/**
 *
 * \brief   通过ioctl获取系统eth0 Mac地址
 *
 * \param   interface_name   指定网卡设备名 比如eth0。
 *
 * \Return  0       成功
 *          else    失败
 */
 int get_mac(char *interface_name)
 {
         if (strcmp(interface_name, "lo") == 0)
             {
                return 0;
            }
    
        int s;

        if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
            {
                    perror("Socket");
                    return -1;
                }

        struct ifreq ifr;
        strcpy(ifr.ifr_name, interface_name);
     /*
      if (ioctl(s, SIOCGIFHWADDR, &ifr) != 0)
      {
      perror("ioctl");
      return -1;
      }
      */
    #pragma mark Mac地址Get
     /*
      SIOCGIFMAC
      获取Mac地址
      */
        if (ioctl(s, SIOCGIFMAC, &ifr) != 0)
            {
                    perror("ioctl");
                    return -1;
            }
     
         u_char *ptr;
     
        ptr = (u_char *) & ifr.ifr_ifru.ifru_addr.sa_data[0];
        printf("MAC:%02x-%02x-%02x-%02x-%02x-%02x\n",*ptr, *(ptr + 1),*(ptr + 2), *(ptr + 3), *(ptr + 4), *(ptr + 5));

         return 0;
}
/**
 *
 * \brief   通过广播socket获取系统eth0当前IP地址和子网掩码
 *
 * \param   interface_name   指定网卡设备名 比如eth0。
 *
 * \Return  0       成功
 *          else    失败
 */
 int get_netmask(char *interface_name)
 {
        int s;
    
         if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
             {
                    perror("Socket");
                     return -1;
            }
    
         struct ifreq ifr;
         strcpy(ifr.ifr_name, interface_name);
#pragma mark 获取最大传输单元Get 接口测度？
    /*
    SIOCGIFNETMASK 获取子网掩码
    SIOCGIFMETRIC 获取接口的测度
    SIOCGIFMTU, SIOCSIFMTU
     使用 ifr_mtu 读取 或 设置 设备的 MTU(最大传输单元). 设置 MTU 是 特权操作. 过小的 MTU 可能 导致 内核 崩溃.
     */
         if (ioctl(s, SIOCGIFMTU, &ifr) < 0)
             {
                     perror("ioctl");
                     return -1;
                 }

         //struct sockaddr_in *ptr;
        //ifru_netmask
     
        int mtu =  ifr.ifr_ifru.ifru_mtu;

         printf("最大传输单元:%d\n", mtu);
    
         return 0;
    }

int get_broadcast(char *interface_name)
 {
         int s;
    
         if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
            {
                perror("Socket");
                return -1;
            }
    
         struct ifreq ifr;
         strcpy(ifr.ifr_name, interface_name);
     
#pragma mark 获取广播地址Get

     /*
      获取广播地址
      */
     
        if (ioctl(s, SIOCGIFBRDADDR, &ifr) < 0)
             {
                     perror("ioctl");
                     return -1;
            }
        struct sockaddr_in *ptr;
        ptr = (struct sockaddr_in *) &ifr.ifr_ifru.ifru_broadaddr;

         printf("        Broadcast:%s\n", inet_ntoa(ptr->sin_addr));
    
         return 0;
    
}

int get_interface_info(char *interface_name)
{
         get_ipaddr(interface_name);
         get_mac(interface_name);
         get_netmask(interface_name);
         get_broadcast(interface_name);
    
         return 0;
}

int set_interface(char *interface_name)
 {
         char ip[18];
         char mac_addr[20];
         char netmask[18];
         char broadcast[18];
    
         printf("Change ");
         get_ipaddr(interface_name);
         printf("To:  ");
         fgets(ip, 17, stdin);
         if (strcmp(ip, "\n") == 0)
                 goto set_mac;
         set_ipaddr(interface_name, ip);
    
       set_mac:
         printf("Change ");
         get_mac(interface_name);
         printf("To:  ");
         fgets(mac_addr, 19, stdin);
         if (strcmp(mac_addr, "\n") == 0)
                 goto set_netmask;
        set_mac(interface_name, mac_addr);
    
       set_netmask:
         printf("Change ");
         get_netmask(interface_name);
         printf("To:  ");
         fgets(netmask, 17, stdin);
         if (strcmp(netmask, "\n") == 0)
                 goto set_broadcast;
         set_netmask(interface_name, netmask);
    
       set_broadcast:
         printf("Change ");
         get_broadcast(interface_name);
         printf("To:  ");
        fgets(broadcast, 17, stdin);
         if (strcmp(broadcast, "\n") == 0)
                 return 0;
        set_broadcast(interface_name, broadcast);
    
         return 0;
     }

int interface_up(char *interface_name)
 {
     /*
      用于设置网卡 IP Mac 地址等参数后, 激活新设置.
      */
         int s;
    
         if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
             {
            perror("Socket");
            return -1;
             }
    
         struct ifreq ifr;
         strcpy(ifr.ifr_name, interface_name);
    
         short flag;
         flag = IFF_UP;
         if (ioctl(s, SIOCGIFFLAGS, &ifr) < 0)
             {
                     perror("ioctl");
                     return -1;
             }
    
         ifr.ifr_ifru.ifru_flags |= flag;
    
         if (ioctl(s, SIOCSIFFLAGS, &ifr) < 0)
             {
                     perror("ioctl");
                     return -1;
             }
    
         return 0;
    
     }

 int interface_down(char *interface_name)
 {
         if (strcmp(interface_name, "lo") == 0)
             {
                printf("You can't pull down interface lo\n");
                     return 0;
             }
    
         int s;
    
         if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
             {
                     perror("Socket");
                     return -1;
                 }
    
         struct ifreq ifr;
         strcpy(ifr.ifr_name, interface_name);
    
         short flag;
         flag = ~IFF_UP;
         if (ioctl(s, SIOCGIFFLAGS, &ifr) < 0)
             {
                     perror("ioctl");
                     return -1;
            }
    
         ifr.ifr_ifru.ifru_flags &= flag;
    
         if (ioctl(s, SIOCSIFFLAGS, &ifr) < 0)
             {
                     perror("ioctl");
                     return -1;
             }
    
         return 0;
     }

int set_ipaddr(char *interface_name, char *ip)
 {
         int s;
    
         if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
             {
                     perror("Socket");
                     return -1;
                 }
    
         struct ifreq ifr;
         strcpy(ifr.ifr_name, interface_name);
    
         struct sockaddr_in addr;
         bzero(&addr, sizeof(struct sockaddr_in));
         addr.sin_family = PF_INET;
         inet_aton(ip, &addr.sin_addr);
     
    #pragma mark IP地址Set
     
         memcpy(&ifr.ifr_ifru.ifru_addr, &addr, sizeof(struct sockaddr_in));

         if (ioctl(s, SIOCSIFADDR, &ifr) < 0)
             {
                     perror("ioctl");
                     return -1;
            }
    
         return 0;
     }
int set_mac(char *interface_name, char *mac_addr)
 {
         int s;
         if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
             {
                perror("Socket");
                     return -1;
            }
    
         struct ifreq ifr;
         strcpy(ifr.ifr_name, interface_name);
    //SIOCGIFHWADDR
     /*
      if (ioctl(s, SIOCGIFHWADDR, &ifr) < 0)
      {
      perror("ioctl");
      return -1;
      }
      */
     #pragma mark MAC地址Set
     /*
      获取网卡Mac地址
      */
         if (ioctl(s, SIOCGIFMAC, &ifr) < 0)
             {
                     perror("ioctl");
                     return -1;
             }
    
         sa_family_t get_family;
     //ifru_hwaddr
     /*
      get_family = ifr.ifr_ifru.ifru_addr.sa_family;
      */
     get_family = ifr.ifr_ifru.ifru_addr.sa_family;
    
    interface_down(interface_name);
    
         bzero(&ifr, sizeof(struct ifreq));
         strcpy(ifr.ifr_name, interface_name);
         ifr.ifr_ifru.ifru_addr.sa_family = get_family;
    
         short tmp;
         int i, j;
         j = 0;
         for (i = 0; i < 17; i += 3)
             {
                     if (mac_addr < 58 && mac_addr > 47)
                    tmp = mac_addr - 48;
                if (mac_addr < 71 && mac_addr > 64)
                             tmp = mac_addr - 55;
                if (mac_addr < 103 && mac_addr > 96)
                        tmp = mac_addr - 87;
                    tmp = tmp << 4;
                if (mac_addr[i + 1] < 58 && mac_addr[i + 1] > 47)
                             tmp |= (mac_addr[i + 1] - 48);
                 if (mac_addr[i + 1] < 71 && mac_addr[i + 1] > 64)
                             tmp |= (mac_addr[i + 1] - 55);
                if (mac_addr[i + 1] < 103 && mac_addr[i + 1] > 96)
                             tmp |= (mac_addr[i + 1] - 87);
                    memcpy(&ifr.ifr_ifru.ifru_addr.sa_data[j++], &tmp, 1);
                 }
    /*
     设置网卡Mac地址
     */
        if (ioctl(s, SIOCSIFMAC, &ifr) < 0)
        {
            perror("ioctl");
            return -1;
        }
    
        interface_up(interface_name);
    
         return 0;
     }

int set_netmask(char *interface_name, char *netmask)
 {
         int s;
    
         if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
             {
                     perror("Socket");
                     return -1;
            }
    
        struct ifreq ifr;
        strcpy(ifr.ifr_name, interface_name);
    
         struct sockaddr_in netmask_addr;
            bzero(&netmask_addr, sizeof(struct sockaddr_in));
         netmask_addr.sin_family = PF_INET;
         inet_aton(netmask, &netmask_addr.sin_addr);
    
         memcpy(&ifr.ifr_ifru.ifru_cap, &netmask_addr,sizeof(struct sockaddr_in));
     
    #pragma mark 子网掩码Set
/*
 设置子网掩码
 */
         if (ioctl(s, SIOCSIFNETMASK, &ifr) < 0)
             {
                     perror("ioctl");
                    return -1;
                }
    
         return 0;
    
     }

int set_broadcast(char *interface_name, char *broadcast)
 {
         int s;
    
         if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
            {
                     perror("Socket");
                     return -1;
                 }
    
         struct ifreq ifr;
        strcpy(ifr.ifr_name, interface_name);
    
         struct sockaddr_in broadcast_addr;
         bzero(&broadcast_addr, sizeof(struct sockaddr_in));
         broadcast_addr.sin_family = PF_INET;
         inet_aton(broadcast, &broadcast_addr.sin_addr);
    
         memcpy(&ifr.ifr_ifru.ifru_broadaddr, &broadcast_addr,sizeof(struct sockaddr_in));
     
     #pragma mark 多播地址Set
    /*
     设置多播地址
     */
         if (ioctl(s, SIOCSIFBRDADDR, &ifr) < 0)
             {
                     perror("ioctl");
                     return -1;
                }
    
         return 0;
     }

 int usage(void)
 {
         printf("Usage: myifconfig [all]|[interface [set|up|down]]\n");
         return 0;
}













































