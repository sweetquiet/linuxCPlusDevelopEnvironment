//
//  AEST.c
//  CAESKEY
//
//  Created by admindyn on 2018/6/1.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <memory.h>
#include <unistd.h>


#include "AEST.h"

/*
 AES 用到异或运算
 
 0^0=0,0^1=1    0异或任何数，其结果=任何数
 1^0=1,1^1=0    1异或任何数，其结果=任何数取反
 x^x=0    任何数异或自己，等于把自己置0
 
 异或 可以使指定位 值反转
  0111 10100001
 ^0000 11111111
 ----------------
  0111 01011110
 
 异或实现两个值的交换
 
 异或 原文 与 密钥 异或  加密 得到密文
        密文 与 密钥 再异或 得到原文
 
 而原文 与 密文 异或 可以得到 密钥
 
 AES  已知明文暴力破解
 
 AES 如何做到安全
 相对安全的Block Cipher Mode有CBC、PCBC、CFB、OFB、CTR等，其关键思想就是在加密过程中加入上下文块相关或者位置相关的盐。
 */


void test(void)
{
    DATA_INFO info = {
        .dataKeyKey = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,},
        .datanonceApp={0x01,0x02,0x03},
        .datanonceDev={0x01,0x02},
        .datanonceNetID={0x01,0x02,0x03}};
    /*
     当是结构体 访问数据成员 用 . 操作符
     当是结构体指针 使用->访问数据成员
     */
    
    copy_aes_sesskeys(&info);
    
    
}

void copy_aes_sesskeys(DATA_INFO* info)
{
    aes_context aesContext;
    
    /*
     加密策略 使用 16字节 128bit 加密手段
     */
    
    uint8_t b[LORA_KEY_LENGTH];
    
    /*
     AES 如何做到安全
     相对安全的Block Cipher Mode有CBC、PCBC、CFB、OFB、CTR等，其关键思想就是在加密过程中加入上下文块相关或者位置相关的盐。
     */
    memset(&aesContext,0,sizeof(aesContext));
    
    memset(b,0,LORA_KEY_LENGTH);
    
    b[1] = info->datanonceApp[0];
    b[2] = info->datanonceApp[1];
    b[3] = info->datanonceApp[2];
    
    b[4] = info->datanonceNetID[0];
    b[5] = info->datanonceNetID[1];
    b[6] = info->datanonceNetID[2];
    
    b[7] = info->datanonceDev[0];
    b[8] = info->datanonceDev[1];
    
    b[0] = 0x01;
    /*
     这里根据加的上下文的盐 和 我们已知的根密钥
     生成密钥 矩阵
     密钥矩阵特点 其实 每一行 是16字节的 128bit
     但是我们看到文档标注第一行 第一列 元素 是1个32位空间 也就是 4个字节 使用的W[0]
      C语言的宽字节数据类型
     
     设K = “abcdefghijklmnop”，则K0 = a, K15 = p, W[0] = K0 K1 K2 K3 = “abcd”。
     N_MAX_ROUNDS = 14
     N_ROW = 4
     N_COL = 4
     N_BLOCK= N_ROW * N_COL
     typedef struct
     {   uint_8t ksch[(N_MAX_ROUNDS + 1) * N_BLOCK];
         uint_8t rnd;
     } aes_context;
     
     我们进行15 轮 轮密钥加
     
     
     101100   44
     10110000 176
     1011     11
     
     16字节的密钥加密 使用10轮
     前N-1轮
     
     每一轮依次 进行：
     字节代替
     行移位变换
     列混淆
     轮密钥加
     操作 总共进行N-1 轮
     
     最后一轮包含3个变换 而在第一轮前面有一个起始的单变换--轮密钥加 可视为第0轮
     
     每一个变换需要输入一个或多个4*4的矩阵 并输出 4*4 矩阵
     
     最后一轮输出密文
     
     
     */
    copy_aes_set_key(info->dataKeyKey, LORA_KEY_LENGTH, &aesContext);
    
    
}

/*
 字节替换
 */


