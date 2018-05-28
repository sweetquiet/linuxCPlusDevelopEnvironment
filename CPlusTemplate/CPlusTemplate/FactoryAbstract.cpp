//
//  FactoryAbstract.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/1.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <iostream>
#include "FactoryAbstract.hpp"

using namespace std;
FactoryAbstract::FactoryAbstract() 
{
    
    cout<<"工厂抽象构造"<<endl;
}


FactoryAbstract::~FactoryAbstract()
{
    
    cout<<"工厂抽象析构造"<<endl;
    
    
}

ConcreteFactory1::ConcreteFactory1() {
    cout<<"初级怪物工厂抽象构造"<<endl;
}
ConcreteFactory1::~ConcreteFactory1() {
    cout<<"初级怪物工厂抽象析构造"<<endl;
}
/*
 初级工厂 生产小兵
 */
ProductAbstractA* ConcreteFactory1::createProductA() {
    cout<<"初级怪物工厂生产小兵初级"<<endl;
    return new ProductA1();
    
}
ProductAbstractB* ConcreteFactory1::createProductB() {
    /*
     初级工厂 生产坦克
     */
    cout<<"初级怪物工厂生产坦克初级"<<endl;
    
    return new ProductB1();
    
}
ConcreteFactory2::ConcreteFactory2() {
      cout<<"中级怪物工厂构造"<<endl;
}

ConcreteFactory2::~ConcreteFactory2() {
      cout<<"中级怪物工厂析构造"<<endl;
    
}
ProductAbstractA* ConcreteFactory2::createProductA() {
    
    /*
     中级工厂 生产小兵
     */
      cout<<"中级怪物工厂生产小兵中级"<<endl;
    return new ProductA2();
    
}

ProductAbstractB* ConcreteFactory2::createProductB() {
    
    /*
     中级工厂 生产坦克
     */
      cout<<"中级怪物工厂生产坦克中级"<<endl;
    
    return new ProductB2();
    
}



