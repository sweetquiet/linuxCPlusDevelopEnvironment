//
//  VectorClass.cpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/7.
//  Copyright © 2017年 admindyn. All rights reserved.
//


#include <set>
#include <map>
#include <vector>
#include "VectorClass.hpp"
using namespace std;

struct StrLess{

    bool operator() (const char* s1,const char* s2) const{
    
        return  strcmp(s1, s2)<0;
    }
};



void printSetInt(set<int>s){

    copy(s.begin(), s.end(), ostream_iterator<int>(cout,","));
    cout<<endl;
}

void printSetChar(set<const char*,StrLess>s){
    
    copy(s.begin(), s.end(), ostream_iterator<const char*>(cout,","));
    cout<<endl;
}


void printV(vector<int> v){
    
    vector<int>::iterator iter = v.begin();
    
    for (;iter!=v.end(); iter++) {
        cout<<*iter<<endl;
    }
    
}

void logMessage(char* p){
    //数组名代表数组第一个元素的地址
    int a[3][4];
    int (*pIntAr)[4]=a;
    cout<<p<<endl;
}
void logMessageBuYong(char* p){
     //数组名代表数组第一个元素的地址
    int a[3][4];
    int (*pIntAr)[4]=a;
    cout<<*p<<endl;
}
void iteratorCharArray(char* charString)
{
    char *str=charString;
    char p1[]="循环体外";
    logMessage(p1);
    
    logMessage(&str[0]);
    logMessage(&str[1]);
    logMessage(&str[2]);
    logMessage(&str[3]);
    logMessage(&str[4]);
    logMessage(&str[5]);
    cout<<strlen(str)<<endl;
    cout<<sizeof(str)<<endl;
    char p2[]="循环体内";
    logMessage(p2);
    for (int i=0; i<strlen(str); i++) {
        
        logMessage(&str[i]);
    }
    
}

void switchAtoBYinYong(char* (&a) ,char* (&b)){
    char ar[]="交换前";
    char* temp=ar ;
    logMessage(temp);
    logMessage(a);
    logMessage(b);
    temp=a;
    a=b;
    b=temp;
    char ar2[]="交换后";
    logMessage(ar2);
    logMessage(a);
    logMessage(b);
}

void switchAtoBZhiZhen(char* a,char* b){
    char ar[]="交换前zhizhen";
    char* temp=ar ;
    logMessage(temp);
    logMessage(a);
    logMessage(b);
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);;
    char ar2[]="交换后zhizhen";
    logMessage(ar2);
    logMessage(a);
    logMessage(b);
    
    
}

void  dynamicArray()
{
    int *p,i;
    p=(int *)malloc(sizeof(int)*10);//动态申请数组空间
    for(i=0;i<10;scanf("%d",p+i++));//输入数据
    for(i=0;i<10;printf("%d ",p[i++]));//数据使用完毕
    free(p);//释放空间
    p=NULL;//使指针无效
    printf("\n");
}
//定义构造函数
VectorClass::VectorClass(char* mesg,int index):detailS(mesg),index(index){
    this->detailS=mesg;
    this->index=index;
  
  
    int aARR[3][4]={1,2,3,4,4,3,2,1,5,6,7,8};
    this->ar=aARR;
    
    cout<<this->detailS<<endl;
   
    
}
//定义静态数据成员
int VectorClass::count=10;
int VectorClass::sum=0;
//定义静态成员函数
double VectorClass::average()
{
    return sum*1.0/count;
}
//定义非静态成员函数
void VectorClass::logMessage2(char* p){
    
    cout<<p<<endl;
}
//定义非静态成员函数
void VectorClass::testCharArrToZhiZhenShuZu(char (*aArZhiZhen)[2],char bCharAr [],char * cZhiZhenAr[],int count)
{
    logMessage("测试 字符数组指针（ 二位数组 某个元素的指针） 与 （字符数组 字符串指针）与 字符串数组（字符串指针数组）");
    logMessage(*aArZhiZhen);
    logMessage(bCharAr);
    for (int i=0; i<count; i++) {
          logMessage(cZhiZhenAr[i]);
    }
  
}
//定义非静态成员函数
void VectorClass::handleFuncHuiDiaoCallBack()
{
    this->testFuncZhiZhen("我处理完了");
}




