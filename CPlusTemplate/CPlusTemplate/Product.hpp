//
//  Product.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/1.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef Product_hpp
#define Product_hpp
/*
 C++工厂模式
 */
#include <stdio.h>

class Product {
    
    
public:
    virtual ~Product() = 0;

    /*屏蔽构造函数*/
protected:
    Product();

};

class ConcreteProduct:public Product {
    
    
public:
    ~ConcreteProduct();
    ConcreteProduct();
protected:
    
private:
    
};


#endif /* Product_hpp */
