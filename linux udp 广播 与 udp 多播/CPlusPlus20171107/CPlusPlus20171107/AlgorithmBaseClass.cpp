//
//  AlgorithmBaseClass.cpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/24.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#include <set>
#include <vector>
#include <list>
#include <map>
#include <__hash_table>
#include <algorithm>
#include <iostream>
#include <numeric>
#include "AlgorithmBaseClass.hpp"



using namespace std;

bool equal5(int val){
    cout<<endl;
    cout<<val<<endl;
    return val>5;
}
void outPut(int val){
    
    cout<<val<<" ";

}
void outPut2(int val){
    
    cout<<val<<endl;
    
}
void outPutString(const string& val){
    
    cout<<val<<" ";
    
}
AlgorithmBaseClass:: AlgorithmBaseClass(){

}

void AlgorithmBaseClass::xiangLinChongFu(){

    multiset<int,less<int>>intSet;
    
    intSet.insert(7);
     intSet.insert(5);
     intSet.insert(1);
     intSet.insert(5);
     intSet.insert(6);
     intSet.insert(4);
     intSet.insert(3);
     intSet.insert(1);
    
    cout<<"Set"<<":";
    multiset<int,less<int>>::iterator it = intSet.begin();
    
    for (int i=0; i<intSet.size(); ++i) {
        cout<<*it++<<"";
        
        
       
    }
    cout<<endl;
    cout<<"第一次匹配:";
    it = adjacent_find(intSet.begin(), intSet.end());
    
    cout<<*it++<<"";
    
    cout<<*it<<endl;
    
    cout<<"第二次匹配:";
    
    it=adjacent_find(it, intSet.end());
    
    cout<<*it++<<"";
    cout<<*it<<endl;
    
    

}
void AlgorithmBaseClass::itemChongFuGeShuMutiset()
{

    multiset<int,less<int>>intSet;
    
    intSet.insert(7);
    intSet.insert(5);
    intSet.insert(1);
    intSet.insert(5);
    intSet.insert(6);
    intSet.insert(4);
    intSet.insert(3);
    intSet.insert(1);
    intSet.insert(5);
    
    
    cout<<"Set"<<":";
    
    multiset<int,less<int>>::iterator it = intSet.begin();
    
    for (int i=0; i<intSet.size(); ++i) {
        cout<<*it++<<"";
        
    }
    cout<<endl;
    
    
    int cnt  =count(intSet.begin(), intSet.end(), 5);
    
    cout<<"相同元素的数量:"<<cnt<<endl;
    
    
}

void AlgorithmBaseClass::bianLiXiuZhengForEach()
{
    multiset<int,less<int>>intSet;
    
    intSet.insert(7);
    intSet.insert(5);
    intSet.insert(1);
    intSet.insert(5);
    intSet.insert(6);
    intSet.insert(4);
    intSet.insert(3);
    intSet.insert(1);
    intSet.insert(5);
    
    
    cout<<"Set"<<":";
    
    for_each(intSet.begin(), intSet.end(), outPut);
    
    cout<<endl;
}

void AlgorithmBaseClass::fillVector()
{

    vector<int> intVect;
    
    intVect.push_back(5);
    intVect.push_back(1);
    intVect.push_back(8);
    intVect.push_back(4);
    intVect.push_back(7);
    cout<<"Vector"<<":";
    
    for_each(intVect.begin(), intVect.end(), outPut);
    
    fill(intVect.begin(), intVect.begin()+5, 1);
    
    cout<<endl;
    
    cout<<"vect:";
    
    for_each(intVect.begin(), intVect.end(), outPut);
    cout<<endl;
}

void AlgorithmBaseClass::randomShuffleVector()
{
    vector<int> intVect;
    
    for (int i=0; i<10; i++) {
        intVect.push_back(i);
        
    }
    
    cout<<"Vect:"<<"";
    
    for_each(intVect.begin(), intVect.end(), outPut);
    
    random_shuffle(intVect.begin(), intVect.end());
    
    cout<<endl;
    cout<<"Vect:";
    
    for_each(intVect.begin(), intVect.end(), outPut);
}
void AlgorithmBaseClass::partSplitVector()
{

    vector<int> intVect;
    
    intVect.push_back(7);
    intVect.push_back(3);
    intVect.push_back(5);
    intVect.push_back(8);
    intVect.push_back(9);
    intVect.push_back(19);
    intVect.push_back(10);
    intVect.push_back(11);
    intVect.push_back(1);
    intVect.push_back(4);
    
    cout<<endl;
    cout<<"Vect:"<<"";
    
    for_each(intVect.begin(), intVect.end(), outPut);
    cout<<endl;
    partition(intVect.begin(), intVect.end(), equal5);
    
    cout<<endl;
    cout<<"Vect:"<<"";
    
    for_each(intVect.begin(), intVect.end(), outPut);
    
    cout<<endl;

}

