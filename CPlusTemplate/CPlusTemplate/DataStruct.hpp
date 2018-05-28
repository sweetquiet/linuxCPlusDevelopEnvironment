//
//  DataStruct.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef DataStruct_hpp
#define DataStruct_hpp

#include <stdio.h>

typedef struct
{
    char  title[50];
    char  author[50];
    char  subject[100];
    int   book_id;
}BookType;

struct Books {
    char title[50];
    char author[50];
    char subject[100];
    int book_id;
};

class DataStruct {
    
    
public:
    struct Books* book1;
    struct Books* book2;
    
public:
    DataStruct(const Books*p1,const Books*p2);
   void logout(void);
    ~DataStruct();
   
};


#endif /* DataStruct_hpp */
