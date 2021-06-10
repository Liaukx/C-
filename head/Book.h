//
// Created by 22942 on 2021/6/5.
//

#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <iostream>
#include <fstream>
typedef std::string string;

class Book {
public:
    Book(const string &title,const string& writer,const string& IsBN,double &price,int num):title(title),writer(writer),ISBN(IsBN),price(price),num(num){}
    string getTitle() const{return title;}
    string getWriter()const{return writer;}
    string getISBN()const{return ISBN;}
    int getNum() const{return num;}
    double getPrice()const{return price;}
    void setNum(int n){num = n;}
    void show()const{std::cout << title << " " << writer << " " << ISBN << " " << price << "  " << num<<std::endl;};

private:
    string title;
    string writer;
    string ISBN;
    double price;
    int num;
};
std::ostream& operator<< (std::ostream& out ,const Book &book){
    out << book.getTitle() << " " << book.getWriter()<< " " << book.getISBN() << " " << book.getPrice() <<" " <<  book.getNum() << std::endl;
    return out;
}
#endif //BOOKSYSETM_BOOK_H
