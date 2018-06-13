//
//  AEST.c
//  CAESKEY
//
//  Created by admindyn on 2018/6/1.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <memory.h>
#include <unistd.h>
#include "SuanFa.h"

#include "AEST.h"

/*
 位运算 实现加减乘除
 
 https://www.jianshu.com/p/7bba031b11e7
 */


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
typedef unsigned char uc;
uc sboxTest[16][16];
/*
 被调用函数uc msb(unsigned short num) msb函数返回最高非零位的位置（当然是从0开始）
 */
uc msb(unsigned short num)
{
    uc i;
    for(i = 0; i <= 8; i++)
    {
        if(!(num >> (i + 1)))
        {
            return i;
        }
    }
    return -1;
}
uc divide(unsigned short a, uc b, uc *r)
{
    /*
     被调用函数uc msb(unsigned short num) msb函数返回最高非零位的位置（当然是从0开始）
     */
    uc a_msb = msb(a);
    uc b_msb = msb(b);
    if(a < b)
    {
        //      printf("111111\n");
        *r = a;
        //  printf("22222\n");
        return 0;
    }
    uc bit = a_msb - b_msb;
    unsigned short temp = b;
    temp = temp << bit;
    a = a ^ temp;
    //  printf("%0x\n",a);
    return (1 << bit) | divide(a, b, r);
}

uc multiply(uc a, uc b)
{
    uc res = 0;
    if(b & 0x01)
    {
        res = a;
    }
    for (uc i = 1; i < 8; i++)
    {
        if(b & (0x01 << i))
        {
            uc temp = a;
            for(uc j = 0; j < i; j++)
            {
                if(!(temp & 0x80))
                {
                    temp <<= 1;
                }
                else
                {
                    temp <<= 1;
                    temp = temp ^ 0x1B;
                }
            }
            res = res ^ temp;
        }
    }
    return res;
}
/*
 该函数 返回乘法 逆元
 参数及返回值说明 返回b
 的乘法逆元
 */
uc inverse(uc b)
{
    /*
     先去看懂扩展欧几里得算法
     */
    
    if(b == 0)
        return 0;
    /*
      0x11b 这个在AES 中出现相同值的宏定义 WPOLY
     */
    short r0 = 0x11B;
    uc r1 = b, r2, q;
    //  uc v0 = 1, v1 = 0, v2;
    uc w0 = 0, w1 = 1, w2;
    /*
     双字节除法
     参数及返回值说明 参数a
     和b
     分别为被除数和除数，即a/b
     ；参数r
     r是存储余数的；返回值是商。（此处余数和商应该可以用一个结构体解决，这样就不用指针的方法了）。
     */
    q = divide(r0, r1 , &r2);
    //  v2 = v0 ^ multiply(q, v1);//v2 = 1
    /*
     单字节乘法 0x1b 这个在AES 中出现相同值的宏定义 BPOLY
     */
    w2 = w0 ^ multiply(q, w1);//w2 = -q
    while(1)
    {
        //      printf("q=%02x,v=%02x,w=%02x\n",q,v2,w2);
        if(r2 == 0)
            break;
        r0 = r1;
        r1 = r2;
        q = divide(r0, r1, &r2);
        //      v0 = v1;
        //      v1 = v2;
        //      v2 = v0 ^ multiply(q, v1);
        w0 = w1;
        w1 = w2;
        w2 = w0 ^ multiply(q, w1);
    }
    return w1;
}
uc map(uc a)
{
    //  uc matrix[] = {0xF1, 0xE3, 0xC7, 0x8F, 0x1F, 0x3E, 0x7C, 0xF8};
    uc c = 0x63;
    uc res = 0x0;
    uc temp = 0x0;
    uc i;
    for(i = 0; i < 8; i++)
    {
        temp = temp ^ ((a >> i) & 0x1) ^ ((a >> ((i + 4) % 8)) & 0x1);//优先级>> 高于 &
        temp = temp ^ ((a >> ((i + 5) % 8)) & 0x1) ^ ((a >> ((i + 6) % 8)) & 0x1);
        temp = temp ^ ((a >> ((i + 7) % 8)) & 0x1) ^ ((c >> i) & 0x1);
        res = res | (temp << i);
        temp = 0x0;
    }
    return res;
}
void s_box_initial(void)
{
    
        uc i, j;
        for(i = 0; i <= 0xF; i++)
        {
             // printf("\n");
            for(j = 0; j <= 0xF; j++)
            {
                /*
                 先初始化S-box,使第x
                 行第y
                 列的元素为{xy
                 }
                 */
                
                sboxTest[i][j] = inverse((i << 4) + j);
                   //  printf("%02x ",sboxTest[i][j]);
            }
        }
    
    uc i2, j2;
    for(i2 = 0; i2 <= 0xF; i2++)
    {
        printf("\n");
        for(j2 = 0; j2 <= 0xF; j2++)
        {
            sboxTest[i2][j2] = map(sboxTest[i2][j2]);
            printf("%02X ",sboxTest[i2][j2]);
        }
    }
    
}

