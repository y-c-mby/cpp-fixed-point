//
// Created by mby on 09/06/2020.
//
#include "Price.h"
#include "StringsToWords.h"
template <unsigned int S, typename T =int>
struct fp{
    typedef FixedPoint<S,T> type;
};
std::string makeMoney(FixedPoint<2> price){
    std::string numstr = price.asString();
    std::size_t  len =numstr.length();
    std::size_t afterpoint = price.getPrecision();
    std::string dollarstr = convert_to_words(numstr,0,len-afterpoint-1);
    std::string centstr = convert_to_words(numstr,len-afterpoint,len);
    return  dollarstr + " dolllars "+" and " + centstr + " cents ";
}
int main()
{
    FixedPoint<2> p1(454,1);
    FixedPoint<2> p2(1234,30);
    std::cout<<p1<<" the precision "<<(p1.getPrecision())<<std::endl;
    std::cout<<p2<<" the precision "<<(p2.getPrecision())<<std::endl;
    p1 = ++p2;
    std::cout<<(p1)<<std::endl;
    p1 =p2++;
    std::cout<<p1<<std::endl;
    std::cout<<p2<<std::endl;
    std::cout<<p1.getPrecision()<<std::endl;
    std::cout <<makeMoney(p1)<<std::endl;
//    FixedPoint<5>::theType var=0;
    return 1;
}

