//
// Created by 22942 on 2021/6/9.
//

#include "account.h"
#include <iostream>
using namespace std;
void accountRecord::show() const {
    date.showDate();
    cout << date.getYear()<< "-" << date.getMonth() <<"-" << date.getDay() << "   "<< acc->getId() << "   " << desc<< endl;
}

void account::record(const Date& date,const string& desc){
    account::recordMap.insert(make_pair(date, accountRecord(date,this,desc)));
}

void account::query(const Date &begin, const Date &end) const{
    if(begin<end){
        _Rb_tree_const_iterator<pair<const Date,accountRecord>> iter1 = recordMap.lower_bound(begin);
        _Rb_tree_const_iterator<pair<const Date,accountRecord>> iter2 = recordMap.upper_bound(end);
        for(_Rb_tree_const_iterator<pair<const Date,accountRecord>> iter = iter1;iter != iter2;++iter){
            iter ->second.show();
        }
    }
    else cout << "·Ç·¨ÊäÈë";
}