void test(void)
{
    s_box_initial();
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
     将原本16字节的密钥 扩展为44字 每一个双字 4字节32位
     
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
    //16 10000 = 0x10
    //32
    //24
    hi = (keylen + 28) << 2;
    //44 101100
    //60 111100
    //52 110100
    // 101100 10110000=176 1011 = 11
    // 111100 11110000=240 1111 = 15
    // 110100 11010000=208 1101 = 13
    ctx->rnd = (hi >> 4) - 1;
    // 16 字节10 轮 32 字节 14轮
    
    /*
     密钥扩展函数为 N+1 轮
     */
    /*
     hi == 44  密钥序列 总共44个双字
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
        /*
         第一次循环 就先拿到 当前密钥序列中最后一个双字的 四个字节的值
         12 13 14 15 字节的值
         */
        uint_8t tt, t0, t1, t2, t3;
        
        t0 = ctx->ksch[cc - 4];
        t1 = ctx->ksch[cc - 3];
        t2 = ctx->ksch[cc - 2];
        t3 = ctx->ksch[cc - 1];
        /*
         这里以16字节换行 因此当前序列中最后一个双字节 已经到16 也就是16的倍数
         
         */
        if( cc % keylen == 0 )
        {
            /*
             当cc 加到16的倍数时
             对当前持有的4个字节
             也就是这个字 进行行移位
             也就是 字循环：将当前1各自中的4个字节循环左移一个字节
             */
            tt = t0;
            /*
            按照算法这里异或是需要
             与32 bits的常量（RC[j/4],0,0,0）进行异或，RC是一个一维数组，其值如下。（RC的值只需要有10个，而此处用了11个，实际上RC[0]在运算中没有用到，增加RC[0]是为了便于程序中用数组表示。由于j的最小取值是4，j/4的最小取值则是1，因此不会产生错误。）
             注意 这里是 轮常量异或：将前两步的结果同轮常量Rcon[j/4]进行异或，其中j/4表示轮数 j表示字的 列数
             
             　　　　　　RC = {00 000000,
             01 000000,
             02 000000,
             04 000000,
             08 000000,
             10 000000,
             20 000000,
             40 000000,
             80 000000,
             1B 000000,
             36 000000}
             
             上面的RC数据 中11个元素 都是四字节的字 我这里补全了 其余三个字节000000
             但是由于 任何数异或0 还是任何数 节省了性能
             */
            /*
             宏定义 s_box
             sbox[(x)]
             uint_8t sbox[256]  =  sb_data(f1)
             sb_data(f1)
             f1(x)   (x)
             */
            t0 = s_box(t1) ^ rc;
            //任何数异或0 还是任何数
            t1 = s_box(t2);
            t2 = s_box(t3);
            t3 = s_box(tt);
            /*
             这里修改轮常量  第一轮 轮常量默认为1
             然后通过f2函数 修改 下一轮要用的常量
             */
            rc = f2(rc);
        }else if( keylen > 24 && cc % keylen == 16 )
        {
            t0 = s_box(t0);
            t1 = s_box(t1);
            t2 = s_box(t2);
            t3 = s_box(t3);
        }
        tt = cc - keylen;
        /*
         前面 奠定基础
         如果 当前cc已经到16的倍数
         则当前cc的当前字的四个字节 进行字循环 然后再进行字节替换 然后再进行轮常量异或
         将修改后的当前字四个字节 与前一行的 第一个字的 四个字节进行异或后 给到下一行的第一个新字
         
         如果 当前cc不是16的倍数
         直接将当前字的四个字节 与 与其相隔16个字节的字的四个字节异或后 给到新行的下一个新字
         */
        ctx->ksch[cc + 0] = ctx->ksch[tt + 0] ^ t0;
        ctx->ksch[cc + 1] = ctx->ksch[tt + 1] ^ t1;
        ctx->ksch[cc + 2] = ctx->ksch[tt + 2] ^ t2;
        ctx->ksch[cc + 3] = ctx->ksch[tt + 3] ^ t3;
    }
    
    return 0;
    
}



