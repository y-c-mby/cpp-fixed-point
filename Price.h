//
// Created by mby on 09/06/2020.
//
#ifndef PRICE_PRICE_H
#define PRICE_PRICE_H

#include <cstdlib>
#include <math.h>
#include <cmath>
#include <iostream>
#include <stdbool.h>
#include <typeinfo>
#include <string>
#include <sstream>
//#include <typeindex>
//template <typename T>
//struct getType
//{
//    enum {value=decltype(T)};
//};
//#include <type_traits>
template <unsigned int SIZE,typename T=int >
class FixedPoint {
public:
    FixedPoint(T dollar =0, int cents=0);
    T getDollar() const;
    int getCents() const;
    bool isPositive()const;
    FixedPoint&operator+=(const FixedPoint &p);
    FixedPoint&operator-=(const FixedPoint &p);
    FixedPoint&operator*=(const FixedPoint &p);
    FixedPoint&operator/=(const FixedPoint &p);
    FixedPoint&operator%=(const FixedPoint &p);
    FixedPoint&operator=(int i);
    FixedPoint operator ++(int);
    FixedPoint operator ++();
    FixedPoint operator --(int);
    FixedPoint operator --();
    const size_t getPrecision() const;
    std::string asString()const;
//    operator double ();
    void fixed_cents(T &dollar, int &cents) const;
    void isOverflow(T &dollar, T &add)const;
    static const int SIZE_IN_DOLLAR;
    static const T theType;
private:
    T m_dollar;
    int m_cents;
    bool m_sign;
    double getDouble()const;
};
template <unsigned int SIZE,typename T>
const int FixedPoint<SIZE ,T>::SIZE_IN_DOLLAR((int)pow(10,SIZE));
/********************private functions*********************/
template <unsigned int SIZE,typename T >
inline void FixedPoint<SIZE,T>::fixed_cents(T &dollar, int &cents) const{
        if(dollar+int(cents/SIZE_IN_DOLLAR)<dollar)
            throw std::out_of_range("overflow type");

        dollar+=int(cents/SIZE_IN_DOLLAR);
        cents=cents%SIZE_IN_DOLLAR;
}
template <unsigned int SIZE,typename T>
inline void FixedPoint<SIZE,T>::isOverflow(T &dollar, T &add)const{
    if((dollar+add)<dollar)
        throw std::out_of_range("overflow type");
}
template <unsigned int SIZE,typename T>
inline double FixedPoint<SIZE,T>::getDouble() const{
    double d=0;
    if(m_sign){
        d+=(double(m_dollar));
        d+=double(m_cents)/SIZE_IN_DOLLAR;
    }
    else{
        d-=(double(m_dollar));
        d-=double(m_cents)/SIZE_IN_DOLLAR;
    }
    return d;
}
template <unsigned int SIZE,typename T>
inline FixedPoint<SIZE,T>::FixedPoint(T dollar, int cents):m_dollar(0),m_cents(0),m_sign(true){
   if((dollar>=0) && (cents>=0)){
       m_sign= true;
   }
   else{
       m_sign = false;
   }
   m_dollar=abs(dollar);
   m_cents=abs(cents);
   if(cents> SIZE_IN_DOLLAR){
       fixed_cents(m_dollar,m_cents);
   }
}
template <unsigned int SIZE,typename T>
inline const size_t FixedPoint<SIZE,T>::getPrecision()const {
    size_t count=SIZE;
    int tmp = m_cents;
    while (tmp>0){
        if(tmp%10!=0)
            break;
        count--;
        tmp/=10;
    }
    return count;
}
template <typename T>
std::string to_string(T t){
    std::ostringstream oss;
    oss<<t;
    return  oss.str();
}
template <unsigned int SIZE,typename T>
inline std::string FixedPoint<SIZE ,T>::asString() const{
    std::string str=to_string(*this);
    return str;
}
/*******************get functions*********************/
template <unsigned int SIZE,typename T>
inline int FixedPoint<SIZE,T>::getCents() const{
    return m_cents;
}
template <unsigned int SIZE,typename T>
inline T FixedPoint<SIZE,T>::getDollar() const {
    return m_dollar;
}
template <unsigned int SIZE,typename T>
inline bool FixedPoint<SIZE,T>::isPositive() const {
    return m_sign;
}
/******************global functions**************************/
template <unsigned int SIZE,typename T>
FixedPoint<SIZE,T> operator+(const FixedPoint<SIZE,T>& p1, const FixedPoint<SIZE,T> & p2);
template <unsigned int SIZE,typename T>
FixedPoint<SIZE,T> operator-(const FixedPoint<SIZE,T>& p1, const FixedPoint<SIZE,T> & p2);
template <unsigned int SIZE,typename T>
FixedPoint<SIZE,T> operator*(const FixedPoint<SIZE,T>& p1, const FixedPoint<SIZE,T> & p2);
template <unsigned int SIZE,typename T>
FixedPoint<SIZE,T> const operator-(const FixedPoint<SIZE,T>& p);
template <unsigned int SIZE,typename T>
bool operator==(const FixedPoint<SIZE,T>& p1, const FixedPoint<SIZE,T> & p2);
template <unsigned int SIZE,typename T>
bool operator!=(const FixedPoint<SIZE,T>& p1, const FixedPoint<SIZE,T> & p2);
template <unsigned int SIZE,typename T>
bool operator>=(const FixedPoint<SIZE,T>& p1, const FixedPoint<SIZE,T> & p2);
template <unsigned int SIZE,typename T>
bool operator<=(const FixedPoint<SIZE,T>& p1, const FixedPoint<SIZE,T> & p2);
template <unsigned int SIZE,typename T>
bool operator<(const FixedPoint<SIZE,T>& p1, const FixedPoint<SIZE,T> & p2);
template <unsigned int SIZE,typename T>
bool operator>(const FixedPoint<SIZE,T>& p1, const FixedPoint<SIZE,T> & p2);

