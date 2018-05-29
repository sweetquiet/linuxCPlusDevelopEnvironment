//
//  FileHandler.cpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/5/29.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include "FileHandler.hpp"
using namespace std;

void FileHandler::funcTest()
{
    const int BUFSIZE = 128;
    char buf1[BUFSIZE],buf2[BUFSIZE];
    
    //打开文件
    
    //if (argc != 3) {
     //   return EXIT_FAILURE;
    //}
    
    ifstream f1("/Users/admindyn/Desktop/dailyspace/CPlusTemplate/CPlusTemplate/test");
    
    ifstream f2("/Users/admindyn/Desktop/dailyspace/CPlusTemplate/CPlusTemplate/test");
    
    //
    
    f1.getline(buf1,BUFSIZE);
    f2.getline(buf2,BUFSIZE);
    cout<<"两个文件同时开始读数据"<<endl;
    //两个缓冲期 都有数据
    while (f1 && f2) {
        //打印 和 刷新适当的行
        //判断是否相同 相同为 true 不同为 false
        if (strcmp(buf1, buf2)) {
            
            f1.getline(buf1, BUFSIZE);
            
        }else
        {
            cout<< buf2 << endl;
            
            f2.getline(buf2, BUFSIZE);
            
            
            
        }
        
        
        
    }
    
    cout<<"至少一个文件读完了"<<endl;
    //清空剩下的文件
    //至少一个文件已经读完
    while (f1) {
        
        cout<< buf1 <<endl;
        
        f1.getline(buf1, BUFSIZE);
        
    }
    
    /*
     断言 如果 file1 文件 读完 断言为真 继续向下 看file2文件 是否读完
     */
    
    assert(f1.eof());
    
    
    while (f2) {
        cout<< buf2 << endl;
        f2.getline(buf2, BUFSIZE);
        
    }
    
    assert(f2.eof());
    
    
    f1.close();
    
    f2.close();
    
    
    
    
    

}


























