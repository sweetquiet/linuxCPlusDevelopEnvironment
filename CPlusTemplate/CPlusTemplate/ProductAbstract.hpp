//
//  ProductAbstract.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/1.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef ProductAbstract_hpp
#define ProductAbstract_hpp

#include <stdio.h>

class ProductAbstractA {
    
    /*
     
     初级怪物 抽象类
     我们会产生 很多初级怪物
     
     初级 小兵  初级 坦克
     
     就会对应产生一组A抽象类
     
     因此 便于管理 我们对这样的需求 比简单的工厂模式 复杂一点
     
     */
public:
    ~ProductAbstractA();
    
protected:
    ProductAbstractA();
private:
    
};

class ProductAbstractB {
    
    /*
     中级怪物 抽象
     
     
     */
public:
    ~ProductAbstractB();
    
protected:
    ProductAbstractB();
    
    
private:
    
};


class ProductA1:public ProductAbstractA
{
    /*
     小兵 初级 子类
     */
public:
    ProductA1();
    ~ProductA1();
protected:
private:
    
    
};

class ProductA2:public ProductAbstractA {
    
    /*
     坦克 初级 子类
     */
public:
    ProductA2();
    
    ~ProductA2();
    
protected:
    
private:
    
};


class ProductB1:public ProductAbstractB
{
    /*
     小兵 中级 子类
     */
public:
    ProductB1();
    ~ProductB1();
protected:
private:
    
    
};

class ProductB2:public ProductAbstractB {
    
    /*
     坦克 初级 子类
     */
public:
    ProductB2();
    
    ~ProductB2();
    
protected:
    
private:
    
};
#endif /* ProductAbstract_hpp */
