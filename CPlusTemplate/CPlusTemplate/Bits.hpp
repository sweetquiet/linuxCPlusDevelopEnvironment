//
//  Bits.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/5/25.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef Bits_hpp
#define Bits_hpp
#include <assert.h>
#include <set>
#include <map>
#include <vector>
#include <malloc/malloc.h>
#include <limits.h>
#include <stdio.h>

/*选取整型做基*/
typedef unsigned int Block;


/*一些执行的细节*/
#define BLKSIZ (CHAR_BIT* sizeof(Block))
/*一些执行的细节 这里保证每次设置 的 位置 整数 取余 保证 永远不会超出这个范围*/
#define offset(b) (b%BLKSIZ)

#define mask1(b) ((Block)1 << offset(b))

#define mask0(b) (~mask1(b))

/*
 数据结构
 */

typedef struct bits
{
    size_t nbits;/*位数*/
    Block* bits;/*基数组*/
    size_t nblks; /*基数组中的块数*/
    Block clean_mask; /*用来隐藏不常使用的位 */
}Bits;

/*
 私有函数
 */

static size_t word(const Bits*bp,size_t bit)
{
    return  bp->nblks - 1 - bit/BLKSIZ;
}

static void set(Bits* bp,size_t b)
{
    bp->bits[word(bp, b)] |= mask1(b);
    
}

static void reset(Bits* bp,size_t b)
{
    bp->bits[word(bp, b)] &= mask0(b);
    
}
static void toggle(Bits* bp,size_t b)
{
    bp->bits[word(bp, b)] ^= mask1(b);
    
}


static int test(const Bits* bp,size_t b)
{
    return  !!(bp->bits[word(bp, b)]& mask1(b));
    
}

static size_t count_block(Block n)
{
    size_t sum = 0;
    
    while (n) {
        if (n&(Block)1) {
            ++sum;
        }
        n >>= 1;
    }
    
    return  sum;
    
}


static void cleanup(Bits*bp)
{
    
    if (bp->nbits % BLKSIZ) {
        bp->bits[0] &= bp->clean_mask;
        
    }
}

/*
 公有接口的执行在这里开始
 */

Bits* bits_create(size_t nbits)
{
    Bits* bp = (Bits*)malloc(sizeof(Bits));
    
    size_t nbytes;
    
    if (bp == NULL) {
        return NULL;
    }
    /*
     分配基数组
     */
    
    bp->nblks = (nbits + BLKSIZ - 1)/BLKSIZ;
    
    nbytes = bp->nblks * sizeof(Block);
    
    bp->bits = (Block*)malloc(nbytes);
    
    if (bp->bits == NULL) {
        free(bp);
        return  NULL;
    }
    
    memset(bp->bits, '\0', nbytes);
    bp->nbits = nbits;
    
    bp->clean_mask = ~(Block)0 >> (bp->nblks* BLKSIZ - nbits);
    
    return bp;
    
}


unsigned bits_to_uint(const Bits* bp)
{
    
    size_t nblks = sizeof(unsigned) /sizeof(Block);
    
    
    if (nblks>1) {
        int i;
        
        unsigned n = bp->bits[bp->nblks - nblks];
        
        /*
         集中 low -order 子块 到一个无符号数
         */
        
        
        
        if (nblks > bp->nblks) {
            nblks = bp->nblks;
        }
        
        
        while (--nblks) {
            n = (n<<BLKSIZ)|bp->bits[bp->nblks - nblks];
        }
        
        return n;
        
    }else
    {
        
        return (unsigned) bp->bits[bp->nblks - 1];
    }
    
    
    
}



Bits* bits_from_uint(Bits*bp,unsigned n)
{
    size_t nblks = sizeof(unsigned)/sizeof(Block);
    
   
    assert(bp);
    
    memset(bp->bits, '\0', bp->nblks* sizeof(Block));
    
    if (nblks>1) {
        int i;
        
        if (nblks > bp->nblks) {
            nblks = bp->nblks;
        }
        
        for (i=1; i<= nblks; ++i) {
            bp->bits[bp->nblks - i] = (Block)n;
            
            n>>= BLKSIZ;
        }
    }else
    {
        
        bp->bits[bp->nblks - 1] = n;
    }
    
    
    return  bp;
    
    
}


Bits* bits_set(Bits*bp,size_t bit)
{
    
    assert(bp&& (bit< bp->nbits));
    
    set(bp, bit);
    
    return bp;
    
}



Bits* bits_set_all(Bits* bp)

{
    
    assert(bp);
    
    
    memset(bp->bits, ~0u, bp->nblks* sizeof(Block));
    
    cleanup(bp);
    
    return bp;
    
}
Bits*  bits_reset(Bits* bp,size_t bit)
{
    
    assert(bp&&(bit < bp->nbits));
    
    reset(bp, bit);
    
    return bp;
}

Bits* bits_reset_all(Bits * bp)
{
    assert(bp);
    
    memset(bp->bits, '\0', bp->nblks*sizeof(Block));
    
    return bp;
    
}

Bits* bits_toggle(Bits* bp,size_t bit)
{
    
    assert(bp&&(bit< bp->nbits));
    
    toggle(bp,bit);
    
    return bp;
}

Bits* bits_toggle_all(Bits* bp)
{
    size_t nw;
    
    assert(bp);
    
    nw = bp->nblks;
    
    
    while (nw--) {
        bp->bits[nw] = ~bp->bits[nw];
    }
    
    cleanup(bp);
    
    
    return bp;
    
}

int bits_test(const Bits* bp,size_t bit)
{
    
    assert(bp&&(bit < bp->nbits));
    
    return test(bp, bit);
    
    
}


int bits_any(const Bits* bp)
{
    
    int i;
    
    assert(bp);
    
    for (i=0; i<bp->nblks; ++i) {
        if (bp->bits[i]) {
            return 1;
        }
    }
    
    return 0;
    
}
size_t bits_count(const Bits* bp)
{
    
    int i;
    
    size_t sum;
    
    
    assert(bp);
    
    
    for (i=0,sum = 0;i<bp->nblks ; ++i) {
        sum += count_block(bp->bits[i]);
    }
    
    
    return  sum;
    
}

Bits* bits_put(Bits* bp,FILE* f)
{
    int i;
    
    assert(bp);
    
    for (i=0; i<bp->nbits; ++i) {
        fprintf(f,"%d",bits_test(bp, bp->nbits-1-i));
    }
    
    return bp;
    
}

Bits* bits_get(Bits*bp,FILE*f)
{
    char* buf;
    
    char format[9];
    
    /*
     全部复位
     */
    
    assert(bp);
    
    
    bits_reset_all(bp);
    
    /*
     分配字符缓冲器
     */
    
    buf = (char*)malloc(bp->nbits+1);
    
    
    if (buf == NULL) {
        return 0;
    }
    
    /*
     创建 读格式
     */
    
    sprintf(format, "%%%d[01]",bp->nbits);
    
    if (fscanf(f, format,buf)==1) {
        int i;
        
        size_t slen = strlen(buf);
        
        
        /*
         在bitset中设置相应的位
         */
        
        
        for (i=0; i<slen; ++i) {
            if (buf[slen-1-i]=='1') {
                bits_set(bp, i);
            }
        }
        
        
    }
    
    free(buf);
    
    return bp;
    
}

void bits_destroy(Bits* bp)
{
    assert(bp);
    
    free(bp->bits);
    
    free(bp);
    
}



#endif /* Bits_hpp */
