//
//  SET.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/5/25.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef SET_hpp
#define SET_hpp

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stddef.h>


template<typename T>
class Set {
    
    
public:
    Set();
   
    bool contains(const T&x) const;
   
    void insert(const T&x);
  
    void remove(const T&x);
    
    void print(std::ostream&os) const;
    
private:
    enum {LIMIT = 64};
   
    T elems[LIMIT];
    size_t nelems;
};

template<typename  T>

Set<T>::Set()
{
    nelems = 0;
}


template<typename  T>
bool Set<T>::contains(const T&x) const
{
    const T* eof = elems + nelems;
    
    return std::find(elems, eof, x) != eof ;
    
    
    
}

template<typename  T>

void Set<T>::insert(const T& x)
{
    if (nelems <LIMIT && !contains(x)) {
        elems[nelems++] = x;
    }
    
}

template<typename  T>

void Set<T>::remove(const T &x)
{
    
    T* eof = elems + nelems;
    
    if (std::remove(elems, eof, x) != eof) {
        --nelems;
    }
    
}

template<typename  T>

void Set<T>::print(std::ostream &os) const
{
    
    os<<"{";
    
    for (int i=0; i<nelems; ++i) {
        
        if (i>0) {
            os << ',';
        }
        os << elems[i];
        
        
    }
    os<<"}";
    
}


template<typename  T>
std::ostream& operator<<(std::ostream&os,const Set<T>&s)
{
    
    s.print(os);
    
    return os;
    
}

#endif /* SET_hpp */
