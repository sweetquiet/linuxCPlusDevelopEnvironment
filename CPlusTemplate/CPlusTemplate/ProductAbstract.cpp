//
//  ProductAbstract.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/1.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include "ProductAbstract.hpp"



#include <iostream>

using namespace std;

ProductAbstractA::ProductAbstractA() {
    /*
     怪物小兵 抽象
     */
    
    cout<<"小兵抽象构造"<<endl;
}
ProductAbstractA::~ProductAbstractA() {
    
    cout<<"小兵抽象析构造"<<endl;
}
ProductAbstractB::ProductAbstractB() {
    /*
     怪物坦克 抽象
     */
    cout<<"坦克抽象构造"<<endl;
}
ProductAbstractB::~ProductAbstractB() {
    cout<<"坦克抽象析构造"<<endl;
}
ProductA1::ProductA1() {

    cout<<"ProductA1..."<<endl;
    cout<<"小兵A1初级构造"<<endl;
    
}
ProductA1::~ProductA1() {
    
     cout<<"小兵A1初级析构造"<<endl;
    
}
ProductA2::ProductA2() {

    cout<<"小兵A2中级构造"<<endl; cout<<"ProductA2..."<<endl;
    
    
}
ProductA2::~ProductA2() {
    
     cout<<"小兵A2中级构造"<<endl;
    
}


ProductB1::ProductB1()
{
    
     cout<<"ProductB1..."<<endl;
    cout<<"坦克B1初级构造"<<endl;
    
}

ProductB1::~ProductB1() {
    cout<<"坦克B1初级析构造"<<endl;
}
ProductB2::ProductB2() {
    cout<<"ProductB2..."<<endl;
    cout<<"坦克B2中级构造"<<endl;
    
}
ProductB2::~ProductB2() {
    cout<<"坦克B2中级析构造"<<endl;
    
}