void VectorClass::testIteratorCharArr(char a[],int count){
    //外面声明的是字符串指针 这里行参是字符数组
    //这里关键是区分一下 字符数组指针 与 字符指针数组 ；字符数组 与 字符串指针
    
    iteratorCharArray(a);


}
void VectorClass::testString()
{
    
    string str1="Spend all your time waiting";
    string str2="For that second chance";
    string str3(str1,6);
    string str4(str1,6,3);
    
  
    
    cout<<str1<<endl;
    cout<<str2<<endl;
    cout<<str3<<endl;
    cout<<str4<<endl;
    
    logMessage2("将c++ string 转换为 c字符串 ");
    
      const char * cstr = str1.c_str();
    
    logMessage2("c++ string 的 copy 与 截取 字符串");
    
    size_t length;
    char buffter [8];
     logMessage2("c++ string 的 copy函数 将 复制的长度 放在前面 将 复制的起始点放在后面  和 其他语言的复制的略有不同");
    length=str1.copy(buffter, 7,5);
    logMessage2(buffter);
    logMessage2("c++ string 的 拼接");
     string str11="wo shi di yi string";
    string str12=" 2wo2 shi di yi string 2";
    string str13=str11+str12;
    
    char buffter2 [128];
    length=str13.copy(buffter2, 7+str11.size(),0);
  
    logMessage2(buffter2);
    
    
    

}

void VectorClass::testStrTo64I(long long a)
{
    char buf[32];
    snprintf(buf, sizeof(buf), "%lld",a);
    logMessage(buf);
    /*
     %012d 将数字 格式化为字符串 （数字 与 int 的类型转换）
     格式 指 int 型的数值 以 12 位 的固定位宽输出 如果不足12 位前面用0补足 如果超过12位 则按实际位宽输出 如果输出的数值不是 int 类型 则将其 强制类型转换为int
     
     那就是先得到000000012345 再取前面9-1位  即 8位 则是00000001
     */
    snprintf(buf, 9, "%012d",a);
    logMessage(buf);
}

int64_t VectorClass::int64StrtoInt(const std::string& s){
    
    char * endPtr;
    int64_t ret=strtoll(s.c_str(), &endPtr, 0);
    
    return ret;
}

void testVector()
{
    char meg1[]="vector 优点  1、可以使用下标访问个别的元素 2、 迭代器可以按照不同的方式遍历容器 3、可以在容器的末尾增加或删除元素 缺点 在其他位置 添加或删除元素 则不及lists";
    char * p =meg1;
    logMessage(p);
}

int  cmp(Rect a,Rect b){

    if (a.idIndex!=b.idIndex) {
        return  a.idIndex>b.idIndex;
    }else
    {
        if (a.length!=b.length) {
            return a.length>b.length;
        }else
        {
            return a.width>b.width;
        }
    }
}

void  VectorClass::testSet(){

    set<int> s1;
    
    set<const char* ,StrLess>s2(StrLess);
    
    set<int>s3(s1);
    
    int iArray[]={13,32,19};
    
    set<int> s4(iArray,iArray+3);
    
    const char* szArray[] ={"hello","dog","bird"};
    
    set<const char*,StrLess>s5(szArray,szArray+3,StrLess());
    
    set<const char*,StrLess>::iterator iterSet5=s5.begin();
    
    cout<<*iterSet5<<endl;
    
    
    pair<set<const char*,StrLess>::iterator, bool> insertPair;
    
    insertPair = s5.insert("我插入set");
    
   
    if (insertPair.second==true) {
        logMessage2("插入set5成功");
    }else
    {
     logMessage2("插入set5失败");
    }
        printSetChar(s5);
}
void  VectorClass::testMapYouXU(){
    
    /*
     在 c++中的 map 是 在数据插入时 是保证有序的
     
     默认按照 key从小到大排序的
     
     Map排序问题中 按照什么排序 采用函数对象
     
     是指 重载函数操作符的类 
     
     less<_Key> 默认的Map中 默认传参 函数对象 实现排序方法
     */
    
    map<int,string> mapStudent;
    
    mapStudent[8]="student_one";
    mapStudent[9]="student_two";
    mapStudent[1]="student_three";
    
    pair<map<int,string>::iterator, bool> insert_pair;
    
   insert_pair= mapStudent.insert(pair<int, string>(3,"naline_student"));
                      
    if (insert_pair.second==true) {
        cout<<"数据插入成功"<<endl;
    }else
    {
        cout<<"数据插入失败"<<endl;
    }
  
    map<int, string>::iterator iterMap=mapStudent.begin();
    
    for (;iterMap!=mapStudent.end(); iterMap++) {
        cout<<iterMap->first<<endl;
         cout<<iterMap->second<<endl;
    }
}


