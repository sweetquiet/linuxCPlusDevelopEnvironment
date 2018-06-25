//
//  AlgorithmBaseClass.hpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/24.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#ifndef AlgorithmBaseClass_hpp
#define AlgorithmBaseClass_hpp

#include <stdio.h>

class AlgorithmBaseClass {

public:
    char* message;
    
    AlgorithmBaseClass();
    
//非修正序列算法
    void xiangLinChongFu();
    void itemChongFuGeShuMutiset();
    void bianLiXiuZhengForEach();
//修正序列算法
    void fillVector();
    void randomShuffleVector();
    void partSplitVector();
    void rotateVector();
//排序算法
    void  sortVector();
    
    void partionSortVector();
    void findSortVector();
    void mergeVector();
    void includeVector();
    
//数值算法
    
    void accumulateVector();
    void inner_prodoctVector();
    void leiChaAdjacent_difference();
    //
    ~AlgorithmBaseClass();
};


#endif /* AlgorithmBaseClass_hpp */
