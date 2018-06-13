//
//  AEST.h
//  CAESKEY
//
//  Created by admindyn on 2018/6/1.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef AEST_h
#define AEST_h


#include <stdio.h>
#include "aes.h"

#define LORA_KEY_LENGTH         16
#define LORA_MIC_LENGTH         4

typedef struct data_info {
    uint8_t datanonceApp[3];
    uint8_t datanonceDev[2];
    uint8_t datanonceNetID[3];
    uint8_t dataKeyKey[16];
}DATA_INFO;

void test(void);



void copy_aes_sesskeys(DATA_INFO* info);

return_type copy_aes_set_key(const unsigned char key[],length_type keylen,aes_context ctx[1]);

void copy_block_copy_nn(void* dest,const void*src,size_t srclen);



static void copy_copy_and_key( void *d, const void *s, const void *k );

















#endif /* AEST_h */
