//
//  main.c
//  SocketTLS
//
//  Created by admindyn on 2018/6/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include "ssl.h"
#include "err.h"
#include "bio.h"
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


#define MAXBUF 1024
#define CA_FILE "cacert.pem"
#define CA_PATH ""
#define SERVER_PKEY_FILE "server-key.pem"
#define SERVER_CERT_FILE "server-cert.pem"
#define CLIENT_PKEY_FILE "client-key.pem"
#define CLIENT_CERT_FILE "client-cert.pem"
#define WEB_DIR "./web_con/"
#define FILES_DIR "/files"

void showCerts(SSL* ssl)
{
    X509* cert;
    
    char* line;
    
    cert = SSL_get_peer_certificate(ssl);
    
    if (cert!=NULL) {
        printf("Digital certificate information:\n");
        
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        
        printf("Certificate:%s\n",line);
        
        free(line);
        
        
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        
        printf("Issuer:%s\n",line);
        
        free(line);
        
        X509_free(cert);
    }else
    {
        printf("No certificate information\n");
        
    }

}

int testClient(int argc, const char * argv[]);

int testServer(int argc, const char * argv[]);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    testServer(argc, argv);
    
    
    return 0;
}

int testServer(int argc, const char * argv[])
{
    
    int sockfd,fd_new,fd;
    socklen_t len;
    struct sockaddr_in my_addr,their_addr;
    unsigned int myport , lisnum;
    char buf[MAXBUF+1];
    char file_Name_N[50] = WEB_DIR;
   __owur SSL_CTX* ctx;
    mode_t mode;
    char pwd[100];
    char* temp;
    /*
     在根目录下创建一个文件夹
     */
    getcwd(pwd, 100);
    /*
     strlen 返回 字符串长度 这里专门判断1 strlen计算字符
     不包括'\0'
     */
    if (strlen(pwd)==1) {
        pwd[0]='\0';
    }
    
    /*
     在命令行运行时 就是程序工作目录
    比如我在/Users/admindyn/Downloads/certs-2目录运行程序
     工作目录 /Users/admindyn/Downloads/certs-2
     */
    printf("工作目录 %s\n",pwd);
  // int state = mkdir(FILES_DIR, mode);
   // printf("mkdir state:%d\n",state);
    if (argv[1]) {
        myport = atoi(argv[1]);
    }else
    {
#pragma mark 默认 端口
        myport = 7838;
        argv[2] = argv[3]= NULL;
    }
    if (argv[2]) {
        lisnum = atoi(argv[2]);
    }else
    {
#pragma mark 默认 连接并发数
        lisnum = 2;
        argv[3] = NULL;
    }
    /*
     SSL 库初始化
     */
    SSL_library_init();
    /*
     SSL算法库
     */
    OpenSSL_add_all_algorithms();
    /*
     载入所有SSL错误信息
     */
    SSL_load_error_strings();
    /*
     以ssl v2 和 v3 标准兼容方式生产一个SSL CTX 即SSL Content Text
     */
__owur const SSL_METHOD *   meth = SSLv23_server_method();
    ctx = SSL_CTX_new(meth);
    
    /*
     也可以用 SSLv2_server_method() 或 SSLv3_server_method() 单独表示 V2 或 V3标准
     当SSL会话环境申请成功后，还要根据实际的需要设置CTX的属性，通常的设置是指定SSL握手阶段证书的验证方式和加载自己的证书。
     */
    
/*　当设置为1时，假如关闭后，不通知对方，这样不适合TLS标准*/
    SSL_CTX_set_quiet_shutdown(ctx,1);
/*ctx->options|=SSL_OP_ALL，     SSL/TLS有几个公认的bug,这样设置会使出错的可能更小
       */
    SSL_CTX_set_options(ctx,SSL_OP_ALL);
    /*
    设置cache的大小:
    默认的为1024*20=20000，这个也就是可以存多少个session_id，一般都不需要更改的。假如为0的话将是无限
    */
    SSL_CTX_sess_set_cache_size(ctx,128);
    /*
     用于加载受信任的CA证书，CAfile如果不为NULL，则他指向的文件包含PEM编码格式的一个或多个证书，可以用e.g.来简要介绍证书内容
     　　
     CApath如果不为NULL，则它指向一个包含PEM格式的CA证书的目录，目录中每个文件包含一份CA证书，文件名是证书中CA名的HASH值
     　
     　可以用c-rehash来建立该目录，如cd /some/where/certs（包含了很多可信任的CA证书） c_rehash。返回一成功，0 失败。
     */
    
        char* capath = NULL;
        char* cafile = CA_FILE;
    
     SSL_CTX_load_verify_locations(ctx,cafile,capath);
    
    if(cafile !=NULL )SSL_CTX_set_client_CA_list(ctx,SSL_load_client_CA_file(cafile));
    
    /*
     设置验证方式
     SSL_VERIFY_NONE表示不验证，SSL_VERIFY_PEER用于客户端时要求服务器必须提供证书，用于服务器时服务器会发出证书请求消息要求客户端提供证书，但是客户端也可以不提供　　SSL_VERIGY_FAIL_IF_NO_PEER_CERT只适用于服务器且必须提供证书。他必须与SSL_VERIFY_PEER一起使用
     */
    
   //static int s_server_verify=SSL_VERIFY_NONE;
    
    SSL_CTX_set_verify(ctx,SSL_VERIFY_PEER,NULL/*verify_callback*/);
    
    if (ctx == NULL) {
        ERR_print_errors(stdout);
        return  -1;
    }
    
    /*
     载入用户的数字证书 此证书用来发送給客户端 证书里 包含有公钥
     */
    
    getcwd(pwd, 100);
    
    if (strlen(pwd)==1) {
        pwd[0]='\0';
    }
    /*
     该函数读取证书文件，证书文件通常都进行了加密保护。普及一下，证书文件里肯定是有公钥的，一般没私钥，某些情况会把私钥也包含进去，但那样作太不安全了，原则上私钥是永远不会给别人看到的，就算是进行了加密保护
     */
    int slstate = -1;
    
    if ((slstate=SSL_CTX_use_certificate_file(ctx, temp= SERVER_CERT_FILE, SSL_FILETYPE_PEM))<0) {
        
        ERR_print_errors(stdout);
        
        return -1;
    }
    
    /*
     载入用户私钥
     */
    
    getcwd(pwd, 100);
    
    if (strlen(pwd)==1) {
        pwd[0] = '\0';
    }
    /*
     设置SSL要加载的证书的口令，如果不设置的话加载证书时会出提示符要求输入口令的，这样在程序中使用就比较麻烦，该函数就是预先将口令保存，在读证书时自动使用
     获取私钥之前先把私钥的密码给写上 我们这里没有密码
     char *pKeyPasswd="serve";
     SSL_CTX_set_default_passwd_cb_userdata(ctx, pKeyPasswd);
     */
    if ((slstate=SSL_CTX_use_PrivateKey_file(ctx, temp= SERVER_PKEY_FILE,SSL_FILETYPE_PEM))<0) {
            
        ERR_print_errors_fp(stdout);
            
        return -1;
            
        }
    
    
        /*
         检查用户私钥是否正确
         */
        if (!SSL_CTX_check_private_key(ctx)) {
            ERR_print_errors_fp(stdout);
            
            return -1;
        }
        /*
         开启一个socket 监听
         */
#pragma mark 这里服务器是PF_INET
        if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)
            )==-1) {
            perror("socket");
            return  -1;
        }else
        {
            printf("socket created\n");
        }
    
        bzero(&my_addr, sizeof(my_addr));
        my_addr.sin_family = PF_INET;
        my_addr.sin_port= htons(myport);
        if (argv[3]) {
            my_addr.sin_addr.s_addr = inet_addr(argv[3]);
        }else
        {
            my_addr.sin_addr.s_addr = INADDR_ANY;
        }
        if (bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr))==-1) {
            perror("bind");
            return -1;
        }else
        {
            printf("binded\n");
        }
        if (listen(sockfd, lisnum)==-1) {
            perror("listen");
            
            return -1;
        }else
        {
            printf("begin listen\n");
        }
        while (1) {
            /*ssl套接字*/
            SSL* ssl;
            ssl = SSL_new(ctx);
            len = sizeof(struct sockaddr);
            /*
             等待客户端连接上来
             */
            if ((fd_new = accept(sockfd, (struct sockaddr*)&their_addr, &len))==-1) {
                perror("accept");
                return -1;
            }else
            {
                printf("server: got connection from %s,port %d socket %d\n",inet_ntoa(their_addr.sin_addr),ntohs(their_addr.sin_port),fd_new);
            }
                /*
                 基于ctx 产生一个新的SSL
                 建立SSL套接字
                 SSL套接字是建立在普通的TCP套接字基础之上，在建立SSL套接字时
                 先 申请一个SSL套接字
                 */
                ssl = SSL_new(ctx);
            
                /*
                 再 绑定读写套接字
                 将连接用户的socket 加入到ssl
                 */
                
                SSL_set_fd(ssl, fd_new);
                
                /*
                 建立SSL连接 这里服务端 普通的socket accept 之后又进行ssl accept
                 */
                
                if (SSL_accept(ssl)==-1) {
                    perror("ssl accept");
                    
                    close(fd_new);
                    
                    break;
                }
            
            printf("accept with %s encryption\n",SSL_get_cipher(ssl));
            showCerts(ssl);
            
                /*
                 接受客户端所传文件的文件名 并在特定目录创建空文件
                 */
                bzero(buf, MAXBUF+1);
                int file_offset = 9;
                bzero(file_Name_N+file_offset, 42);
                
                len = SSL_read(ssl, buf, MAXBUF);
                
                if (len == 0) {
                    printf("Receive Complete\n");
                }else if (len<0)
                {
                    printf("Failure to receive message!Error code is %d,Error Messages are %s\n",errno,strerror(errno));
                }
            
            char* fspace = strcat(file_Name_N, buf);
            printf("收到将文件写入默认目录的指定文件名下:%s\n",fspace);
            
                if ((fd=open(fspace, O_CREAT|O_TRUNC|O_RDWR,0666))<0) {
                        perror("open:");
                        return -1;
                    }
#pragma mark 读写1
        /*
        接受客户端的数据并写入文件
                    */
                    while (1) {
                        bzero(buf, MAXBUF+1);
                        len = SSL_read(ssl, buf, MAXBUF);
                        if (len==0) {
                            printf("Receive Complete\n");
                            break;
                        }else if(len<0)
                        {
                            printf("Failure to receive message! Error code is %d,Error message are %s\n",errno,strerror(errno));
                            return -1;
                            
                        }
                        
        
                        if (SSL_write(ssl, buf, len)<0) {
                            perror("write:");
                            
                            return  -1;
                        }
                        
                        
                        
                        
                    }
                    

  #pragma mark 读写2
                    /*
                     关闭文件
                     */
                    
                    close(fd);
                    
                    /*
                     关闭SSL连接
                     */
                    
                    SSL_shutdown(ssl);
                    /*
                     释放SSL
                     */
                    
                    SSL_free(ssl);
                    
                    /*关闭socket*/
                    
                    close(fd_new);
            
                
            }
        
        
        
        /*关闭监听的socket*/
        
        close(sockfd);
        
        /*释放SSL CTX */
        
        SSL_CTX_free(ctx);
    
    return 0;
}

