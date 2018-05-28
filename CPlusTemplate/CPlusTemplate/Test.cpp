//
//  Test.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/1.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <stdio.h>
#include "Bits.hpp"
#include "Test.hpp"
#define NBITS 36

void Test::funcBits()
{
    
    int i ;
    
    unsigned int n;
    
    Bits* bp = bits_create(NBITS);
    
    assert(bp);
    
    /*
     将偶数位置位
     */
    
    for (i=0; i<NBITS; i+=2) {
        bits_set(bp, i);
    }
    
    bits_put(bp, stdout);
    
    printf("(%d)\n",bits_count(bp));
    
    
    /*
     高位 取反 （上面的一半）
     */
    
    
    for (i=NBITS/2; i<NBITS; ++i) {
        bits_toggle(bp, i);
    }
    
    bits_put(bp, stdout);
    
    printf("(%d)\n",bits_count(bp));
    
    /*
     复数低位（下面的一半）
     */
    
    for (i=0; i<NBITS/2; ++i) {
        bits_reset(bp, i);
    }
    
    bits_put(bp, stdout);
    
    printf("(%d)\n",bits_count(bp));
    
    /*读一个位字符串*/
    
    fputs("Enter a bit string:", stderr);
    
    bits_put(bits_get(bp, stdin), stdout);
    
    printf("(%d)\n",bits_count(bp));
    
    /*
     无符号数之间的转换
     */
    
    
    n = bits_to_uint(bp);
    
    printf("n:%u\n",n);
    
    bp = bits_from_uint(bp, n);
    
    bits_put(bp, stdout);
    
    printf("(%d)\n",bits_count(bp));
    
    /*测试any()和 test()*/
    
    
    printf("any? %d\n",bits_any(bp));
    
    
    printf("test(0)?%d\n",bits_test(bp, 0));
    
    /*
     取反并复位
     */
    
    
    bits_put(bits_toggle_all(bp), stdout);
    printf("(%d)\n",bits_count(bp));
    
    bits_put(bits_reset_all(bp), stdout);
    
    printf("(%d)\n",bits_count(bp));
    
    bits_put(bits_set_all(bp), stdout);
    printf("(%d)\n",bits_count(bp));
    
    bits_destroy(bp);
}


void Test::funcTest()
{
    typedef unsigned int word;
    
    typedef unsigned char byte;
    
    byte a = 0x55;
    byte b = 0xf0;
    
    cout<< "a|b == " <<setw(2)<<word(a|b)<<endl;
    cout<<"a&b == "<<setw(2)<<word(a&b)<<endl;
    cout<<"a^b == "<<setw(2)<<word(a^b)<<endl;
    
    cout<<"~a == "<<setw(2)<<word(byte(~a))<<endl;
    
    cout<<"a << 1 == "<<setw(2)<< word(a<<1) <<endl;
    
    cout<<"b >> 6 == "<<setw(2) << word(a>>6)<<endl;
    
    
}




void Test::funcBitMask()
{
    BitMask b;
    
    cout.setf(ios::boolalpha);
cout.setf(ios::hex,ios::basefield);
    
    b.set(1);
    //0x10
    cout<< b <<endl;
    b.set(3);
    //0x1010
    cout<< b <<endl;
    
    b.reset(1);
    //0x1000
    cout<< b <<endl;
    //false
    cout<< b.test(1) <<endl;
     cout<< b.test(2) <<endl;
     cout<< b.test(3) <<endl;
    
    b |= BitMask(0xabcdef00);
    
    cout << b << endl;
    
    //以二进制形式打印全部的bitmask
    
    for (int i=b.size()-1; i>=0; --i) {
        cout<< (b.test(i)?"1":"0");
    }
    cout<<endl;
}



