//
//  Date.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/5/29.
//  Copyright © 2018年 admindyn. All rights reserved.
//


#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdio>
#include "Date.hpp"

using namespace std;

//必须在类定义外初始化静态成员

int Date::dtab[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};


Date::Date()
{
    //获得今天的日期
    
    time_t tval = time(0);
    
    struct tm* tmp = localtime(&tval);
    
    _month = tmp->tm_mon + 1;
    
    _day = tmp->tm_mday;
    
    _year = tmp->tm_year + 1900;
    
    
    
}

Date::operator string() const
{
    char buf[9];
    
    sprintf(buf, "%04d%02d%02d",_year,_month,_day);
    
    return string(buf);
    
}

