void copy_block_copy_nn(void* dest,const void*src,size_t srclen)
{
    memcpy(dest,src,srclen);
    
}

return_type copy_aes_encrypt( const unsigned char in[N_BLOCK], unsigned char  out[N_BLOCK], const aes_context ctx[1] )
{
    /*
     宏定义
     gfm2_sb(x)
     gfm2_sbox[(x)]
     sb_data(f2)
     f2(x) ((x << 1) ^ (((x >> 7) & 1) * WPOLY))
     */
    if( ctx->rnd )
    {
        uint_8t s1[N_BLOCK], r;
        /*
         再进行迭代10轮之前
         
         在第一轮迭代之前，先将明文和原始密钥进行一次异或加密操作。
         最后将异或后的值給到s1 之后操作s1的数据
         */
       copy_copy_and_key( s1, in, ctx->ksch );
        
        for( r = 1 ; r < ctx->rnd ; ++r )
            
#if defined( VERSION_1 )
        {
            mix_sub_columns( s1 );
            add_round_key( s1, ctx->ksch + r * N_BLOCK);
        }
#else
        {   uint_8t s2[N_BLOCK];
            mix_sub_columns( s2, s1 );
            copy_and_key( s1, s2, ctx->ksch + r * N_BLOCK);
        }
#endif
        shift_sub_rows( s1 );
        copy_copy_and_key( out, s1, ctx->ksch + r * N_BLOCK );
    }
    else
        return -1;
    return 0;
    
}



static void copy_copy_and_key( void *d, const void *s, const void *k )
{
#if defined( HAVE_UINT_32T )
    ((uint_32t*)d)[ 0] = ((uint_32t*)s)[ 0] ^ ((uint_32t*)k)[ 0];
    ((uint_32t*)d)[ 1] = ((uint_32t*)s)[ 1] ^ ((uint_32t*)k)[ 1];
    ((uint_32t*)d)[ 2] = ((uint_32t*)s)[ 2] ^ ((uint_32t*)k)[ 2];
    ((uint_32t*)d)[ 3] = ((uint_32t*)s)[ 3] ^ ((uint_32t*)k)[ 3];
#elif 1
    ((uint_8t*)d)[ 0] = ((uint_8t*)s)[ 0] ^ ((uint_8t*)k)[ 0];
    ((uint_8t*)d)[ 1] = ((uint_8t*)s)[ 1] ^ ((uint_8t*)k)[ 1];
    ((uint_8t*)d)[ 2] = ((uint_8t*)s)[ 2] ^ ((uint_8t*)k)[ 2];
    ((uint_8t*)d)[ 3] = ((uint_8t*)s)[ 3] ^ ((uint_8t*)k)[ 3];
    ((uint_8t*)d)[ 4] = ((uint_8t*)s)[ 4] ^ ((uint_8t*)k)[ 4];
    ((uint_8t*)d)[ 5] = ((uint_8t*)s)[ 5] ^ ((uint_8t*)k)[ 5];
    ((uint_8t*)d)[ 6] = ((uint_8t*)s)[ 6] ^ ((uint_8t*)k)[ 6];
    ((uint_8t*)d)[ 7] = ((uint_8t*)s)[ 7] ^ ((uint_8t*)k)[ 7];
    ((uint_8t*)d)[ 8] = ((uint_8t*)s)[ 8] ^ ((uint_8t*)k)[ 8];
    ((uint_8t*)d)[ 9] = ((uint_8t*)s)[ 9] ^ ((uint_8t*)k)[ 9];
    ((uint_8t*)d)[10] = ((uint_8t*)s)[10] ^ ((uint_8t*)k)[10];
    ((uint_8t*)d)[11] = ((uint_8t*)s)[11] ^ ((uint_8t*)k)[11];
    ((uint_8t*)d)[12] = ((uint_8t*)s)[12] ^ ((uint_8t*)k)[12];
    ((uint_8t*)d)[13] = ((uint_8t*)s)[13] ^ ((uint_8t*)k)[13];
    ((uint_8t*)d)[14] = ((uint_8t*)s)[14] ^ ((uint_8t*)k)[14];
    ((uint_8t*)d)[15] = ((uint_8t*)s)[15] ^ ((uint_8t*)k)[15];
#else
    block_copy(d, s);
    xor_block(d, k);
#endif
}



















