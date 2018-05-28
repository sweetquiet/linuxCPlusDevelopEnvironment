//
//  Director.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef Director_hpp
#define Director_hpp

#include "Builder.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;


class Director {
    
    
public:
    Director(Builder* bld);
    
    ~Director();
    
    void construct();
    
protected:
private:
    Builder* _bld;
    
};










#endif /* Director_hpp */
