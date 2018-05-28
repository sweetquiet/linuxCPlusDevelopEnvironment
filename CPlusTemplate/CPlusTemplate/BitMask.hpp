//
//  BitMask.hpp
//  CPlusTemplate
//
//  Created by admindyn on 2018/5/25.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef BitMask_hpp
#define BitMask_hpp

#include <stddef.h>
#include <assert.h>
#include <limits.h>
#include <stdio.h>

class BitMask {
    typedef unsigned long _Block;
    
public:
    explicit BitMask(_Block n = 0ul);
    bool test(size_t pos) const;
    
    void set(size_t pos);
    
    void set1(size_t pos,bool val);
    
    void reset(size_t pos);
    
    void reset();
    
    
    BitMask& operator|=(const BitMask&x);
    
    BitMask& operator&=(const BitMask&x);
    
    friend BitMask operator|(const BitMask&l,const BitMask&r);
    
    friend BitMask operator&(const BitMask&l,const BitMask&r);
    
    BitMask operator~() const;
    
    
    operator _Block() const;
    
    size_t size() const;
    
private:
    _Block m_Bits;
};

inline BitMask::BitMask(_Block n)
{
    
    m_Bits = n;
}

inline bool BitMask::test(size_t pos) const
{
    
    assert(0 <= pos && pos <size());
    
    return m_Bits & (1ul << pos);
}

inline void BitMask::set(size_t pos)
{
    
    assert(0 <= pos && pos <size());
    
    m_Bits |= (1ul << pos);
    
}
inline void BitMask::set1(size_t pos, bool val)
{
    
    val? set(pos) : reset(pos);
    
}


inline void BitMask::reset(size_t pos)
{
    
    assert(0<= pos && pos < size());
    
    m_Bits &= ~(1ul << pos);
}


inline void BitMask::reset()
{
    
    m_Bits = 0ul;
}

inline BitMask& BitMask::operator|=(const BitMask &x)
{
    
    m_Bits |= x.m_Bits;
    
    return *this;
}


inline BitMask& BitMask::operator&=(const BitMask &x)
{
    m_Bits &= x.m_Bits;
    
    return *this;
    
}

inline BitMask operator|(const BitMask&l,const BitMask&r)
{
    
    return BitMask(l.m_Bits|r.m_Bits);
    
}

inline BitMask operator&(const BitMask& l,const BitMask&r)
{
    
    return BitMask(l.m_Bits&r.m_Bits);
    
    
}

inline BitMask BitMask::operator~() const
{
    return BitMask(~m_Bits);
    
}


inline BitMask::operator BitMask::_Block() const
{
    return m_Bits;
}

inline size_t BitMask::size() const
{
    
    return  sizeof(_Block)* CHAR_BIT;
    
}


#endif /* BitMask_hpp */
