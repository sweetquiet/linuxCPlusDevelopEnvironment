//
//  DataDynamicCast.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/5/28.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <iostream>
#include "DataDynamicCast.hpp"

using namespace std;

DataDynamicCast::DataDynamicCast()
{
    
}

DataDynamicCast::~DataDynamicCast()
{
    
    
}

void DataDynamicCast::changeV(DataDynamicCast &d)
{
    
    d.value = 200;
}

void DataDynamicCast::cpV(const DataDynamicCast &d)
{
    
/*
 error
 
 const_cast<DataDynamicCast*>(d)->value = 200;
 */
}

void DataDynamicCast::calcuate()
{
    this->value = 200;
    const_cast<DataDynamicCast*>(this)->value = 200;
    
    
}

void DataDynamicCast::printV(DataDynamicCast &d) const
{
    cout.setf(ios::dec,ios::basefield);
    cout<<d.value<<endl;
    
}







