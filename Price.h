//
// Created by mby on 09/06/2020.
//
#ifndef PRICE_PRICE_H
#define PRICE_PRICE_H

#include <cstdlib>
#include <math.h>
#include <iostream>
template <typename T >
class Price {
public:
    Price(T dollar =0, T cents=0);
    T getDollar() const;
    T getCents() const;
    bool isPositive()const;
    Price&operator+=(const Price &p);
    Price&operator-=(const Price &p);
    Price&operator*=(const Price &p);
    Price&operator/=(const Price &p);
    Price&operator%=(const Price &p);
    Price&operator=(const Price& p1);
    Price operator ++(int);
    Price operator ++();
    operator double (){ return getDouble();}
    void fixed_cents(T &dollar, T &cents) const;
    static const short int cents_in_dollar=100;
private:
    T m_dollar;
    T m_cents;
    bool m_sign;
    bool isOverflow(T &dollar, T &cents)const;
    double getDouble()const;
};
/********************private functions*********************/
template <typename T>
inline void Price<T>::fixed_cents(T &dollar, T &cents) const{
        dollar+=cents/cents_in_dollar;
        cents=cents%cents_in_dollar;

}
template <typename T>
inline bool Price<T>::isOverflow(T &dollar, T &cents) const {
    return true;
}
template <typename T>
inline double Price<T>::getDouble() const{
    double d=0;
    if(m_sign){
        d+=(double(m_dollar));
        d+=double(m_cents)/100;
    }
    else{
        d-=(double(m_dollar));
        d-=double(m_cents)/100;
    }
    return d;
}
template <typename T>
inline Price<T>::Price(T dollar, T cents):m_dollar(abs((dollar))),m_cents(abs((cents))){
   if(dollar>0 && cents>0){
       m_sign= true;
   }
   else{
       m_sign = false;
   }
   if(cents>100){
       fixed_cents(m_dollar,m_cents);
   }
}
/*******************get functions*********************/
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
/******************global functions**************************/
template <typename T >
Price<T> operator+(const Price<T>& p1, const Price<T> & p2);
template <typename T >
Price<T> operator-(const Price<T>& p1, const  Price<T> &p2);
template <typename T >
Price<T> operator*(const Price<T>& p1, const  Price<T> &p2);
template <typename T >
Price<T> const operator-(const Price<T>& p);
template <typename T >
bool operator==(const Price<T>& p1, const Price<T>& p2);
template <typename T >
bool operator!=(const Price<T>& p1, const Price<T>& p2);
template <typename T >
bool operator>=(const Price<T>& p1, const Price<T>& p2);
template <typename T >
bool operator<=(const Price<T>& p1, const Price<T>& p2);
template <typename T >
bool operator<(const Price<T>& p1, const Price<T>& p2);
template <typename T >
bool operator>(const Price<T>& p1, const Price<T>& p2);
template <typename T >

inline Price<T> operator+(const Price<T>& p1, const  Price<T> & p2){
    T dollar ,cents;
    if(p1.getDollar()+p2.getDollar()> pow(2,sizeof(T))){
//        throw exception;
    }
    if(p1.isPositive() == p2.isPositive())
    {
        dollar = (p1.getDollar()+p2.getDollar())*(p1.isPositive()*2-1);
        cents = p1.getCents()+p2.getCents();
        return Price<T>(dollar,cents);
    }
    if(p1.isPositive()== true){
        return p1-(-p2);
    }
    return p2-(-p1);

}
template <typename T >
inline Price<T> operator-(const Price<T>& p1, const  Price<T> &p2) {
    if(p1.isPositive()==p2.isPositive()){
        T dollar,cents;
        if(p1.isPositive()==true){
            dollar=p1.getDollar()-p2.getDollar();
            cents=p1.getCents()-p2.getCents();
            if(dollar>0 && cents<0){
                dollar--;
                cents = (-1)*cents;
                if(dollar==0){
                    cents = 0-cents;
                }
            }
            else{
                if(dollar<0 && cents>0){
                    dollar++;
                    if(dollar==0){
                        cents = 0-cents;
                    }
                }
            }
            return Price<T>(dollar,cents);

        }
        else{
            return (-p2 )- (-p1);
        }
    }
    if(p1.isPositive()==true)
    {
        Price<T> p (p1+(-p2)) ;
        return p;
    }
    return p1+(-p1);
}
template <typename T>
inline const Price<T> operator-(const Price<T>& p)  {
    return p *(Price<int>(-1));
}
template <typename T>
inline bool operator==(const Price<T>& p1, const Price<T>& p2){
    return ((p1.getDollar()==p2.getDollar()) && (p1.getCents()==p2.getCents())) && (p1.isPositive()==p2.isPositive());
}
template <typename T>
inline bool operator!=(const Price<T>& p1, const Price<T>& p2){
    return !(p1==p2);
}
template <typename T>
inline bool operator >(const Price<T>& p1, const Price<T>& p2){
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
template <typename T>
inline bool operator <(const Price<T>& p1, const Price<T>& p2){
    return (!(p1>p2)) && (p1!=p2);
}
template <typename T>
inline bool operator <= (const Price<T>& p1, const Price<T>& p2){
    return !(p1>p2);
}
template <typename T>
inline bool operator >=(const Price<T>& p1, const Price<T>& p2){
    return (p1>p2) || (p1==p2);
}
template <typename T>
std::ostream& operator<<(std::ostream & cout , const Price<T> &p1){
    cout<<p1;
    return cout;
}
template <typename T >
inline Price<T> operator * (const Price<T>& p1, const  Price<T> &p2){
    T dollar ,cents;
    dollar = p1.getDollar()*p2.getDollar();
    cents = p1.getDollar()*p2.getCents()+ p2.getDollar()*p1.getCents()+p1.getCents()*p2.getCents()/10;
    if(cents>100)
        p1.fixed_cents(dollar,cents);
    return Price<T> (dollar,cents);
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
template <typename  T>
inline Price<T> Price<T>::operator++(int){
    return Price<T>(m_dollar+1,m_cents);
}
template <typename T>
inline Price<T> Price<T>::operator++() {
    return Price<T>(m_dollar+1,m_cents);
}
template <typename T>
inline Price<T>& Price<T>::operator+=(const Price<T> &p) {
    *this = *this + p;
}
template <typename T>
inline Price<T>& Price<T>::operator-=(const Price<T> &p) {
    *this = *this - p;
}
template <typename T>
inline Price<T>& Price<T>::operator*=(const Price<T> &p) {
    *this = *this * p;
}
template <typename T>
inline Price<T>& Price<T>::operator/=(const Price<T> &p) {
    *this = *this / p;
}
template <typename T>
inline Price<T>& Price<T>::operator%=(const Price<T> &p) {
    *this = *this % p;
}
//template <typename T>
////inline Price<T>& Price<T>::operator=(const Price &p1) {
////
////}
#endif //PRICE_PRICE_H