void AlgorithmBaseClass::rotateVector()
{
    vector<char> charVect;
    charVect.push_back('B');
    charVect.push_back('A');
    char a='\0';
    charVect.push_back(a);
    charVect.push_back('M');
    charVect.push_back('R');
    charVect.push_back(a);
    charVect.push_back('K');
     charVect.push_back('L');
     charVect.push_back('M');
    /*没有排序直接分割旋转*/
    cout<<"VectRoate1:";
    for_each(charVect.begin(), charVect.end(), outPut);
    cout<<endl;
    rotate(charVect.begin(), charVect.begin()+6, charVect.end());
     cout<<endl;
     cout<<"VectRoate2:";
    for_each(charVect.begin(), charVect.end(), outPut);
     cout<<endl;

}
void AlgorithmBaseClass::sortVector()
{

    vector<char> charVect;
    
    charVect.push_back('M');
    charVect.push_back('R');
    charVect.push_back('K');
    charVect.push_back('J');
    charVect.push_back('H');
    charVect.push_back('I');
    
    
    cout<<endl;
    cout<<"VectSort:";
    
    for_each(charVect.begin(), charVect.end(), outPut);
    
    sort(charVect.begin(), charVect.end());
    
    cout<<endl;
    cout<<"VectSort:";
    for_each(charVect.begin(), charVect.end(), outPut);
    
    cout<<endl;
    

}

void AlgorithmBaseClass::partionSortVector()
{

    vector<string> strVect;
    
    strVect.push_back("Sunday");
    strVect.push_back("Monday");
    strVect.push_back("Tuseaday");
    strVect.push_back("Wednesday");
    strVect.push_back("Thuesday");
    strVect.push_back("Friday");
    strVect.push_back("Saturday");
    
    cout<<"Vect Partion Sort"<<"";
    
    for_each(strVect.begin(), strVect.end(), outPutString);
    /*先排序再分割旋转*/
    partial_sort(strVect.begin(), strVect.begin()+3, strVect.end());
    
    cout<<endl;
     cout<<"Vect:";
    
    for_each(strVect.begin(), strVect.end(), outPutString);
    
}
void AlgorithmBaseClass::findSortVector()
{
    vector<string> strVect;
    
    strVect.push_back("Sunday");
    strVect.push_back("Monday");
    strVect.push_back("Tuseaday");
    strVect.push_back("Wednesday");
    strVect.push_back("Thuesday");
    strVect.push_back("Friday");
    strVect.push_back("Saturday");
    
    cout<<"Vect nth_element"<<"";
     cout<<endl;
    for_each(strVect.begin(), strVect.end(), outPutString);
    
    cout<<endl;
    
    nth_element(strVect.begin(), strVect.begin()+3, strVect.end());
    /*查找元素的位置 看来查找的过程中有排序动作 完成后 的 容器 有变动  整个容器被排序了*/
    cout<<"Vect"<<endl;
    
    for_each(strVect.begin(), strVect.end(), outPutString);
}
void AlgorithmBaseClass::mergeVector()
{

    vector<string> strVect1;
    vector<string> strVect2;
    
    strVect1.push_back("Sunday");
    strVect1.push_back("Monday");
    strVect1.push_back("Tuesday");
    strVect1.push_back("Wednesday");
    strVect2.push_back("Thursday");
    strVect2.push_back("Friday");
    strVect2.push_back("Saturday");
    strVect2.push_back("Over");
    
    
    cout<<endl;
    cout<<"Vect1"<<endl;
    for_each(strVect1.begin(), strVect1.end(), outPutString);
    cout<<endl;
    cout<<"Vect2"<<endl;
    for_each(strVect2.begin(), strVect2.end(), outPutString);
    cout<<endl;
    sort(strVect1.begin(), strVect1.end());
    sort(strVect2.begin(), strVect2.end());
    
    int size =strVect1.size()+strVect2.size();
    
    
    vector<string>strVect3(size);
    merge(strVect1.begin(), strVect1.end(), strVect2.begin(), strVect2.end(), strVect3.begin());
    
    cout<<"Vect3:"<<endl;
    for_each(strVect3.begin(), strVect3.end(), outPutString);


}
void AlgorithmBaseClass::includeVector()
{
    vector<string> strVect1;
    vector<string> strVect2;
    
    strVect1.push_back("Sunday");
    strVect1.push_back("Monday");
    strVect1.push_back("Tuesday");
    strVect1.push_back("Wednesday");
    strVect1.push_back("Thursday");
    strVect1.push_back("Friday");
    strVect1.push_back("Saturday");
    strVect1.push_back("Over");
    strVect1.push_back("Pnull");strVect2.push_back("Saturday");
    strVect2.push_back("Over");
    
    sort(strVect1.begin(), strVect1.end());
    sort(strVect2.begin(), strVect2.end());
    
    cout<<"Vect include1"<<endl;
    
    for_each(strVect1.begin(), strVect1.end(), outPutString);
    
    cout<<endl;
    cout<<"Vect include2"<<endl;
     for_each(strVect2.begin(), strVect2.end(), outPutString);
    cout<<endl;
    
    
    bool result= includes(strVect1.begin(), strVect1.end(), strVect2.begin(), strVect2.end());
    
    if (result) {
        cout<<"result:OK"<<endl;
    }else
    {
        cout<<"result:error"<<endl;
    }
    
    

}
void AlgorithmBaseClass::accumulateVector()
{
    
    vector<int> intVect;
    
    for (int i=0; i<5; i++) {
        intVect.push_back(i);
    }
    
    cout<<"Vect"<<endl;
    
    for_each(intVect.begin(), intVect.end(), outPut);
    
    int  result = accumulate(intVect.begin(), intVect.begin()+3, 5);
    /*计算序列元素和 与 并加 指定的值 这里是5
     原序列 元素累加 并最后 再加上我们指定的值 返回结果
     */
    cout<<endl;
    cout<<"Result:"<<result<<endl;
}