int testClient(int argc, const char * argv[])
{
    
    int i,j,sockfd,len,fd,size;
    
    char fileName[50],sendFN[20];
    
    struct sockaddr_in dest;
    
    char buffer[MAXBUF+1];
    
    SSL_CTX* ctx;
    
    SSL* ssl;
    
    if (argc!=3) {
        printf("Parameter format error! Correct usage is as follows:\n\t\t%s IP Port \n\t Such as: \t %s 127.0.0.1 80 \n",argv[0],argv[0]);
        return -1;
    }
    /*
     xxx 127.0.0.1 80
     
     */
    
    //SSL库初始化
    SSL_library_init();
    
    
    OpenSSL_add_all_algorithms();
    
    SSL_load_error_strings();
    
    ctx = SSL_CTX_new(SSLv23_client_method());
    
    if (ctx==NULL) {
        ERR_print_errors_fp(stderr);
        return -1;
    }
    /*
     创建一个socket 用于tcp通信
     */
#pragma mark 这里客户端是AF_INET
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0) {
        perror("socket");
        return -1;
    }
    
    printf("socket created\n");
    
    /*
     初始化服务器端 （对方）的地址和端口信息
     */
    
    bzero(&dest, sizeof(dest));
    
    
    dest.sin_family = AF_INET;
    
    dest.sin_port = htons(atoi(argv[2]));
    
    if (inet_aton(argv[1], (struct in_addr*)&dest.sin_addr)==0) {
        perror(argv[1]);
        
        return -1;
    }
    
    printf("address created\n");
    
    
    /*
     连接服务器
     */
    
    
    if (connect(sockfd, (struct sockaddr*)&dest, sizeof(dest))!=0) {
        perror("connenct");
        return -1;
    }
    
    printf("server connecnted\n");
    
    
    /*
     基于ctx 产生一个新的ssl
     */
    
    
    ssl = SSL_new(ctx);
    
    SSL_set_fd(ssl, sockfd);
    /*
     建立SSL 连接
     */
    
    
    if (SSL_connect(ssl)==-1) {
        ERR_print_errors_fp(stderr);
        
    }else
    {
        printf("connencted with %s encryption\n",SSL_get_cipher(ssl));
        showCerts(ssl);
    }
    
    /*
     接受用户输入的文件名 并打开文件
     */
    
    printf("\n Please input the file name of you want to load:\n");
    
    scanf("%s",fileName);
    
    if ((fd=open(fileName, O_RDONLY,0666))<0) {
        perror("open:");
        
        return -1;
    }
    
    /*
     将用户输入的文件名 去掉路径信息后 发给服务器
     */
    j=0;
    i=0;
    
    for (i=0; i<=strlen(fileName); i++) {
        if (fileName[i]=='/') {
            j=0;
            continue;
        }else{
            sendFN[j]= fileName[i];
            ++j;
        }
    }
    
    len = SSL_write(ssl, sendFN, strlen(sendFN));
    
    if (len<0) {
        printf("%s message sebd failure!Error code is %d ,Error Messages are %s \n",buffer,errno,strerror(errno));
        
        /*
         循环发送消息内容给服务器
         */
        
        bzero(buffer, MAXBUF+1);
        
        while ((size = read(fd, buffer, 1024))) {
            if (size<0) {
                perror("read:");
                return  -1;
            }else
            {
                len = SSL_write(ssl, buffer, size);
                if (len<0) {
                    printf("%s message sebd failure!Error code is %d ,Error Messages are %s \n",buffer,errno,strerror(errno));
                    
                    
                    
                }
                
                bzero(buffer, MAXBUF+1);
                
                
                
            }
            
            
        }
        
        printf("Send complete!\n");
    }
    
    /*
     关闭连接
     */
    
    close(fd);
    
    SSL_shutdown(ssl);
    
    SSL_free(ssl);
    
    close(sockfd);
    
    SSL_CTX_free(ctx);
    
    
    return 0;

}











