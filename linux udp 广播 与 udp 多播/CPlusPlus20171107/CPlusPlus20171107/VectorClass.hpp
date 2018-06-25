//
//  VectorClass.hpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/7.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#ifndef VectorClass_hpp
#define VectorClass_hpp

#include <stdio.h>
#include <iostream>

typedef struct rect {
    int idIndex;
    int width;
    int length;
    bool operator<(const rect& a)const{
    
        if(idIndex!=a.idIndex){
            return idIndex<a.idIndex;
        }else
        {
            if(length!=a.length){
            
                return length<a.length;
            }else
            {
                return width<a.width;
            }
        }
    }
}Rect;

struct Student {
    int num;
    char name[20];
    int age;
};

class VectorClass
{
public:
    char* detailS;
    double length;
    int index;
    //数组指针
    int (*ar)[4];
    //静态数据成员 是所有成员共享的
    static int count;
    static int sum;
    
//    //指针数组 报错信息"field has incomplete type"。
//    char* strL [];
   
    /*
     构造函数除了有名字，参数列表和函数体之外，还可以有初始化列表，初始化列表以冒号开头，后跟一系列以逗号分隔的初始化字段
     */
    VectorClass(char* mesg,int index);//声明构造函数
    void testIteratorCharArr(char *a ,int count);//声明非静态成员函数
    void testCharString(char*a,char*b);
    void testCharArrToZhiZhenShuZu(char (*aArZhiZhen)[2],char* bCharAr ,char * cZhiZhenAr[],int count);
    void handleFuncHuiDiaoCallBack();
    void (* testFuncZhiZhen)(char* p);
    void logMessage2(char* p);
    void testString();
    void testStrTo64I(long long a);
    void testVectorStruct();
    void exec();//声明非静态成员函数
    int64_t int64StrtoInt(const std::string& s);
    void  testMapYouXU();/*红黑树*/
    void  testSet();/*红黑树*/
    static double average();//声明静态成员函数
    ~VectorClass();//声明析构函数
    
};

//类和结构体的声明要以分号结尾



#endif /* VectorClass_hpp */