void AlgorithmBaseClass::inner_prodoctVector()
{

    /*
     注：向量积 ≠向量的积（向量的积一般指点乘）
     */
    vector<int> intVect1;
    vector<int> intVect2;
    
    for (int i=0; i<5; i++) {
        intVect1.push_back(1);
    }
    
    for (int j=2; j<10; j++) {
        intVect2.push_back(j);
    }
    
    cout<<"Vect inner_product1"<<endl;
    for_each(intVect1.begin(), intVect1.end(), outPut);
    cout<<endl;
    cout<<"Vect inner_product2"<<endl;
    
       for_each(intVect2.begin(), intVect2.end(), outPut2);
    
    cout<<endl;
    cout<<"Result"<<endl;
    /*
     
     注：向量积 ≠向量的积（向量的积一般指点乘）
     一定要清晰地区分开向量积（矢积）与数量积（标积）。见下表。
     在数学中，数量积（dot product; scalar product，也称为点积）是接受在实数R上的两个向量并返回一个实数值标量的二元运算。它是欧几里得空间的标准内积。[1]
     两个向量a = [a1, a2,…, an]和b = [b1, b2,…, bn]的点积定义为：
     a·b=a1b1+a2b2+……+anbn。
     使用矩阵乘法并把（纵列）向量当作n×1 矩阵，点积还可以写为：
     a·b=a^T*b，这里的a^T指示矩阵a的转置
     */
    int  result=inner_product(intVect1.begin(), intVect1.end(), intVect2.begin(), 100);
    cout<<endl;
    cout<<"Result:"<<result<<endl;
    
}
void AlgorithmBaseClass::leiChaAdjacent_difference()
{

    vector<int> intVect1;
    
    intVect1.push_back(7);
    intVect1.push_back(3);
    intVect1.push_back(5);
    
    
    cout<<"Vect1:";
    for_each(intVect1.begin(), intVect1.end(), outPut);
    
    cout<<endl;
    
    vector<int> intVect2(intVect1.size());
    
    /*
     原序列 相邻元素的差值 形成 新序列
     */
    adjacent_difference(intVect1.begin(), intVect1.end(), intVect2.begin());
    cout<<endl;
    cout<<"Vetc2 adjacent_difference"<<"";
    
    for_each(intVect2.begin(), intVect2.end(), outPut);
    cout<<endl;
    /*
     原序列 与 新序列 前后相邻元素求和 形成新序列
     */
    partial_sum(intVect1.begin(), intVect1.end(), intVect2.begin());
    cout<<endl;
    cout<<"Vetc2 partial_sum"<<"";
    
    for_each(intVect2.begin(), intVect2.end(), outPut);
    cout<<endl;
    
    

}
AlgorithmBaseClass:: ~AlgorithmBaseClass(){
    
}
