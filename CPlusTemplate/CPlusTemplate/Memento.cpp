//
//  Memento.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <iostream>
#include "Memento.hpp"
using namespace std;

typedef string StateStr;

Memento::Memento()
{
    cout<<"Memento无参数构造函数"<<endl;
}

Memento::Memento(const StateStr& sdt)
{
    cout<<"Memento有参数构造函数"<<endl;
    _sdt = sdt;
    
}

Memento::~Memento()
{
    cout<<"Memento析构造函数"<<endl;
    
}

StateStr Memento::getState()
{
    /*
     备忘录类 返回备忘录记录的类的状态信息
     */
       cout<<" 备忘录类 返回备忘录记录的类的状态信息"<<endl;
    return _sdt;
}

void Memento::setState(const StateStr &sdt)
{
     cout<<" 备忘录类 更新备忘录记录的类的状态信息"<<endl;
    _sdt = sdt;
}




















