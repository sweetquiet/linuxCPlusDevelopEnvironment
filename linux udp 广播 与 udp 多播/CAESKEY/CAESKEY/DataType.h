//
//  DataType.h
//  CAESKEY
//
//  Created by admindyn on 2018/6/13.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef DataType_h
#define DataType_h

#define N_ROW                   4
#define N_COL                   4
#define N_BLOCK   (N_ROW * N_COL)
#define N_MAX_ROUNDS           14

typedef unsigned char uint_8t;

typedef uint_8t return_type;

/*  Warning: The key length for 256 bit keys overflows a byte
 (see comment below)
 */

typedef uint_8t length_type;

typedef struct
{   uint_8t ksch[(N_MAX_ROUNDS + 1) * N_BLOCK];
    uint_8t rnd;
} aes_context;

#endif /* DataType_h */
