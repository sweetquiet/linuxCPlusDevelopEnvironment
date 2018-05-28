//
//  DataClass.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include "DataClass.hpp"
using namespace std;


DataClass::DataClass()
{
    
}

void DataClass::setWidth(int w)
{
    width = w;
}

void DataClass::setHeight(int h)
{
    height = h;
}

DataClass::~DataClass()
{
    
    
}


int Rectangle::getArea()
{
    cout<<"面积输出:"<<(width *  height)<<endl;
    
    return (width *  height);
    
}


