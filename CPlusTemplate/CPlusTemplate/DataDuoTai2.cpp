//
//  DataDuoTai2.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include "DataDuoTai2.hpp"
using namespace std;

DataDuoTai2::DataDuoTai2(int a,int b)
{
    DataDuoTai(a,b);
    
}

int DataDuoTai2::area()
{
    cout << "DataDuoTai2 class area :" <<endl;
    return (width * height);
}

DataDuoTai2::~DataDuoTai2()
{
    
}









