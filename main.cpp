//
// Created by mby on 09/06/2020.
//
#include "Price.h"
int main()
{
    Price<int> p1(4,6);
    Price<int> p2(2,6);
    std::cout<<p2<<std::endl;
    double d =p1;
    std::cout<<d<<std::endl;
//    Price<char> p1(4,6);
    return 1;
}

