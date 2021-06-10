//
// Created by 22942 on 2021/6/9.
//

#ifndef BOOK_DEMO_ACCOUNT_H
#define BOOK_DEMO_ACCOUNT_H
#include "Date.h"
#include <string>
#include <iostream>
#include <map>
typedef std::string string;
typedef std::ostream ostream;

class account;
class accountRecord{
private:
    Date date;
    const account* acc;
    string desc;
public:
    accountRecord(const Date date,const account* Acc,const string& desc):acc(Acc),desc(desc), date(date){}
    void show()const;
};
typedef std::multimap<Date,accountRecord> RecordMap;

class account{
public:
    account(const string& id):id(id){}
    void record(const Date& date,const string& desc);
    string getId() const{return id;}
    void query(const Date & begin,const Date& end)const;
    ostream &operator <<(ostream& out) {
        out << id;
        return out;
    }
private:
    string id;
    RecordMap recordMap;
};

#endif //BOOK_DEMO_ACCOUNT_H
