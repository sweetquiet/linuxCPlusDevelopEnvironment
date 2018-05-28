//
//  Prototype.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <iostream>
#include "Prototype.hpp"

using namespace std;

Prototype::Prototype()
{
    
    cout<<"prototype构造函数"<<endl;
    
}

Prototype::~Prototype()
{
    
    cout<<"prototype析构造函数"<<endl;
}


Prototype* Prototype::Clone() const
{
    
    return 0;
    
}

ConcretePrototype::ConcretePrototype()
{
    
    cout<<"Concreteprototype 无参构造函数"<<endl;
}

ConcretePrototype::~ConcretePrototype()
{
    cout<<"Concreteprototype析构函数"<<endl;
    
    
}

ConcretePrototype::ConcretePrototype(const ConcretePrototype&cp){
    
    cout<<"Concreteprototype有参构造函数 用于原型复制 模式"<<endl;
    
    cout<<"ConcretePrototype copy..."<<endl;
}



Prototype* ConcretePrototype::Clone() const
{
    
    
    return new ConcretePrototype(*this);

}












