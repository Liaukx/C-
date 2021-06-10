#include <iostream>
#include <iosfwd>
#include <vector>
#include <string>
#include <algorithm>
#include "Book.h"
#include "schedule.h"

using  namespace  std;
vector<account> accounts;
vector<Book> Books;
int Accounts_num = -1;
int Log_num = -1;

string KEY ("Key Of Liau's System");

void FileLog(Date& date,string& msg){
    ofstream fout("log.txt",ios_base::app);
    fout << date.getYear() <<" "<< date.getMonth()<<" "<<date.getDay()<<" "<<msg /*<< "#"*/ << endl;
}

void logLoad(){
    ifstream fin("log.txt");
    if(! fin.is_open()){
        cout << "日志信息加载失败，请检查文件路径"<< endl;
    }else{
        string line;
        int year,month,day;
        string id;
        string cmd,title;
        string ISBN;
        while(fin >>year>>month >> day >> id >> cmd >>title>> ISBN){
            for(int i = 0;i<Accounts_num;++i){
                if(accounts[i].getId() == id){
                    string msg = id;
                    msg+=" ";
                    msg+=cmd;
                    msg+= " ";
                    msg += title;
                    msg+= " ";
                    msg+=ISBN;
                    accounts[i].record(Date(year,month,day),msg);
                    //cout <<msg ;
                }
            }
            ++Log_num;
        }
        cout << "日志信息加载成功" << endl;
    }
}

