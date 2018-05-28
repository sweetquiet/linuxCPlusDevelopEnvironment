//
//  Subject.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include "Observer.hpp"
#include "Subject.hpp"
#include <iostream>

using namespace std;

Subject::Subject()
{
    cout<<"Subject 构造函数 "<<endl;
    //在模版使用之前一定要new 创建
    _obvs = new list<Observer*>;
}

Subject::~Subject()
{
    cout<<"Subject 析构造函数 "<<endl;
}

void Subject::Attach(Observer *obv)
{
    _obvs->push_front(obv);
    
    
}

void Subject::Detach(Observer *obv)
{
    
    if (obv != NULL) {
        _obvs->remove(obv);
    }
    
}


void Subject::Notify()
{
    
    list<Observer*>::iterator it;
    
    it = _obvs->begin();
    
    for (; it != _obvs->end(); it++) {
        //关于模版 与 iterator的用法
        
        /*
         dynamic_cast<Observer *>
         */
        
        (*it)->update(this);
        
        
    }
}


ConcreteSubject::ConcreteSubject()
{
    
    cout<<"ConcreteSubject 构造函数 "<<endl;
    _st =  '\0' ;
    
}

ConcreteSubject::~ConcreteSubject()
{
    cout<<"ConcreteSubject 析构造函数 "<<endl;
    
}

StateStr ConcreteSubject::getState()
{
    
    return  _st;
    
    
}

void ConcreteSubject::setState(const StateStr &st)
{
    
    _st = st;
    
}























