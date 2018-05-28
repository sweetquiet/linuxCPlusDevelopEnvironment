//
//  Director.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include "Director.hpp"

Director::Director(Builder* bld)
{
    cout<<"Director 构造 函数"<<endl;
    _bld = bld;
    
}


Director::~Director()
{
    
    cout<<"Director 析构函数"<<endl;
    
}

void Director::construct()
{
      _bld->buildPartA("user-defined");
      _bld->buildPartB("user-defined");
      _bld->buildPartC("user-defined");
    
    
}





