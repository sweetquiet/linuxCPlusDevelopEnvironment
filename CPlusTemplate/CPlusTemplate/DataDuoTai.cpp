//
//  DataDuoTai.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <iostream>

#include <stdio.h>

#include "DataDuoTai.hpp"

using namespace std;

/*
 多态按字面的意思就是多种形态。当类之间存在层次结构，并且类之间是通过继承关联时，就会用到多态。
 C++ 多态意味着调用成员函数时，会根据调用函数的对象的类型来执行不同的函数。
 */
/*
 在声明函数时指定了默认参数
 在定义函数的时候可以不指定默认参数
 */
/*
 冒号后 添加初始化列表
 */
DataDuoTai::DataDuoTai(int a ,int b):width(a),height(b)
{
//    width =a;
//    height =b;
    
}

int DataDuoTai::area()
{
    
    cout<<"Parent class area:"<<endl;
    return 0;
}

DataDuoTai::~DataDuoTai()
{
    
    
}





