//
//  Facroty.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/1.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include "Product.hpp"

#include <iostream>

#include "Facroty.hpp"

using namespace std;

Factory::Factory() {
    
    cout<<"Factory构造函数"<<endl;
    
}
Factory::~Factory() {
    
    cout<<"Factory析构造函数"<<endl;
    
}
ConcreteFactory::ConcreteFactory() {
    
    cout<<"ConcreteFactory构造函数"<<endl;
    
    
}
ConcreteFactory::~ConcreteFactory() {
    
    cout<<"ConcreteFactory析构造函数"<<endl;
    
}

Product* ConcreteFactory::createProduct() {
    
    return new ConcreteProduct();
    
}
