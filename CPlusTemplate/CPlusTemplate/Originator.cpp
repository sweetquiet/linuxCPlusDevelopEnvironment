//
//  Originator.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include "Memento.hpp"
#include <iostream>
#include "Originator.hpp"

using namespace std;
typedef string StateStr;

Originator::Originator()
{
    _sdt = "";
    
    _mt = 0 ;
    
}


Originator::Originator(const StateStr&sdt)
{
    _sdt = sdt;
    
    _mt = 0;
    
}

Originator::~Originator()
{
    
    
}

Memento* Originator::createMemento()
{
    return new Memento(_sdt);
    
}


StateStr Originator::getState()
{
    
    return _sdt;
    
}


void Originator::setState(const StateStr &sdt)
{
    
    _sdt = sdt;
    
}

void Originator::printState()
{
    
    cout<<this->_sdt<<"......"<<endl;
    
}

void Originator::setMemento(Memento *men)
{
    
    
}

void Originator::restoreToMemento(Memento *mt)
{
    
    this->_sdt = mt->getState();
    
}
























