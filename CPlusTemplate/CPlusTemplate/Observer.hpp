//
//  Observer.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/5.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef Observer_hpp
#define Observer_hpp

#include "Subject.hpp"

#include <string>

#include <stdio.h>


typedef string  StateStr;

class Observer {
    
    
public:
    
    virtual ~Observer();
    
    /*
     　纯虚函数的语法：
     
     　　1、  将成员函数声明为virtual
     
     　　2、  后面加上 = 0
     
     　　3、  该函数没有函数体
     
     在许多情况下，在基类中不能对虚函数给出有意义有实现，而把它说明为纯虚函数，它的实现留给该基类的派生类去做。这就是纯虚函数的作用。
     */
    
    virtual void update(Subject* sub) = 0;
    
    virtual void printInfo() = 0;
    
protected:
    
    Observer();
    
    StateStr _st;
  
    
private:
    /*
     私有的时候 子类都无法访问
     
     友元类 才可以访问
     */
    
    
    
    
    
};



class ConcreteObserverA:public Observer {
    
    
public:
    
    
    
    ConcreteObserverA(Subject* sub);
    
 
    
    void update(Subject* sub)  ;
    
     void printInfo() ;
    
    
    virtual ~ConcreteObserverA();
    
    virtual Subject* getSubject();
    
protected:
    
private:
    Subject* _sub;
    
    
    
};
/*
 virtual关键字可以修饰普通的成员函数，也可以修饰析构函数，但并不是没有限制
 
 virtual在函数中的使用限制
 
 普通函数不能是虚函数，也就是说这个函数必须是某一个类的成员函数，不可以是一个全局函数，否则会导致编译错误。
 静态成员函数不能是虚函数 static成员函数是和类同生共处的，他不属于任何对象，使用virtual也将导致错误。
 内联函数不能是虚函数 如果修饰内联函数 如果内联函数被virtual修饰，计算机会忽略inline使它变成存粹的虚函数。
 构造函数不能是虚函数，否则会出现编译错误。
 */
class ConcreteObserverB:public Observer {
    
    
public:
    
    
    ConcreteObserverB(Subject* sub);
    
    void update(Subject* sub) ;
    
    void printInfo() ;
    
    
   virtual   ~ConcreteObserverB();
    
    /*
     虚函数为了重载和多态的需要，在基类中是有定义的，即便定义是空，所以子类中可以重写也可以不写基类中的此函数！
     纯虚函数在基类中是没有定义的，必须在子类中加以实现，
     */
    
   virtual Subject* getSubject() ;
    
protected:
    
private:
    Subject* _sub;
    
    
    
};


#endif /* Observer_hpp */
