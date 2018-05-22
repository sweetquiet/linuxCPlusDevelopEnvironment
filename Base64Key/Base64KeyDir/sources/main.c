//
//  main.c
//  Base64Key
//
//  Created by admindyn on 2018/5/21.
//  Copyright © 2018年 admindyn. All rights reserved.
//
#include <stdlib.h>
#include "base64.h"
#include <stdio.h>
void get_restr(char  *str, size_t len)  ;
int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    if (argc<2) {
        printf("请输入要转码的16进制字符串\n");
        return 0;
    }
   const char* src = argv[0];

    const char* srcStr = argv[1];
    
    printf("您要转码的16进制字符串为:%s\n",srcStr);
    printf("开始转码:\n");
    uint8_t valDes [16];
    /*
     ""
     */
    char* valSrcStrP = srcStr;

#pragma mark 原以为和以前一样 低字节 在小端 我们测试处理 小端字节序 后来发现大端字节序
    
   // int zijiexu = sizeof(valDes)-1;
    int zijiexu = 0;
    int vnum =0;
    do {
        char val[4]={'0','x'};
        snprintf(val, 3, "%s",valSrcStrP);
        printf("%s-",val);
        long v =strtol(val, NULL, 16);
        valDes[zijiexu] =v;
        printf("%ld-",v);
        //zijiexu--;
        zijiexu++;
        vnum++;
    valSrcStrP=valSrcStrP+2;
        
    } while (*valSrcStrP!='\0');
    printf("\n");
    printf("获得大整数key:");
    
    for (int i=0;i<sizeof(valDes); i++) {
        printf("%.2x",valDes[i]);
    }
    printf("\n");
    char str64[64] = {0};
    bin_to_b64(valDes,sizeof(valDes),str64,sizeof(str64));
    
    printf("%s",str64);
    
    return 0;
}
void get_restr(char  *str, size_t len)           //字符串的逆序函数
{
    char temp;
    int i;
    for(i = 0; i < len / 2; i++)
    {
        temp = *(str + i);
        char con = *(str + len - i - 1);
        *(str + i) = con;
        
        *(str + len - 1 - i) = temp;
    }
    
    return ;
}
