//
//  TemplateObj.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/2/28.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef TemplateObj_hpp
#define TemplateObj_hpp

#include <stdio.h>

/*
 在模版生命中 你可能会见到
 使用Class
 template <Class T>
 
 这时历史原因 因为 关键字 typename 出现的晚了一些
 
 */
template <typename T>
/*
 类模版定义
 */
class TemplateObj {
    
    
public:
    template <typename H>
    
    /*
     函数模版定义
     
     函数模版定义 与 类模版定义 有一定的区别
     */
    
    inline H const& max (H const& a,H const & b){
        
        return a < b ? b : a;
    }
};




#endif /* TemplateObj_hpp */
