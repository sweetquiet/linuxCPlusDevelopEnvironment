//
//  Builder.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef Builder_hpp
#define Builder_hpp

#include "ProductBuilder.hpp"
#include <stdio.h>
#include <iostream>

using namespace std;

class ProductBuilder;

class Builder {
    
    
public:
    virtual ~Builder();
    
    virtual void buildPartA(const string& buildPara) = 0;
    
     virtual void buildPartB(const string& buildPara) = 0;
    
     virtual void buildPartC(const string& buildPara) = 0;
    
    virtual ProductBuilder* getProduct() =0;
protected:
    Builder();
private:
    
    
};


class ConcreteBuilder:public Builder {
    
    
public:
    ConcreteBuilder();
    
    ~ConcreteBuilder();
    
    void buildPartA(const string& buildPara);
    
    void buildPartB(const string& buildPara);
    
    void buildPartC(const string& buildPara);
    
    ProductBuilder* getProduct();
    
};









#endif /* Builder_hpp */
