//
//  KqueueNETIO.hpp
//  CPlusPlus20171107
//
//  Created by admindyn on 2017/11/10.
//  Copyright © 2017年 admindyn. All rights reserved.
//

#ifndef KqueueNETIO_hpp
#define KqueueNETIO_hpp
/*
 网络服务器的开发，主要在linux上，底层都是使用epoll进行异步IO处理。而开发者最常见的工作环境确是mac，不支持epoll，但有一个类似epoll的kqueue。为了方便开发与调试，我把自己的https://github.com/yedf/handy库移植到了mac平台上，把epoll的调用改成kqueue
 */
#include <stdio.h>

#endif /* KqueueNETIO_hpp */
