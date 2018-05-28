//
//  State.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#include "Context.hpp"
#include <stdio.h>

class Context;

class State {
    
    
public:
    State();
    
    virtual ~State();
    
    virtual void operationInterface(Context*) = 0;
    
    virtual void operationChangeState(Context*) = 0;
    
protected:
    bool changeState(Context* con,State* st);
    
private:
    
    
    
};



class ConcreteStateA:public State {
    
    
public:
    
    ConcreteStateA();
    
    virtual ~ConcreteStateA();
    
    
    virtual void operationInterface(Context*);
    
    virtual void operationChangeState(Context*) ;
    
    
protected:
private:
    
    
    
    
};



class ConcreteStateB:public State {
    
    
public:
    
    ConcreteStateB();
    
    virtual ~ConcreteStateB();
    
    
    virtual void operationInterface(Context*);
    
    virtual void operationChangeState(Context*) ;
    
    
protected:
private:
    
    
    
    
};





#endif /* State_hpp */
