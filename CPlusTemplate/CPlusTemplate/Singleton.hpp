//
//  Singleton.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/1.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef Singleton_hpp
#define Singleton_hpp

#include <stdio.h>


class Singleton {
    
    
public:
    static Singleton* Instance();
    ~Singleton();
protected:
    Singleton();

private:
    static Singleton* _instance;
    
    
};


#endif /* Singleton_hpp */
