//
//  main.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/2/28.
//  Copyright © 2018年 admindyn. All rights reserved.
//



#include "FileHandler.hpp"

#include "DataQianTao.hpp"
#include "Date.hpp"
#include "DataDynamicCast.hpp"

#include "DataYouYuan.hpp"
#include "BitMask.hpp"
#include "Test.hpp"
#include "DataDuoTai.hpp"
#include "DataDuoTai1.hpp"
#include "DataDuoTai2.hpp"

#include "DataClass.hpp"

#include "DataStruct.hpp"

#include "Memento.hpp"

#include "Originator.hpp"

#include "Subject.hpp"

#include "Observer.hpp"

#include "Context.hpp"

#include "State.hpp"

#include "Prototype.hpp"

#include "Builder.hpp"
#include "ProductBuilder.hpp"
#include "Director.hpp"

#include "Singleton.hpp"

#include "FactoryAbstract.hpp"

#include "ProductAbstract.hpp"

#include "Facroty.hpp"

#include "Product.hpp"

#include <iostream>

#include "DataChongZai.hpp"

#include "TemplateObj.hpp"

#include "SET.hpp"

using namespace std;

double sum (int a,int b, double num_args,...);

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int i = 42 ;
    
    TemplateObj<int>obj;
    
std::cout<<obj.max<int>(1, i)<<std::endl;
    
    
    Factory* fac =new ConcreteFactory();
    
    Product* p = fac->createProduct();
    
    delete fac;
    
    delete p;
    
    /*
     抽象工厂模式
     */
    
    
    FactoryAbstract* cf1 = new ConcreteFactory1();
    cf1->createProductA();
    
    cf1->createProductB();
    FactoryAbstract* cf2 = new ConcreteFactory2();
    
    cf2->createProductA();
    cf2->createProductB();
    
    /*
     单例模式
     */
    
    Singleton* sgn = Singleton::Instance();
    
     Singleton* sgn2 = Singleton::Instance();
    
    double total = sum(10, 20, 1.2,1.4,1.6);
    
    /*
     构造模式Builder
     
     预构建 完  还可修改construct
     */
    Director* d = new Director(new ConcreteBuilder());
    
    d->construct();
    
    /*
     原型模式 原型复制
     
     */
    
    
    Prototype* ptype = new ConcretePrototype();
    
    Prototype* ptype2 = ptype->Clone();
    
    /*
     State 模式
     */
    
    
    State* st = new ConcreteStateA();
    
    Context* con = new Context
    (st);
    
    con->operationChangeState();
    
    con->operationChangeState();
    
    con->operationChangeState();
    
    
    if (con != NULL) {
        
        delete con;
        
    }
    
    if (st != NULL) {
        
        st = NULL;
    }
    
    
    /*
     观察者模式
     */
    
    ConcreteSubject* sub = new ConcreteSubject();
    Observer* ob1 = new  ConcreteObserverA(sub);
    
    Observer* ob2 = new  ConcreteObserverB(sub);
    
    sub->setState("Old");
    
    sub->Notify();
    
    sub->setState("xin");
    
    sub->Notify();
    
  /*
   备忘录 模式
   */
    
    Originator* o = new Originator();
    //备忘前的状态
    o->setState("oldstate");
    
    o->printState();
    //将状态备忘
    Memento* m = o->createMemento();
    //修改状态
    o->setState("xinstate");
    
    o->printState();
    //从备忘录恢复旧状态
    o->restoreToMemento(m);
    
    o->printState();
    
    Books book1;
    Books book2;
    
    strcpy(book1.title, "learn c++ programming");
    
    strcpy(book1.author, "chand miyan");
    
    strcpy(book1.subject, "c++project");
    book1.book_id = 1000;
    
    // 输出 Book1 信息
    cout << "Book 1 title : " << book1.title <<endl;
    cout << "Book 1 author : " << book1.author <<endl;
    cout << "Book 1 subject : " << book1.subject <<endl;
    cout << "Book 1 id : " << book1.book_id <<endl;
    
    DataStruct* pstruct = new DataStruct(&book1, &book2);
    pstruct->logout();
    
    Rectangle rect;
    
    rect.setHeight(7);
    rect.setWidth(5);
    
    rect.getArea();
    
   
    DataChongZai da1;
    DataChongZai da2;
     DataChongZai da3;
    
    // Box1 详述
    da1.setLength(6.0);
    da1.setBreadth(7.0);
    da1.setHeight(5.0);
    
    // Box2 详述
    da2.setLength(12.0);
    da2.setBreadth(13.0);
    da2.setHeight(10.0);
    
    // Box1 的体积
    double volume = da1.getVolume();
    cout << "Volume of Box1 : " << volume <<endl;
    
    // Box2 的体积
    volume = da2.getVolume();
    cout << "Volume of Box2 : " << volume <<endl;
    
    // 把两个对象相加，得到 Box3
    da3 = da1 + da2;
    
    // Box3 的体积
    volume = da3.getVolume();
    cout << "Volume of Box3 : " << volume <<endl;
    DataDuoTai *shape;
    DataDuoTai1 rec(10,7);
    DataDuoTai2  tri(10,5);
    
    // 存储矩形的地址
    shape = &rec;
    // 调用矩形的求面积函数 area
    shape->area();
    
    // 存储三角形的地址
    shape = &tri;
    // 调用三角形的求面积函数 area
    shape->area();
    
    
    Set<int> s;
    
    s.insert(77);
    s.insert(33);
    s.insert(500);
    cout<< s <<endl;
    
    s.remove(77);
    
    cout<< s <<endl;
    
    cout<< "s "<<(s.contains(77) ? "does":"does not")<<"contains 77"<<endl;
    
    
    Test* funcT = new Test();
    
    funcT->funcTest();
    
    funcT->funcBitMask();
    
    /*
     位操作类
     */
    //funcT->funcBits();
    
    
    DataYouYuan foo;
    
    int x = foo[0];
    
    cout<<"x == "<<x<<endl;
    
    foo[0] = 1;
    
    DataDynamicCast data;
    
    data.calcuate();
    
    data.printV(data);
    
    //
    
    Date d1,d2(1951,10,1);
    
    cout<< "d1 = "<< &d1 << endl;
    
    cout<< "d2 = "<< &d2 << endl;
    
    
    //
    
    
    Test t;
    long n = 3;
    t.funcFac(n);
    
    
    FileHandler f;
    
    f.funcTest();
    
    
    
    
    return 0;
}
/*
 可变参数  列表 取参
 
 每取一次  指针 向下偏移一次
 
 
 */
double sum (int a,int b, double num_args,...)
{
    
    
    double val = 0;
    
    va_list ap;
    
    int i = 0;
    
    va_start(ap, num_args);
    
    val = va_arg(ap, double);
    
   cout<< val <<endl;
    
    val = va_arg(ap, double);
    
    cout<< val <<endl;
    
    va_end(ap);
    
    
    
    return val;
    
}
