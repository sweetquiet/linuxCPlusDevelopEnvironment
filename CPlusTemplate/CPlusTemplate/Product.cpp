
//
//  Product.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/1.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <iostream>
#include "Product.hpp"

using namespace std;

Product::Product()
{
    
    cout<<"Product构造函数"<<endl;
}



Product::~Product(){
    
    cout<<"Product析造函数"<<endl;
}




ConcreteProduct::ConcreteProduct()
{
    
    cout<<"ConcreteProduct构造函数"<<endl;
}



ConcreteProduct::~ConcreteProduct()
{
    cout<<"ConcreteProduct析构造函数"<<endl;
    
    
    
}

