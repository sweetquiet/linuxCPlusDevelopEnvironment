//
//  Originator.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef Originator_hpp
#define Originator_hpp

#include <stdio.h>
#include <string>

using namespace std;


class Memento;


class Originator {
    
    
public:
    typedef string StateStr;
    
    Originator();
    
    Originator(const StateStr& sdt);
    
    ~Originator();
    
    Memento* createMemento();
    
    void setMemento(Memento* men);
    
    void restoreToMemento(Memento* mt);
    
    StateStr getState();
    
    void setState(const StateStr&sdt);
    
    void printState();
    
protected:
private:
    StateStr _sdt;
    
    Memento* _mt;
    
    
};


























#endif /* Originator_hpp */
