//
//  define.h
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/9.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#ifndef define_h
#define define_h
#pragma pack(1)

struct Header{
    
    int num; //包id
    int index; //学生编号
};

struct PkgContent{
    char  sex;//性别
    int score;//分数
    char address[100];//地址
    
    int  age;
};

struct Pkg{
    Header head;
    PkgContent content;
};

#endif /* define_h */
