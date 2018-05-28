//
//  ProductBuilder.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef ProductBuilder_hpp
#define ProductBuilder_hpp

/*
 Builder模式
 
 当我们创建的对象很复杂的时候 （通常有很多其他的对象组合而成）
 我们一步步的进行复杂对象的构建
 
 由于在每一步的构造过程中可以引入参数
 通过这样经过相同的步骤创建最后得到多元化的对象展示
 
 */

#include <stdio.h>

class ProductBuilder {
    
    
public:
    ProductBuilder();
    
    ~ProductBuilder();
    
    
    void producePart();
    
protected:
private:
    
    
};

class ProductPart {
    
    
public:
    ProductPart();
    ~ProductPart();
    
    ProductPart* buildPart();
    
protected:
private:
    
};








#endif /* ProductBuilder_hpp */
