//
//  Subject.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef Subject_hpp
#define Subject_hpp



#include <list>

#include <string>

#include <stdio.h>

using namespace std;

typedef string StateStr;

class Observer;

class Subject {
    
    
public:
    
    virtual ~Subject();
    
    virtual void Attach(Observer* obv);
    
    virtual void Detach(Observer* obv);
    
    virtual void Notify();
    
    virtual StateStr getState() = 0;
    
protected:
    Subject();
private:
    list<Observer*>* _obvs;
    
    
    
    
};


class ConcreteSubject:public Subject {
    
    
public:
    ConcreteSubject();
    ~ConcreteSubject();
    
    StateStr getState();
    
    void setState(const StateStr& st);
protected:
private:
    StateStr _st;
};








#endif /* Subject_hpp */
