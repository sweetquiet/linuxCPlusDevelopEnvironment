//
//  DataQianTao.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/5/29.
//  Copyright © 2018年 admindyn. All rights reserved.
//


#include <iostream>
#include <cstring>
#include "DataQianTao.hpp"
using namespace std;
/*
 构造函数的特点：
 
 1.是一个特殊的成员函数；
 
 2.名字与类名相同；
 
 3.有初始化列表；
 
 4.创建类类型对象时，由编译器自动调用，在对象的声明周期内只调用一次；
 
 5.构造函数可以重载，实参决定了调用哪个函数；
 
 6.无参构造函数和带有缺省值得构造函数都认为是缺省构造函数，并且缺省构造函数只能有一个；
 
 7.如果没有显示定义构造函数时，编译器会提供一个默认的构造函数；（不一定，有一定的条件）
 
 */


DataQianTaoStr::DataQianTaoStr(const char* buf)
{
    
    if (!buf) {
        rep = new Srep("");
    }else {
        rep = new Srep(buf);
    }
}
/*
 拷贝构造函数
 
 1.只有单个形参，而且该形参是对本类型对象的引用（常用const修饰）；
 
 2.是构造函数的重载；
 
 3.拷贝构造函数是特殊的构造函数，创建对象时使用已存在的同类对象来进行初始化，由编译器自动调用。也就是说，当用一个本类类型对象来初始化一个变量时，编译器会自动调用拷贝构造函数
 */

//noexcept

DataQianTaoStr::DataQianTaoStr(const DataQianTaoStr& s){
    
    rep = s.rep;
    rep->count++ ;
    
}

DataQianTaoStr::~DataQianTaoStr()
{
    
    if (--rep->count <= 0) {
        delete rep;
    }
    
}

DataQianTaoStr::Srep::Srep(const char* s)
{
    // 类存储 真正的内存开辟
    
    strcpy(rep = new char[strlen(s)+1],s);
    
    count = 1;
}


DataQianTaoStr::Srep::~Srep()
{
    // 类 释放真正的存储数据的内存区
    
    delete [] rep;
    
}



















