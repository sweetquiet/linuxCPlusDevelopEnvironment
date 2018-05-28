//
//  Builder.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include "Builder.hpp"

Builder::Builder()
{
    
    cout<<"Builder 构造函数"<<endl;
    
}

Builder::~Builder()
{
    cout<<" Builder 析构"<<endl;
    
    
    
}

ConcreteBuilder::ConcreteBuilder()
{
    
    cout<<"ConcreteBuilder 构造函数"<<endl;
    
}

ConcreteBuilder::~ConcreteBuilder()
{
    
    cout<<"ConcreteBuilder 析构造函数"<<endl;
    
}


void ConcreteBuilder::buildPartA(const string &buildPara)
{
    
    cout<<"Step1:Build PartA.."<<buildPara<<endl;
    
}


void ConcreteBuilder::buildPartB(const string &buildPara)
{
    
    cout<<"Step2:Build PartB.."<<buildPara<<endl;
    
}

void ConcreteBuilder::buildPartC(const string &buildPara)
{
    
    cout<<"Step3:Build PartC.."<<buildPara<<endl;
    
}



ProductBuilder* ConcreteBuilder::getProduct()
{
    buildPartA("pre-defined");
    
    buildPartB("pre-defined");
    
    buildPartC("pre-defined");
    
    return new ProductBuilder;
    
    
}







