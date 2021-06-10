//
// Created by 22942 on 2021/6/9.
//

#ifndef BOOK_DEMO_DATE_H
#define BOOK_DEMO_DATE_H
#include <iostream>
typedef std::ostream ostream;
typedef std::istream istream;
class Date{
    int year,month,day;
public:
    Date(int year=0,int month=0,int day=0):year(year),month(month),day(day){}
    int getYear() const{return year;}
    int getMonth() const{return month;}
    int getDay() const{return day;}
    void showDate() const {std::cout << getYear() <<"-" << getMonth() <<"-" << getDay() << "    "; }
    bool operator <(const Date date) const{
        if(year<date.getYear() || year>date.getYear()) return year<date.getYear();
        else if(month<date.getMonth() || month>date.getMonth()) return month<date.getMonth();
        else if(day < date.getDay() || day>date.getDay()) return day<date.getDay();
        else return false;
    }
};
ostream& operator<< (ostream& fout,Date date);
istream & operator >> (istream& fin, Date date);

#endif //BOOK_DEMO_DATE_H
