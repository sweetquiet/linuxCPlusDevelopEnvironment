//
//  DataChongZai.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/3/27.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef DataChongZai_hpp
#define DataChongZai_hpp

#include <stdio.h>

class DataChongZai {
    
private:
    double length;
    double breadth;
    double height;
    
public:
    DataChongZai();
    ~DataChongZai();
    void print(int i);
    void print(double f);
    void print(char* c);
    
    double getVolume(void);
    void setLength(double len);
    void setBreadth(double bre);
    void setHeight(double hei);
    
    double getLength();
    double getBreadth();
    double getHeight();
    
   friend DataChongZai operator+(const DataChongZai& b,const DataChongZai& a);

    
};










#endif /* DataChongZai_hpp */
