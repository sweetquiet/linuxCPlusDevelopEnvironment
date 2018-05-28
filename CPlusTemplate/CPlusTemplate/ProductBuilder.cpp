//
//  ProductBuilder.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include "ProductBuilder.hpp"
#include <iostream>

using namespace std;

ProductBuilder::ProductBuilder()
{
    producePart();
    
    cout<<"return a product"<<endl;
    
}

ProductBuilder::~ProductBuilder()
{
    
    cout<<"ProductBuilder 析构"<<endl;
}



void ProductBuilder::producePart()
{
    
    cout<<"build part of product.."<<endl;
    
}


ProductPart::ProductPart()
{
    
    cout<<"ProductPart 构建"<<endl;
    
}


ProductPart::~ProductPart()
{
    
    cout<<"ProductPart 析构"<<endl;
    
}


ProductPart* ProductPart::buildPart()
{
    
    return  new ProductPart;
    
}














