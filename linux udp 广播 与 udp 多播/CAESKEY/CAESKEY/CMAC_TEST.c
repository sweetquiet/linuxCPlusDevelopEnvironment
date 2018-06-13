//
//  CMAC_TEST.c
//  CAESKEY
//
//  Created by admindyn on 2018/6/7.
//  Copyright © 2018年 admindyn. All rights reserved.
//
#include "aes.h"
#include "cmac.h"
#include "CMAC_TEST.h"

uint8_t MAC[16];
uint8_t MACKey[16];
uint8_t k1[16];
uint8_t k2[16];

typedef struct
{   uint_8t ksch[(N_MAX_ROUNDS + 1) * N_BLOCK];
    uint_8t rnd;
} AES_CMAC_CONTEXT;

void leftshift(int len,uint8_t*add,uint8_t*des)
{
    int i;
    for (i=0; i<len-1; i++) {
        des[i]=(add[i]<<1)+(add[i+1]>=0x80?1:0);
    }
    des[len-1] = add[len-1]<<1;
}

void ArrayXor(int len,uint8_t*a1,uint8_t*a2,uint8_t*des)
{
    int i;
    
    for (i=0; i<len; i++) {
        des[i] = a1[i]^a2[i];
    }
}

void LoadMacKey(uint8_t*key)
{
    int i;
    uint8_t plain[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t Rb[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87 };
    uint8_t c0[16];
    for (i=0; i<16; i++) {
        MACKey[i] = key[i];//setMacKey
    }
    AES_CMAC_CONTEXT aes;
   
    
}

void testCMAC(void)
{
    
    
}





