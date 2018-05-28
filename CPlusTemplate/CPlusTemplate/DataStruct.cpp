
//
//  DataStruct.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "DataStruct.hpp"
using namespace std;


DataStruct::DataStruct(const Books*p1,const Books*p2)
{
    /*
     int * const 指针常量： 指针指向的地址不可以 再修改
     */
    /*
     const int * 常量指针  指针指向的地址可以修改 但是内容不能修改
     */
    book1 =(Books*) p1;
    book2 =(Books*) p2;
    
}

void DataStruct::logout()
{
    cout<<"book 1 title:"<< book1->title<<endl;
    cout<<"book 1 author:"<< book1->author<<endl;
    cout<<"book 1 subject:"<< book1->subject<<endl;
    cout<<"book 1 id:"<< book1->book_id<<endl;
}
DataStruct::~DataStruct()
{
    
    
    
}


