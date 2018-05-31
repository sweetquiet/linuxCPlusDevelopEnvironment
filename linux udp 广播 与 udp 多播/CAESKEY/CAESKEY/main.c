//
//  main.c
//  CAESKEY
//
//  Created by admindyn on 2018/5/31.
//  Copyright © 2018年 admindyn. All rights reserved.
//
#include <string.h>
#include <stdbool.h>
#include <memory.h>
#include "aes.h"
#include <stdio.h>
#define LORA_KEY_LENGTH         16
#define LORA_MIC_LENGTH         4

#define LSHIFT(v, r) do {                                       \
int i;                                                  \
for (i = 0; i < 15; i++)                                \
(r)[i] = (v)[i] << 1 | (v)[i + 1] >> 7;         \
(r)[15] = (v)[15] << 1;                                 \
} while (0)

#define XOR(v, r) do {                                          \
int i;                                                  \
for (i = 0; i < 16; i++)     \
{    \
(r)[i] = (r)[i] ^ (v)[i]; \
}                          \
} while (0) \


#define MIN(a,b) (((a)<(b))?(a):(b))
int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
