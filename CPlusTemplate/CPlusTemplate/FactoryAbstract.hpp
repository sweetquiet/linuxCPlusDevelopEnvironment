//
//  FactoryAbstract.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/1.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef FactoryAbstract_hpp
#define FactoryAbstract_hpp

#include "ProductAbstract.hpp"
#include <stdio.h>


class FactoryAbstract {
    
    
public:
    
    virtual ~FactoryAbstract();
    
    virtual ProductAbstractA* createProductA() = 0;
    
     virtual ProductAbstractB* createProductB() = 0;
    
protected:
        FactoryAbstract();
    
private:
    
    
    
    
};

/*
 由于将子类 分组 初级 中级
 
 子类 初级 小兵 坦克
 
     中级 小兵 坦克
 */

/*
 将工厂 也 分类
 */

/*
 初级 工厂
 */
class ConcreteFactory1:public FactoryAbstract {
    
    
public:
    ConcreteFactory1();
    
    ~ConcreteFactory1();
    
    ProductAbstractA* createProductA();
    
     ProductAbstractB* createProductB();
    
    
};

/*
 中级 工厂
 */
class ConcreteFactory2:public FactoryAbstract {
    
    
public:
    ConcreteFactory2();
    
    ~ConcreteFactory2();
    
    ProductAbstractA* createProductA();
    
    ProductAbstractB* createProductB();
    
    
};


#endif /* FactoryAbstract_hpp */
