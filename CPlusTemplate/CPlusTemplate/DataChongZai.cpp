//
//  DataChongZai.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include "DataChongZai.hpp"

using namespace std;

void DataChongZai::print(double f)
{
    
    cout << "Printing float: " << f << endl;
}

void DataChongZai::print(char *c)
{
    cout << "Printing character: " << c << endl;
    
}

void DataChongZai::print(int i)
{
    cout << "Printing int: " << i << endl;
}

DataChongZai::DataChongZai()
{
    
    
}

double DataChongZai::getVolume()
{
    return length*height*breadth;
    
}

void DataChongZai::setLength(double len)
{
    
    length = len;
    
}

void DataChongZai::setBreadth(double bre)
{
    breadth = bre;
    
}

void DataChongZai::setHeight(double hei)
{
    
    height = hei;
    
    
}

double DataChongZai::getHeight()
{
    return  height;
}
double DataChongZai::getLength()
{
    return length;
}

double DataChongZai::getBreadth()
{
    return breadth;
}
/*
 通常我们都将其声明为友元函数，因为大多数时候重载运算符要访问类的私有数据，（当然也可以设置为非友元非类的成员函数。但是非友元又不是类的成员函数是没有办法直接访问类的私有数据的），
 对于成员函数来说，一个操作数通过this指针隐式的传递，（即本身），另一个操作数作为函数的参数显示的传递；对于友元函数（非成员函数）两个操作数都是通过参数来传递的。
 我们这里 要用 this 就要用成员函数
 
相加函数，如果没有friend修饰则只许有一个右侧参数
 如果是friend 友元方式就要两个参数
 1、运算符的操作需要修改类对象的状态，则使用成员函数。如需要做左值操作数的运算符（如=，+=，++）
 
 2、运算时，有数和对象的混合运算时，必须使用友元
 
 3、二元运算符中，第一个操作数为非对象时，必须使用友元函数。如输入输出运算符<<和>>
 一般按const引用来传递(若是使用成员函数重载，函数也为const).
 
 对于返回数值的决定:
 
 1) 如果返回值可能出现在=号左边, 则只能作为左值, 返回非const引用。
 
 2) 如果返回值只能出现在=号右边, 则只需作为右值, 返回const型引用或者const型值。
 
 3) 如果返回值既可能出现在=号左边或者右边, 则其返回值须作为左值, 返回非const引用
 由于+ -都是出现在=号的右边，如c=a+b，即会返回一个右值，可以返回const型值
 */

 DataChongZai operator+(const DataChongZai& a,const DataChongZai& b)
{
    
        DataChongZai obj ;
   
    obj.setLength(b.length+a.length);
    
    obj.setBreadth(b.breadth+a.breadth);
    
    obj.setHeight(b.height+a.height);
    
    
    return obj;
    
    
}

/*
 拷贝构造函数和赋值运算符的行为比较相似，都是将一个对象的值复制给另一个对象；但是其结果却有些不同，拷贝构造函数使用传入对象的值生成一个新的对象的实例，而赋值运算符是将对象的值复制给一个已经存在的实例。这种区别从两者的名字也可以很轻易的分辨出来，拷贝构造函数也是一种构造函数，那么它的功能就是创建一个新的对象实例；赋值运算符是执行某种运算，将一个对象的值复制给另一个对象（已经存在的）。调用的是拷贝构造函数还是赋值运算符，主要是看是否有新的对象实例产生。如果产生了新的对象实例，那调用的就是拷贝构造函数；如果没有，那就是对已有的对象赋值，调用的是赋值运算符。
 
 在默认情况下（用户没有定义，但是也没有显式的删除），编译器会自动的隐式生成一个拷贝构造函数和赋值运算符。但用户可以使用delete来指定不生成拷贝构造函数和赋值运算符，这样的对象就不能通过值传递，也不能进行赋值运算。
 */

DataChongZai::~DataChongZai()
{
    
}