//加载账户信息
bool loadAccounts(){
    ifstream fin("accounts.txt");
    string id;
    if(! fin.is_open()) {
        return false;
    }
    else{
        while (!fin.eof()){
            fin >> id;
            accounts.emplace_back(id);
            ++Accounts_num;
        }
        fin.close();
        return true;
    }
}
//读入图书信息
bool loadBook(){
    ifstream fin;
    string title,writer,ISBN;
    double price;
    int num;
    fin.open("Book.txt");
    if(! fin.is_open()) {
        return false;
    }
    else{
        while (fin >> title >> writer >> ISBN >> price >> num){
            //fin >> title >> writer >> ISBN >> price >> num;
            Books.emplace_back(Book(title,writer,ISBN,price,num));
        }
        //cout << Book_num;
        fin.close();    //当有\n时 fin.eof = 0也就是会多算一次，所以，Book_num初始化为-1
        return true;
    }
}
//查看账户是否已经注册,若未注册,注册新用户
int login(){
    cout << "请输入id  " ;

    while (true){
        string id;
        cin >> id;
        bool flag = false;
        for(int i =0 ;i<Accounts_num;++i){
            if(accounts[i].getId() == id) {
                flag = true;
                return i;
            }
        }
        if(!flag){
            cout << "重新输入id 键入1 ;注册新id键入 2  ";
        }
        char c;
        cin >> c;
        if(c == '2'){
            cout << "请输入id" << endl;
            cin >> id;
            accounts.emplace_back(id);
            ++Accounts_num;
            return Accounts_num-1;
        }
    }
}
//对管理者和普通用户提供不同的界面
void UsersLoad(int ord){
    //cout << getchar();
    cout << "欢迎使用本图书管理系统" << endl;
    cout << "借书请输入B,还书请输入R,浏览图书列表请输入L,退出系统输入E,查询借还记录输入Q" << endl;
    bool end = false;

    //getchar();
    while (!end){
        char c;
        cin >> c;
        switch (c) {
            case 'B':
            {
                cout << "输入年月日，以空格隔开" << endl;
                int year,month,day;
                cin >> year>> month >> day;
                Date date(year,month,day);
                cout << "输入书名和数目"<< endl;
                string Title;
                int num;
                bool flag = false;
                cin >> Title >> num;
                for(int i = 0;i<Books.size();++i){
                    if (Books[i].getTitle() == Title){
                        flag = true;
                        if(schedule(Books[i]).Borrow(num)){

                            cout << "借书成功" << endl;
                            string msg = accounts[ord].getId()+string(" B ")+Title+" "+Books[i].getISBN();
                            accounts[ord].record(date,msg);
                            FileLog(date,msg);
                            ++Log_num;
                            break;
                        } else{
                            cout <<"库存不足" << endl;
                        }
                    }
                }

                if (!flag) cout << "sorry，找不到这本书" << endl;
                break;
            }
            case 'R':
            {
                cout << "输入年月日，以空格隔开" << endl;
                int year,month,day;
                cin >> year>> month >> day;
                Date date(year,month,day);
                string Title;
                int num;
                cout << "输入书名和数目，以空格隔开" << endl;
                cin >> Title >> num;
                for(int i = 0;i<Books.size();++i){
                    if (Books[i].getTitle() == Title){
                        schedule(Books[i]).Return(num);
                        cout << "还书成功" << endl;
                        string msg = accounts[ord].getId()+string(" R ")+Title+" "+Books[i].getISBN();
                        accounts[ord].record(date,msg);
                        FileLog(date,msg);
                        ++Log_num;
                        break;
                    }
                }
                break;
            }
            case 'L':
            {
                for(int i = 0;i<Books.size();++i){
                    Books[i].show();
                }
                break;
            }
            case 'Q':{
                Date date1,date2;
                int Year,Month,Day;
                cout << "输入起止时间以空格隔开" << endl;
                cin >>Year >> Month >> Day;
                date1 = Date(Year,Month,Day);
                cin >>Year >> Month >> Day;
                date2 = Date(Year,Month,Day);
                accounts[ord].query(date1,date2);
                break;
            }
            case 'E': {
                ofstream fout;
                fout.open("Book.txt",ios_base::out);
                for(int i = 0;i<Books.size();++i){
                    fout << Books[i] << endl;
                }
                fout.open("accounts.txt",ios_base::out);
                for(int i = 0;i<Accounts_num;++i){
                    fout << accounts[i].getId()<<endl;
                }
                cout<< "安全退出" << endl;
                end = true;
                break;
            }
            default:{
                cout << "非法指令" << endl;
                break;
            }
        }
    }
}
void AdmLoad(){
    //getchar();
    cout << "请输入密码" <<endl;
    string key;

    getline(cin,key);
    if(key != KEY){
        cout << key;
        cout << KEY;
        cout << "密码有误"<< endl;
        return;
    }
    else{
        cout << "增添新书 键入A ，删除图书 键入D ，浏览全部 键入L,退出键入E "<< endl;
        bool end = false;
        while (!end){
            char c;
            cin >> c;
            switch (c) {
                case 'A':
                {
                    cout << "输入书名，作者，索书号，价格，数目，以空格隔开" << endl;
                    string Title,writer,ISBN;
                    double price;
                    int num;
                    cin >> Title >> writer >> ISBN >> price >> num ;
                    //cout << Title;
                    Books.emplace_back(Title,writer,ISBN,price,num);
                    //Books.push_back(Book(Title,writer,ISBN,price,num));
                    //cout << Books[++Book_num];
                    cout << "添加成功" << endl;
                    break;
                }
                case 'D':
                {
                    cout << "输入要删除图书的索书号" << endl;
                    string ISBN;
                    fstream fout("Book.txt",ios::out);
                    cin >> ISBN;
                    cout << ISBN;
                    for(int i = 0;i<Books.size();++i){
                        cout << Books[i].getISBN() << endl;
                        if(Books[i].getISBN() != ISBN){
                            fout << Books[i];
                        }
                    }
                    cout << "删除成功,系统即将自动关闭" <<endl;
                    exit(0);
                    break;
                }
                case 'L':
                {
                    for(int i = 0;i<Books.size();++i){
                        Books[i].show();
                    }
                    break;
                }
                case 'E': {
                    getchar();
                    end = true;
                    ofstream fout;
                    fout.open("Book.txt",ios_base::out);
                    for(int i = 0;i<Books.size();++i){
                        fout << Books[i] ;
                    }
                    cout << "安全退出" ;
                    break;
                }
                default: {
                    //getchar();
                    cout << " 非法指令" << endl;
                    break;
                }
            }
        }
        return;
    }
}
void loadIn(){
    cout << "如果是读者请键入U,如果是管理者请键入A"<< endl;
    //getchar();
    char c ;
    cin >> c;
    switch (c) {
        case 'U':{
            getchar();
            int order;
            order = login();
            UsersLoad(order);
            break;
        }
        case 'A':{
            getchar();
            AdmLoad();
            break;
        }
        default: {
            cout << "您的输入有误" << endl;
        }
    }
    //return;
}
int main() {
    if(!loadAccounts()){
        cout << "导入用户信息失败，请检查路径"<< endl;
    }else {
        cout << "导入用户信息成功" << endl;
        logLoad();

        //读入图书信息

        if (!loadBook()) {
            cout << "导入书籍信息失败，请检查文件路径" << endl;
        } else {
            cout << "系统图书信息导入完成" << endl;
            loadIn();
        }
    }
}