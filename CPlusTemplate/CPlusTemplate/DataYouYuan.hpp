//
//  DataYouYuan.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/5/28.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef DataYouYuan_hpp
#define DataYouYuan_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class DataYouYuan {
    
    
public:
    class refrence_youyuan
    {
        friend class DataYouYuan;
        
        DataYouYuan& youyuanData;
        
        int index;
        
        refrence_youyuan(DataYouYuan& f,int idx): youyuanData(f),index(idx)
        {}
        
    public:
        int operator = (int val)
        {
            cout<<"assgining "<<val<<"to position "<<index<<endl;
            
            //通常在这里处理左值
            
            return val;
            
            
        }
        
        operator int() const
        {
            cout << "assgining from position "<<index<<endl;
            //通常在这里处理右值
            
            return 1;
        }
        
            };
    refrence_youyuan operator[](int idx)
            {
                return refrence_youyuan(*this,idx);
            }
};
















#endif /* DataYouYuan_hpp */