void SubBytes(unsigned char state[4][4])
{
    /*
     状态 state 矩阵  state[r][c] = 16i+j
     1个字节 8位 2个16进制数 这个表达式是
     16进制 表达式举例 0x11 * 16 + 0x10
     i为高四位 j为低四位
     
     s盒子 位 16*16 矩阵
     
     因此需要 statr[r][c] =
     */
    
    
}
/*
 
 设初始的128位密钥为：
 3C A1 0B 21 57 F0 19 16 90 2E 13 80 AC C1 07 BD
 那么4个初始值为：
 W[0] = 3C A1 0B 21
 W[1] = 57 F0 19 16
 W[2] = 90 2E 13 80
 W[3] = AC C1 07 BD
 下面求扩展的第1轮的子密钥(W[4],W[5],W[6],W[7])。
 由于4是4的倍数，所以：
 W[4] = W[0] ⨁ T(W[3])
 T(W[3])的计算步骤如下：
 1. 循环地将W[3]的元素移位：AC C1 07 BD变成C1 07 BD AC;
 2. 将 C1 07 BD AC 作为S盒的输入，输出为78 C5 7A 91;
 3. 将78 C5 7A 91与第一轮轮常量Rcon[1]进行异或运算，将得到79 C5 7A 91，因此，T(W[3])=79 C5 7A 91，故
 W[4] = 3C A1 0B 21 ⨁ 79 C5 7A 91 = 45 64 71 B0
 其余的3个子密钥段的计算如下：
 W[5] = W[1] ⨁ W[4] = 57 F0 19 16 ⨁ 45 64 71 B0 = 12 94 68 A6
 W[6] = W[2] ⨁ W[5] =90 2E 13 80 ⨁ 12 94 68 A6 = 82 BA 7B 26
 W[7] = W[3] ⨁ W[6] = AC C1 07 BD ⨁ 82 BA 7B 26 = 2E 7B 7C 9B
 所以，第一轮的密钥为 45 64 71 B0 12 94 68 A6 82 BA 7B 26 2E 7B 7C 9B。
 */



return_type copy_aes_set_key(const unsigned char key[],length_type keylen,aes_context ctx[1])
{
    /*
     将原本16字节的密钥 扩展为44字 每一个字4字节32位
     
     扩展为44字的 密钥序列
     
     以后加密的每一轮 对应从中取出  依次取出 4个字 作为轮密钥
     */
    uint8_t cc, rc,hi;
    
    switch (keylen) {
        case 16:
        case 24:
        case 32:
            break;
            
        default:
            ctx->rnd = 0;
            return -1;
    }
    //15*16 = 240 ;
    
    copy_block_copy_nn(ctx->ksch, key, keylen);
    //16 10000 0x10
    hi = (keylen + 28) << 2;
    //44 101100 60 111100
    ctx->rnd = (hi >> 4) - 1;
    // 16 字节10 轮 32 字节 14轮
    
    /*
     密钥扩展函数为 N+1 轮
     */
    /*
     hi == 44  密钥序列 总共44个字
     cc 初始为 16
     cc 最大值 176
     用cc 对 16 取余 余数为0
     则代表 cc 取到了 16 32 48 64 80 96 112 128 144 160 176
     */
    //0x10 = 16 0xb0 = 176 10110000
    /*
     密钥矩阵的 前四个字 已经 用原始密钥填充
     
     之后形成的 10 行 字 密钥
     i>4 i=5
     每次新增一个密钥字 算法是 W[i]的值 依赖 W[i-4] 和W[i-1]
     */
    for (cc = keylen,rc = 1; cc<hi;cc+=4) {
       /*
        首先将第一轮的密钥的 第4列 4个字节 32位
        
        进行操作
        
        第一：字循环 将第四列四个元素 循环左移一位
        [t0,t1,t2,t3] -> [t1,t2,t3,t0]
        
        
        第二：循环移位后所得数组进行s盒字节替代
        
        */
        /*
         第一：字循环 将第四列四个元素 循环左移一位
         [t0,t1,t2,t3] -> [t1,t2,t3,t0]
         */
        uint_8t tt, t0, t1, t2, t3;
        
        t0 = ctx->ksch[cc - 4];
        t1 = ctx->ksch[cc - 3];
        t2 = ctx->ksch[cc - 2];
        t3 = ctx->ksch[cc - 1];
        if( cc % keylen == 0 )
        {
            tt = t0;
            t0 = s_box(t1) ^ rc;
            t1 = s_box(t2);
            t2 = s_box(t3);
            t3 = s_box(tt);
            rc = f2(rc);
        }
    }
    
    return 0;
    
}

void copy_block_copy_nn(void* dest,const void*src,size_t srclen)
{
    memcpy(dest,src,srclen);
    
}





















