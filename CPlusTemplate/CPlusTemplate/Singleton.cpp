//
//  Singleton.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/1.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <iostream>

#include "Singleton.hpp"

/*
 单列模式
 */

using namespace std;

Singleton* Singleton:: _instance = 0;

Singleton::Singleton()
{
    
    cout<<"Singleton构造函数" <<endl;
    
}

Singleton::~Singleton()
{
    
    cout<<"Singleton析构造函数" <<endl;
    
}

Singleton* Singleton::Instance()
{
    if (_instance == 0) {
        
        _instance = new Singleton();
        
    }
    
    return _instance;
    
    
}







