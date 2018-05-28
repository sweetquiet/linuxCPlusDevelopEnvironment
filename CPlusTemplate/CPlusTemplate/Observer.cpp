//
//  Observer.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//
#include <iostream>



#include "Subject.hpp"

#include "Observer.hpp"

using namespace std;


Observer::Observer()
{
    
    _st = '\0';
    
    cout<<"Observer 构造函数 "<<endl;
}


Observer::~Observer()
{
    cout<<"Observer 析构造函数 "<<endl;
    
}



ConcreteObserverA::ConcreteObserverA(Subject* sub)
{
    _sub = sub;
    
    _sub->Attach(this);
    
}


ConcreteObserverA::~ConcreteObserverA()
{
    
    _sub->Detach(this);
    
    if (_sub != 0) {
        delete _sub;
    }
    
}


Subject* ConcreteObserverA::getSubject()
{
    
    return _sub;
}

void ConcreteObserverA::printInfo()
{
    
    cout<<"ConcreteObserverA observer..."<<_sub->getState()<<endl;
}

void ConcreteObserverA::update(Subject *sub)
{
    
    _st = sub->getState();
    
    
    printInfo();
    
}




ConcreteObserverB::ConcreteObserverB(Subject* sub)
{
    _sub = sub;
    
    _sub->Attach(this);
    
}


ConcreteObserverB::~ConcreteObserverB()
{
    
    _sub->Detach(this);
    
    if (_sub != 0) {
        delete _sub;
    }
    
}


Subject* ConcreteObserverB::getSubject()
{
    
    return _sub;
}

void ConcreteObserverB::printInfo()
{
    
    cout<<"ConcreteObserverB observer..."<<_sub->getState()<<endl;
}

void ConcreteObserverB::update(Subject *sub)
{
    
    _st = sub->getState();
    
    
    printInfo();
    
}




