template <unsigned int SIZE,typename T>
inline FixedPoint<SIZE,T> operator+(const FixedPoint<SIZE,T>& p1, const  FixedPoint<SIZE,T> & p2){
    T dollar ;
    int cents;
    if(p1.isPositive() == p2.isPositive())
    {
        if((p1.getDollar()+p2.getDollar())<p1.getDollar()){
            throw std::overflow_error("overflow type");
        }
        dollar = (p1.getDollar()+p2.getDollar())*(p1.isPositive()*2-1);
        cents = p1.getCents()+p2.getCents();
        return FixedPoint<SIZE,T>(dollar,cents);
    }
    if(p1.isPositive()== true){
        return p1-(-p2);
    }
    return p2-(-p1);

}
template <unsigned int SIZE,typename T>
inline FixedPoint<SIZE,T> operator-(const FixedPoint<SIZE,T>& p1, const  FixedPoint<SIZE,T> &p2) {
    if(p1.isPositive()==p2.isPositive()){
        T dollar;
        int cents;
        if(p1.isPositive()==true){
            dollar=p1.getDollar()-p2.getDollar();
            cents=p1.getCents()-p2.getCents();
            if(dollar>0 && cents<0){
                dollar--;
                cents = (-1)*cents;
                if(dollar==0){
                    cents = FixedPoint<SIZE>::SIZE_IN_DOLLAR-cents;
                }
            }
            else{
                if(dollar<0 && cents>0){
                    dollar++;
                    if(dollar==0){
                        cents = -FixedPoint<SIZE>::SIZE_IN_DOLLAR-cents+cents;
                    }
                }
            }
            return FixedPoint<SIZE,T>(dollar,cents);

        }
        else{
            return (-p2 )- (-p1);
        }
    }
    if(p1.isPositive()==true)
    {
        return p1+(-p2);
    }
    return p1+(-p1);
}
template <unsigned int SIZE,typename T>
inline const FixedPoint<SIZE,T> operator-(const FixedPoint<SIZE,T>& p)  {
    return p *(FixedPoint<SIZE,T>(-1));
}
template <unsigned int SIZE,typename T>
inline bool operator==(const FixedPoint<SIZE,T>& p1, const FixedPoint<SIZE,T>& p2){
    return (((p1.getDollar()==p2.getDollar())&& (p1.getCents()==p2.getCents()))&& p1.isPositive()==p2.isPositive());
}
template <unsigned int SIZE,typename T>
inline bool operator!=(const FixedPoint<SIZE,T>& p1, const FixedPoint<SIZE,T>& p2){
    return !(p1==p2);
}
template <unsigned int SIZE,typename T>
inline bool operator >(const FixedPoint<SIZE,T>& p1, const FixedPoint<SIZE,T>& p2){
    if(p1.isPositive()==p2.isPositive())
    {
        if(p1.isPositive())
            return ((p1.getDollar()>p2.getDollar()) || (p1.getDollar()==p2.getDollar() && p1.getCents()>p2.getCents()));
        return ((p1.getDollar()<p2.getDollar()) || (p1.getDollar()==p2.getDollar() && p1.getCents()<p2.getCents()));
    }
    if(p1.isPositive())
        return true;
    return false;
}
template <unsigned int SIZE,typename T>
inline bool operator <(const FixedPoint<SIZE,T>& p1, const FixedPoint<SIZE,T>& p2){
    return (!(p1>p2)) && (p1!=p2);
}
template <unsigned int SIZE,typename T>
inline bool operator <= (const FixedPoint<SIZE,T>& p1, const FixedPoint<SIZE,T>& p2){
    return !(p1>p2);
}
template <unsigned int SIZE,typename T>
inline bool operator >=(const FixedPoint<SIZE,T>& p1, const FixedPoint<SIZE,T>& p2){
    return (p1>p2) || (p1==p2);
}
template <unsigned int SIZE,typename T>
std::ostream& operator<<(std::ostream & cout , const FixedPoint<SIZE,T> &p1){
    cout<<p1.getDollar()<<".";
    unsigned int help=SIZE-1;
    int tmp = p1.getCents();
    while(tmp>0){
       if(tmp<pow(10,help))
           cout<<0;
       else{
           cout<<tmp/(int)pow(10,help);
           tmp = tmp%(int)pow(10,help);
       }
       help--;
    }
    return cout;
}
template <unsigned int SIZE,typename T>
inline FixedPoint<SIZE,T> operator * (const FixedPoint<SIZE,T>& p1, const FixedPoint<SIZE,T>& p2){
    T dollar ,cents;
    if(p1.getDollar()*p2.getDollar()<p1.getDollar())
        throw std::overflow_error("overflow type");
    dollar = p1.getDollar()*p2.getDollar();
    cents = p1.getDollar()*p2.getCents()+ p2.getDollar()*p1.getCents()+p1.getCents()*(p2.getCents()/10);
    return FixedPoint<SIZE,T> (dollar,cents);
}
//template <typename T , typename U>
//inline Price<T> operator/(const Price<T>& p1, const  Price<U> &p2){
//    size_t new_price;
//    new_price = p1.getDollarAndCents()/p2.getDollarAndCents();
//    if(p1.isPositive()!=p2.isPositive()){
//        new_price =new_price*-1;
//    }
//    return Price<T>(new_price/100,new_price%100);
//}
//inline Price<T> operator%(const Price<T>& p1, const  Price<U> &p2){
//    size_t new_price;
//    new_price = p1.getDollarAndCents()%p2.getDollarAndCents();
//    if(p1.isPositive()!=p2.isPositive()){
//        new_price =new_price*-1;
//    }
//    return Price<T>(new_price/100,new_price%100);
//}
/****************operator functions******************/
template <unsigned int SIZE,typename T>
inline FixedPoint<SIZE,T> FixedPoint<SIZE,T>::operator++(int){

    FixedPoint<SIZE,T> tmp(*this);
    if(m_sign){
        if((m_dollar+1)<m_dollar)
            throw std::overflow_error("overflow");
        this->m_dollar++;
    }
    else
        this->m_dollar--;
    return tmp;
}
//template <typename T>
template <unsigned int SIZE,typename T>
inline FixedPoint<SIZE,T> FixedPoint<SIZE,T>::operator++(){
    if(m_sign){
        if((m_dollar+1)<m_dollar)
            throw std::overflow_error("overflow");
        this->m_dollar++;
    }
    else
        this->m_dollar--;
    return FixedPoint<SIZE,T>(*this);
}
template <unsigned int SIZE,typename T>
inline FixedPoint<SIZE,T>& FixedPoint<SIZE,T>::operator+=(const FixedPoint<SIZE,T> &p) {
    *this = *this + p;
}
template <unsigned int SIZE,typename T>
inline FixedPoint<SIZE,T>& FixedPoint<SIZE,T>::operator-=(const FixedPoint<SIZE,T> &p) {
    *this = *this - p;
}
template <unsigned int SIZE,typename T>
inline FixedPoint<SIZE,T>& FixedPoint<SIZE,T>::operator*=(const FixedPoint<SIZE,T> &p) {
    *this = *this * p;
}
template <unsigned int SIZE,typename T>
inline FixedPoint<SIZE,T>& FixedPoint<SIZE,T>::operator/=(const FixedPoint<SIZE,T> &p){
    *this = *this / p;
}
template <unsigned int SIZE,typename T>
inline FixedPoint<SIZE,T>& FixedPoint<SIZE,T>::operator%=(const FixedPoint<SIZE,T> &p) {
    *this = *this % p;
}
template <unsigned int SIZE,typename T>
inline FixedPoint<SIZE,T>& FixedPoint<SIZE,T>::operator=(int i) {
    m_dollar=abs(i);
    m_cents = 0;
    m_sign = i>0? true: false;
    return *this;
}
template <unsigned int SIZE,typename T>
inline FixedPoint<SIZE,T> FixedPoint<SIZE,T>::operator--(int){
    FixedPoint<SIZE,T> tmp(*this);
    if(m_sign)
        this->m_dollar--;
    else {
        if ((m_dollar + 1) < m_dollar)
            throw std::overflow_error("overflow");
        this->m_dollar++;
    }
    return tmp;
}
//template <typename T>
template <unsigned int SIZE,typename T>
inline FixedPoint<SIZE,T> FixedPoint<SIZE,T>::operator--(){
    if(m_sign)
        this->m_dollar--;
    else{
        if((m_dollar+1)<m_dollar)
            throw std::overflow_error("overflow");
        this->m_dollar++;
    }
    return FixedPoint<SIZE,T>(*this);
}
#endif //PRICE_PRICE_H
