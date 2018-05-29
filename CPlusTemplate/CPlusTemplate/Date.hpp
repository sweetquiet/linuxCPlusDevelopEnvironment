//
//  Date.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/5/29.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef Date_hpp
#define Date_hpp

#include <string>
#include <cassert>
#include <stdio.h>
using namespace std;



class Date {
    
    
public:
    Date();
    Date(int y,int m,int d);
    
    //存取器
    void year(int y);
    void month(int m);
    void day(int d);
    
    //增变器
    
    int year() const;
    
    int month() const;
    
    int day() const;
    
    
    //其他
    
    int compare(const Date& d);
    
    operator string() const;
    
    static bool isleap(int y);
    
    static int endofMonth(int y,int m);
    
private:
    int _year;
    int _month;
    int _day;
    
    static int dtab[2][13];
    
    
    
    
    
    
};

inline Date::Date(int y,int m,int d)
{
    
    assert(1<= m && m<= 12);
    assert(1<= d && d<= endofMonth(y, m));
    
    _year = y;
    
    _month = m;
    
    _day = d;
    
    
}


inline int Date::year() const
{
    
    return _year;
}


inline int Date::month() const
{
    
    return _month;
}

inline int Date::day() const
{
    
    return _day;
}



inline void Date::year(int y)
{
    _year = y;
}

inline void Date::month(int m)
{
    
    assert(1<=m && m <= 12);
    _month = m;
}

inline void Date::day(int d)
{
    
    _day = d;
}


inline bool Date::isleap(int y)
{
    
    return y%4 == 0 && y%100 != 0 || y%400 == 0;
    
}

inline int Date::compare(const Date &d)
{
    
    int ydiff = _year - d._year;
    
    int mdiff = _month - d._month;
    
    return ydiff ? ydiff:(mdiff?mdiff: _day - d._day);
    
    
}



inline int Date::endofMonth(int y, int m)
{
    assert(1<= m && m<= 12);
    
    return dtab[int(isleap(y))][m];
    
}


























#endif /* Date_hpp */
