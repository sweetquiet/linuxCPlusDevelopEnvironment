//
//  DataDuoTai.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef DataDuoTai_hpp
#define DataDuoTai_hpp

#include <stdio.h>


class DataDuoTai {
    
    
public:
    DataDuoTai(int a = 0,int b=0);
    
    /*
     继承 要让子类重写 该方法 要用virtual 关键字
     */
    virtual int area();
    /*
     
     什么时候用到析构函数呢，就是存在继承关系，想用父类指针去指向堆中的子类对象，并且想使用父类指针去释放这块内存，则选用虚析构函数。
     */
    virtual  ~DataDuoTai();
    
protected:
    int width,height;
    
};








#endif /* DataDuoTai_hpp */
