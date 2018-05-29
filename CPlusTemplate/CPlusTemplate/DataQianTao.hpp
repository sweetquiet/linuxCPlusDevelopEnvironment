//
//  DataQianTao.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/5/29.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef DataQianTao_hpp
#define DataQianTao_hpp

#include <stdio.h>

class DataQianTaoStr {
    
    
public:
    //构造函数 析构函数
    
    DataQianTaoStr(const char* s);
    
    DataQianTaoStr(const DataQianTaoStr& s);
    
    ~DataQianTaoStr();
    
private:
    class Srep{
        
    public:
        Srep(const char* p);
        ~Srep();
        
        char* rep;
        
        size_t count;
        
        
        
    };
    
    Srep* rep;
    
    
    
};





















#endif /* DataQianTao_hpp */
