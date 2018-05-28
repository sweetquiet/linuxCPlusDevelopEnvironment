//
//  DataClass.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef DataClass_hpp
#define DataClass_hpp

#include <stdio.h>


class DataClass {
    
    
public:
    
    void setWidth(int w);
    
    void setHeight(int h);
    
    DataClass();
    
    ~DataClass();
    
protected:
    int width;
    int height;
    
    
    
};


class Rectangle:public DataClass {
    
    
public:
    int getArea();
};



#endif /* DataClass_hpp */
