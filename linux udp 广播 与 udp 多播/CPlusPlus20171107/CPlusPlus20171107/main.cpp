//
//  main.cpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/7.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#include "AlgorithmBaseClass.hpp"
#include "PollNETIO.hpp"

#include "ClientPollNETIO.hpp"
#include "SelectNETIO.hpp"
#include "ClientNETIO.hpp"
#include "TCPClass.hpp"
#include "IOSelect.hpp"
#include "DeriveClass.hpp"
#include "VectorClass.hpp"
#include <iostream>
using namespace std;
void testChuanDiFunc(char* p)
{
    cout<<p<<endl;
    cout<<"我们在传递函数指针回调方法"<<endl;
    cout<<"现在已经回到调用者中"<<endl;
}

int main(int argc, const char * argv[]) {
  
    


#ifndef __cplusplus
    
#error A C++ compiler is required!
    
    
#endif
    
    
    cout << "This is the line number " << __LINE__;
    cout << " of file " << __FILE__ << ".\n";
    cout << "Its compilation began " << __DATE__;
    cout << " at " << __TIME__ << ".\n";
    cout << "The compiler gives a __cplusplus value of " << __cplusplus <<"\n";
    
#ifdef _WIN32
    //define something for Windows (32-bit and 64-bit, this part is common)
    cout << "WIN32位操作系统!\n";
#ifdef _WIN64
    //define something for Windows (64-bit only)
    cout << "WIN64位操作系统!\n";
#else
    //define something for Windows (32-bit only)
#endif
    
#elif __APPLE__
    
#include "TargetConditionals.h"
    
#if TARGET_IPHONE_SIMULATOR
    // iOS Simulator
    cout << "Apple Simulator操作系统!\n";
#elif TARGET_OS_IPHONE
    // iOS device
    cout << "Apple IOS操作系统!\n";
#elif TARGET_OS_MAC
    // Other kinds of Mac OS
    cout << "Apple Mac操作系统!\n";
#else
#   error "Unknown Apple platform"
#endif
    
#elif __ANDROID__
    // android
#elif __linux__
    // linux
    cout << "linux操作系统!\n";
#elif __unix__ // all unices not caught above
    cout << "unix操作系统!\n";
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#   error "Unknown compiler"
#endif
    
    
#if defined(__linux__)
    
     cout << "__linux__操作系统!\n";
#elif defined(__APPLE__)
     cout << "__APPLE__操作系统!\n";
#endif
    // insert code here...
    std::cout << "Hello, World!\n";
    char mesg1[]="我是vector1";
     VectorClass cl1= VectorClass(mesg1,1) ;
    char a1[]="我是a";
    char b1[]="我是b";
    cl1.testCharString(a1,b1);
    char mesg2[]="我们区分一下 字符数组 与 字符串指针";
    cl1.testIteratorCharArr(mesg2, 0);
    char mesg3[]="我是字符数组";
    //这个是二级指针 char**p
    char (*aaa)[2];
   
//    aaa=mesg3;
    char* pAr[2]={"我是二级指针1","我是二级指针2"};
    char** p=pAr;
    cl1.logMessage2(p[0]);
    char ar[]={'a','b'};
    char (*pAr2)[2]=&ar;
    aaa=pAr2;
  
    
    char  mesg4[]="我是字符串指针";
    char* mesg5[]={"我是字符串指针数组1","我是字符串指针数组2","我是字符串指针数组3"};
   cl1.testCharArrToZhiZhenShuZu(aaa, mesg4, mesg5, 3);
    
    
    int a[3][4];
    //这里二维数组 赋值给指针 只赋值的是第一个元素的首地址 并不是整体的二维数组
    int (*pIntAr)[4]=a;
    
    cl1.testFuncZhiZhen=testChuanDiFunc;
    cl1.handleFuncHuiDiaoCallBack();
    
    
    
    DeriveClass* de=new DeriveClass();
    delete de;
    
    cl1.logMessage2("分割线");
     cl1.logMessage2("分割线");
    cl1.logMessage2("派生类 分为 公有派生 私有派生 受保护派生");
    
    cl1.logMessage2("虚函数的使用 只能用virtual关键字声明类的成员函数");
    cl1.logMessage2("不能将类外的普通函数声明为虚函数");
    
    cl1.logMessage2("虚函数的作用是允许在派生类（类的继承问题处理中）对基类的虚函数重新定义。显然它 只能用于类的继承层次结构中-继承多态");
    cl1.logMessage2("当一个成员函数被生命虚函数后 就不允许同一类族中的类再定义一个非virtual的相同的函数（函数名 与 参数列表 参数类型 都相同）");
    cl1.logMessage2("根据什么考虑将一个成员函数声明为虚函数呢");
    cl1.logMessage2("第一 看成员函数所在类 是不是会作为基类");
    cl1.logMessage2("第二 看成员函数在类的继承后有无可能被更改功能，如果希望更改我们 声明虚函数");
    cl1.logMessage2("第三 有时定义虚函数时并不定义其函数体 即函数体为空 就是为了让派生类继承去实现");
    cl1.logMessage2("第四 纯虚函数 即将所在类抽象化 任何试图对该类的实例化的语句都是错误的 因为抽象类不能直接调用 必须辈子类继承重载后 再根据要求调用其子类的方法 且在子类中必须实现纯虚函数的定义");
    cl1.logMessage2("第五 最关键 影响内存的释放 如下 我们用基类引用子类实例化对象 然后 释放对象 如果不对基类析构函数声明为 虚函数 内存释放会有问题  【应考虑对成员函数的调用 是通过对象名还是通过基类指针或引用去访问 如果是通过基类指针或引用去访问 则应当声明为虚函数】");
    BaseClass* de2=new DeriveClass();
    
    delete de2;
    
    cl1.testString();
    
    cl1.testStrTo64I(12345);
    
    cl1.int64StrtoInt("0x12345");
    
    cl1.testVectorStruct();
    
    cl1.testMapYouXU();
    
    cl1.testSet();
//    IOSelect sel;
    
    /*
     事件驱动 网络IO复用
     对比了poll select epoll和kqueue的性能。select和poll是一个级别的，epoll和kqueue是一个级别的，相差不多。epoll用在linux 上,kqueue用在bsd上,不能物理上共存。 如果你的服务器cpu较好，linux内核新，可考虑用epoll.
     
     */
//    SelectNETIO server;
    
//    PollNETIO server;
//    
//    server.testServer();
    
    
    AlgorithmBaseClass algoti;
    algoti.xiangLinChongFu();
    algoti.itemChongFuGeShuMutiset();
    
    algoti.bianLiXiuZhengForEach();
    algoti.fillVector();
    algoti.randomShuffleVector();
    algoti.partSplitVector();
    algoti.rotateVector();
    
    algoti.sortVector();
    algoti.partionSortVector();
    algoti.findSortVector();
    algoti.mergeVector();
    algoti.includeVector();
    algoti.accumulateVector();
    algoti.inner_prodoctVector();
    algoti.leiChaAdjacent_difference();
    
    return 0;
}
