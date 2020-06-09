//
// Created by mby on 09/06/2020.
//

#ifndef PRICE_PRICE_H
#define PRICE_PRICE_H

#include <cstdlib>
template <typename T >
class Price {
public:
    Price(T dollar =0, T cents=0);
    T getDollar() const;
    T getCents() const;
    T getDollarAndCents() const;
    bool isPositive()const;
private:
    T m_dollar;
    T m_cents;
    bool m_sign;

};
template <typename T>
inline Price<T>::Price(T dollar, T cents):m_dollar(abs((dollar))),m_cents(abs((cents))){
   if(dollar>0 && cents>0){
       m_sign= true;
   }
   else{
       m_sign = false;
   }
}
template <typename T >
inline T Price<T>::getCents() const{
    return m_cents;
}
template <typename T >
inline T Price<T >::getDollar() const {
    return m_dollar;
}
template <typename T >
inline bool Price<T >::isPositive() const {
    return m_sign;
}
template <typename T >
inline T Price<T >::getDollarAndCents() const {
    return m_dollar*100+m_cents;
}
template <typename T , typename U>
inline Price<T> operator+(Price<T>& p1,  Price<U> & p2){
    int new_price ;
    if(p1.isPositive() == p2.isPositive())
    {
        new_price = (p1.getDollarAndCents()+p2.getDollarAndCents()*p1.isPositive());
    }
    if(p1.isPositive()== true){
        new_price=p1.getDollarAndCents()-p2.getDollarAndCents();
    }
    else
    {
        new_price=p2.getDollarAndCents()-p1.getDollarAndCents();
    }
    return Price<T>(new_price/100,new_price%100);
}
template <typename T , typename U>
inline Price<T> operator-(const Price<T>& p1, const  Price<U> &p2) {
    return p1+(p2*Price<char>(-1));
}
//template <template T , typename U>
//inline Price<T> operator * (const Price<T>& p1, const  Price<U> &p2)

#endif //PRICE_PRICE_H
