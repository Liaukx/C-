//
// Created by 22942 on 2021/6/6.
//

#ifndef BOOK_DEMO_SCHEDULE_H
#define BOOK_DEMO_SCHEDULE_H
#include "Book.h"
#include "iostream"
#include "account.h"
class schedule{
private:
    Book &book;
public:
    schedule(Book& book):book(book){}
    bool Borrow(int amount = 1){
        if(book.getNum()>= amount) {
            book.setNum(book.getNum() - amount);
            return true;
        }
        else {
            return false;
        }
    }
    void Return(int amount = 1){
        book.setNum(book.getNum() + amount);
    }
};
#endif //BOOK_DEMO_SCHEDULE_H
