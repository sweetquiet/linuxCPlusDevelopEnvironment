//
//  DataDynamicCast.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/5/28.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef DataDynamicCast_hpp
#define DataDynamicCast_hpp

#include <stdio.h>

/*
 dynamic_cast
 强制类型转换 该操作符 提供了安全的向下强制类型转换
 
 可以 将一个指向派生了句的指针赋值给指向基类的指针
 class B{...};
 
 class D:public B {...};
 
 D d;
 
 B* bp = &d;
 
 以上是安全的 因为D 与 B 服从 is-a 关系 但这里还没有使用 强制类型转换 向下转型
 
 下面开始：
 
 如果被引用的对象实际上是D 则从指向B的指针給指向D的指针赋值才有意义 这种 叫 向下类型转换
 
 
 D* dp = dynamic_cast(B*)bp;
 注意这里使用if检查语句
 如果强制类型转换不安全 则dynamic_cast操作符会返回一个空指针 否则 它返回强制转换的原始指针給新类型
 
 if(dp)
 {
 
 
 }
 
 
 以上强制类型转换是 运行期机制
 
 
 还有三种类型转换 是编译器机制
 
 
 当确实知道指向B的指针 指向了 指向D的指针 这时可使用static_cast 因为运行期的检查变得没必要，他可能是从C移植过来的代码中应用最广泛的强制类型转换
 
 
 还有就是 经常用到的 const 类型指针 转换为 去掉const的指针
 
 void B::f() const
 {
    //改变一个常量对象的数据成员
 
 const_cast(B*)(this)->state = ...;
 
 }

 以上去限定符const volatile的类型转换 的存在
 
 实参的类型必须与括号中的目标类型相同
 */

class DataDynamicCast {
    
   
public:
    int value = 100;
    DataDynamicCast();
    void changeV(DataDynamicCast& d);
    
    void printV(DataDynamicCast& d) const;
    void calcuate();
    void cpV(const DataDynamicCast &d);
    ~DataDynamicCast();
};
 
 
 
 
 
 











#endif /* DataDynamicCast_hpp */