void VectorClass::testVectorStruct()
{

    vector<Rect> vec;
    
    Rect rec;
    rec.idIndex=2;
    rec.length=3;
    rec.width=4;
    
    vec.push_back(rec);
    rec.idIndex=1;
    rec.length=2;
    rec.width=3;
    
    vec.push_back(rec);
    
    vector<Rect>::iterator it=vec.begin();
    
    cout<<(*it).idIndex<<(*it).length<<(*it).width<<endl;
    logMessage2("vector 迭代器 排序");
    sort(vec.begin(), vec.end());
    
    cout<<(*it).idIndex<<(*it).length<<(*it).width<<endl;
    
    sort(vec.begin(), vec.end(), cmp);
    cout<<(*it).idIndex<<(*it).length<<(*it).width<<endl;
    
       logMessage2("vector 迭代器 查找元素");
    
    vector<int> vecInt;
    
    vecInt.push_back(1);
    vecInt.push_back(12);
    vecInt.push_back(13);
    vecInt.push_back(14);
    vecInt.push_back(3);
    vecInt.push_back(5);
    /*注意 find sort 函数 不存在于 vector 文件中 存在 #include <algorithm> 中*/
    vector<int>::iterator iter = find(vecInt.begin(), vecInt.end(), 3);
    
    if (iter==vecInt.end()) {
        cout<<"Not Found"<<endl;
    }else
    {
        cout<<*iter<<endl;
    }
    
    logMessage2("vector 的删除某个元素 erase");
    
    logMessage2("vector 的删除前");
    for (iter=vecInt.begin(); iter!=vecInt.end(); iter++) {
        cout<<*iter<<endl;
    }
    if (iter==vecInt.end()) {
        logMessage2("我已经改变自己当初开始的位置了");
        iter=vecInt.begin();
    }
    for (;iter!=vecInt.end(); ) {
        if (*iter==3) {
            iter=vecInt.erase(iter);
        }else
        {
            ++iter;
        }
    }
     logMessage2("vector 的删除后");
    for (iter=vecInt.begin(); iter!=vecInt.end(); iter++) {
        cout<<*iter<<endl;
    }
    
   logMessage2("vector 的 插入元素");
    vector<int> vecTest1(12,18);
    
    printV(vecTest1);
    
    int a[7]={1,2,3,4,5,6,7};
    vector<int> vecTest2(a,a+7);
    printV(vecTest2);
    
    vector<int> vecTest3(12);
     printV(vecTest3);
    
    vector<int> vecTest4;
    
    int values[] ={101,103,108,109};
    vecTest4.insert(vecTest4.end(), values+1,values+3);
    
     printV(vecTest4);
    logMessage2("中间插入");
    vecTest4.insert(vecTest4.begin()+1, 4);
    
    printV(vecTest4);
    logMessage2("中间插入2");
    vecTest4.insert(vecTest4.begin(), 4,99 );
    printV(vecTest4);
    
    vecTest4.clear();
    
    if (true==vecTest4.empty()) {
        cout<<"vecTest4 已经被清空"<<endl;
    }
    
    
    
    
    
}

void VectorClass::testCharString(char*a,char*b){
    //这里关键是区分一下 字符数组 与 字符串指针
    //字符数组
    char meg1[]="函数体外的a,b";
    //字符串指针
    char * mesg1=meg1;
    logMessage(mesg1);
    logMessage(a);
    logMessage(b);
    char meg2[]="引用传值函数体内的a,b";
    char * mesg2=meg2;
    logMessage(mesg2);
    switchAtoBYinYong(a, b);
    char meg3[]="函数体外经过引用传值改变后的a,b";
    char * mesg3=meg3;
    logMessage(mesg3);
    logMessage(a);
    logMessage(b);
    char meg4[]="指针传值函数体内的a,b";
    char * mesg4=meg4;
    logMessage(mesg4);
    switchAtoBZhiZhen(a, b);
    char meg5[]="函数体外经过指针传值改变后的a,b";
    char * mesg5=meg5;
    logMessage(mesg5);
    logMessage(a);
    logMessage(b);
    
}
VectorClass::~VectorClass(){
//定义析构函数
    char meg5[]="析构函数的主要功能是 删除成员变量 需要先判断 字符串指针 是否为空 如果不为空 再将其指向null";
    char * mesg5=meg5;
    logMessage(mesg5);
    
    if (detailS) {
//        delete [] detailS;
        detailS=0;
    }
    

}
