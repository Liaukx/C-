//
// Created by 22942 on 2021/6/9.
//
#include "Date.h"
ostream& operator<< (ostream& fout,Date date){
    fout << date.getYear() <<"-" << date.getMonth() <<"-" << date.getDay() << "    ";
    return fout;
}
istream & operator >> (istream& fin, Date date){
    int year,month,day;
    char c1,c2;
    fin >> year >> c1 >> month >> c2 >> day;
    if(c1!='-' ||c2!= '-')
       std::cout << "ÊäÈë¸ñÊ½´íÎó" <<std::endl;
    date = Date(year,month,day);
    return fin;
}
