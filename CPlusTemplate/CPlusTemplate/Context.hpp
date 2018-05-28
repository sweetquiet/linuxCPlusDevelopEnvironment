//
//  Context.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef Context_hpp
#define Context_hpp

#include "State.hpp"
#include <stdio.h>


class State;

class Context {
    
    
public:
    Context();
    
    Context(State* state);
    
    
    ~Context();
    
    void operationInterface();
    
    void operationChangeState();
    
protected:
private:
    friend class State; //表明在 State 类中可以访问 Context 类的 private 字段
    
    bool changeState(State* state);
    
private:
    
    State* _state;
    
    
};








#endif /* Context_hpp */
