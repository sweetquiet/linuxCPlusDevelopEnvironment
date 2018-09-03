//
//  main.c
//  DevMachine
//
//  Created by admindyn on 2018/5/18.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
char right,left,temp;//right表示低八位，left表示高八位
int size_right,size_left,size_temp;
short int number,size_number;
short int number_two,number_three;
void test (void);
char* my_itoa(int value, char* result, int base);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    
    test();
    
    /*
     传感器的DevEUI地址为8个字节长度，其中最高3个字节为OUI用于唯一标识生产厂家的地址编码。智云自己生产的产品OUI地址定义为40-01-01，其他生产厂家按照此OUI地址向上递增，在核心网管理系统中做好此OUI和对应客户的关联。
     
     */
    
    
    //大端字节序 看16进制表示的devui
    //解析devui 即mac地址的含义
    
    //大端字节序 高位前三个字节 固定
    int dev = 0x400101;
    
    //大端字节序 高位第四个字节 字节的高4位
    //代表产品类型
    int brandType = 3;
    //大端字节序 高位第四个字节 字节的低4位
    
    //代表频点类型
    int pinDianType = 4;
    
    //小端字节序 第四个字节 字节的最高位 是 0 还是 1 判断
    //  是否国际标准
    int ouStyle = 0;
    
    //
    //小端字节序 第四个字节 字节的低6位
    //代表生产年份 除以100 得到的余数
    // 111111
    
    int year = 2018%100;
    
    //小端字节序 看 第三个字节 高4位
    //1111 = 15
    
    int month = 4;
    
    
    //小端字节序 看 第三个字节
    //第三个字节的低4位 + 第二个字节最高位二进制数
    //代表生产日期的 当天 比如 31号 16 号
    /*
     1111 2进制数代表 15 一旦过了16号  就需要第二个字节的最高位二进制数为1
     11111 16+15 =31
     16 是2的5-1 次方  也就是 2的4次方
     
     */
    int day = 7;//0+0111
    printf("\n%d\n",day);
    printf("\n%.2x\n",day);
    /*
     i ---- 需要转换成字符串的数字
     num ---- 转换后保存字符串的变量
     10 ---- 转换数字的基数（即进制）。10就是说按10进制转换数字。还可以是2，8，16等等你喜欢的进制类型
     */
    char string[32];
    char* res=  my_itoa(day, string, 2);
    //itoa(i ,num ,10 );
    //数字转字符串
    char str[10];
    sprintf(str,"%.2X",day);
    printf("\n%s\n",str);
    printf("\n%s\n",string);
    printf("\n%s\n",res);
    
    
    /*
     可移植性
     */
     //字符串转数字
    int n = 0;
    sscanf(res,"%d",&n);
    printf("\n新的%d\n",n);
    //小端字节序 看 前两个字节
    //前两个字节的 低15位代表
    //代表产品编码SN
    int productSN = 0b100000000000000;
    
    int8_t devEui [8];
    
    int8_t* pV = devEui;
    
    
    
    
    
    
    
    
    return 0;
}

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 
 */
char* my_itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }
    
    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;
    
    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );
    
    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

void test (void)
{
    number =32343; //65536个数范围是 -32768-32767
        size_number = sizeof(number);
        size_right = sizeof(right);
        size_left = sizeof(left);
        size_temp = sizeof(temp);
        printf("size_number=%d个字节\n",size_number);
        printf("size_left=%d个字节\n",size_left);
        printf("size_right=%d个字节\n",size_right);
        printf("size_temp=%d个字节\n",size_temp);
       printf("number=%d\n",number);
    right = number&0XFF;//低八位
        left = number>>8;//高八位
        printf("right = %d\n",right);
        printf("left  = %d\n",left);
        printf("number_two=%d\n",left*256+right);
        //前取高八位，在取低八位
        left=(number>>8)&0XFF; //先取高八位
        right=number&0XFF;     //再取第八位
        printf("number_two=%d\n",left*256+right);
        //现在要把高八位和第八位合并
        number_three=left;
        number_three<<=8;
        number_three|=right;
    printf("number_three=%d",number_three);
    
}
