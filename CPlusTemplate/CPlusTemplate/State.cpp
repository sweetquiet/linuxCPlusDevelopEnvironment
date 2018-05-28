//
//  State.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <iostream>
#include "State.hpp"
#include "Context.hpp"

using namespace std;

State::State()
{
    
    cout<<"State构造函数"<<endl;
    
}

State::~State()
{
    
    cout<<"State析构函数"<<endl;
    
}

void State::operationInterface(Context *con){
    
    cout<<"State::.."<<endl;

}


bool State::changeState(Context *con, State *st)
{
    
    con->changeState(st);
    
    return true;
    
}


void State::operationChangeState(Context *con){
    
    
}


ConcreteStateA::ConcreteStateA()
{
    cout<<"ConcreteStateA构造函数"<<endl;
    
}

ConcreteStateA::~ConcreteStateA()
{
    cout<<"ConcreteStateA析构函数"<<endl;
    
}

void ConcreteStateA::operationChangeState(Context *con){
    
    
    
    operationInterface(con);
    
    this->changeState(con, new  ConcreteStateB());
    
    
}

void ConcreteStateA::operationInterface(Context *con)
{
    cout<<"ConcreteStateA::operationInterface..."<<endl;
    
}




ConcreteStateB::ConcreteStateB()
{
    
     cout<<"ConcreteStateB构造函数"<<endl;
    
}

ConcreteStateB::~ConcreteStateB()
{
    
    cout<<"ConcreteStateB析构造函数"<<endl;
    
}

void ConcreteStateB::operationChangeState(Context *con){
    
    
    
    operationInterface(con);
    
    this->changeState(con, new  ConcreteStateA());
    
    
}

void ConcreteStateB::operationInterface(Context *con)
{
    cout<<"ConcreteStateB::operationInterface..."<<endl;
    
}





























