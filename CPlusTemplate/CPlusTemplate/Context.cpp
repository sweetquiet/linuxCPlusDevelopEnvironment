//
//  Context.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <iostream>
#include "Context.hpp"

using namespace std;

Context::Context()
{
    
   
    cout<<"Context无参 构造函数"<<endl;
    
}

Context::Context(State* state)
{
    
    cout<<"Context有参 构造函数"<<endl;
    this->_state = state;
}

Context::~Context()
{
    cout<<"Context析构造函数"<<endl;
    delete _state;
}

void Context::operationInterface()
{
    
    _state->operationInterface(this);
    
    
}

bool Context::changeState(State *state){
  
    /*这里 应该有内存泄漏*/
    
    this->_state = state;
    
    
    return true;
    
}


void Context::operationChangeState()
{
    _state->operationChangeState(this);
    
}

















