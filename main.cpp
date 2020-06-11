//
// Created by mby on 09/06/2020.
//
#include "Price.h"
int main()
{
    FixedPoint<3> p1(4,1);
    FixedPoint<3> p2(-6,30);
    std::cout<<(p1>p2)<<std::endl;
    p1 = ++p2;
    std::cout<<p1<<std::endl;
    p1 =p2++;
    std::cout<<p1<<std::endl;
    std::cout<<p2<<std::endl;
//    Price<int> p1(1,60);
//    Price<int> p2(-2,40);
//    std::cout<<p2<<std::endl;
//    double d =p1;
//    std::cout<<(p1+p2)<<std::endl;
//    std::cout<<(p1-p2)<<std::endl;
//    std::cout<<(p2*p1)<<std::endl;
//    std::cout<<d<<std::endl;
//    Price<long > p3(1,4);
//    Price<short int> p4(1,4);
//    Price<char> p1(4,6);
    return 1;
}

