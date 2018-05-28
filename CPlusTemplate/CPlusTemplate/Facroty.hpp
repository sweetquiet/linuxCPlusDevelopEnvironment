//
//  Facroty.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/1.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef Facroty_hpp
#define Facroty_hpp

#include <stdio.h>


class Product;


class Factory {
    
    
public:
    virtual ~Factory() = 0;
    
    /*该函数在父类中定义 但并未在父类实现 在子类实现 但是父类定义时 一定要有 =0 标记*/
    virtual Product* createProduct() = 0;
    
protected:
    
    Factory();
    
private:
    
    
};


class ConcreteFactory:public Factory {
    
    
public:
    ~ConcreteFactory();
    
    ConcreteFactory();
    
    Product* createProduct();
    
protected:
    
private:
    
    
    
};


#endif /* Facroty_hpp */
