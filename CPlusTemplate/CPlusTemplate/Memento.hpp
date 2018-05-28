//
//  Memento.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef Memento_hpp
#define Memento_hpp

#include "Originator.hpp"
#include <stdio.h>

class Memento {
    
    
public:
protected:
private:
    /*
     这是最关键的地方 将originator
     为friend类 可以访问内部信息 但是其他类不能访问
     */
    
    
    friend class Originator;
    
    typedef string StateStr;
    
    Memento();
    
    Memento(const StateStr& sdt);
    
    ~Memento();
    
    void setState(const StateStr&sdt);
    
    StateStr getState();
    
private:
    StateStr _sdt;
};


































#endif /* Memento_hpp */
