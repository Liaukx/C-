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
        cout << "��־��Ϣ����ʧ�ܣ������ļ�·��"<< endl;
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
        cout << "��־��Ϣ���سɹ�" << endl;
    }
}

//�����˻���Ϣ
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
//����ͼ����Ϣ
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
        fin.close();    //����\nʱ fin.eof = 0Ҳ���ǻ����һ�Σ����ԣ�Book_num��ʼ��Ϊ-1
        return true;
    }
}
//�鿴�˻��Ƿ��Ѿ�ע��,��δע��,ע�����û�
int login(){
    cout << "������id  " ;

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
            cout << "��������id ����1 ;ע����id���� 2  ";
        }
        char c;
        cin >> c;
        if(c == '2'){
            cout << "������id" << endl;
            cin >> id;
            accounts.emplace_back(id);
            ++Accounts_num;
            return Accounts_num-1;
        }
    }
}
//�Թ����ߺ���ͨ�û��ṩ��ͬ�Ľ���
void UsersLoad(int ord){
    //cout << getchar();
    cout << "��ӭʹ�ñ�ͼ�����ϵͳ" << endl;
    cout << "����������B,����������R,���ͼ���б�������L,�˳�ϵͳ����E,��ѯ�軹��¼����Q" << endl;
    bool end = false;

    //getchar();
    while (!end){
        char c;
        cin >> c;
        switch (c) {
            case 'B':
            {
                cout << "���������գ��Կո����" << endl;
                int year,month,day;
                cin >> year>> month >> day;
                Date date(year,month,day);
                cout << "������������Ŀ"<< endl;
                string Title;
                int num;
                bool flag = false;
                cin >> Title >> num;
                for(int i = 0;i<Books.size();++i){
                    if (Books[i].getTitle() == Title){
                        flag = true;
                        if(schedule(Books[i]).Borrow(num)){

                            cout << "����ɹ�" << endl;
                            string msg = accounts[ord].getId()+string(" B ")+Title+" "+Books[i].getISBN();
                            accounts[ord].record(date,msg);
                            FileLog(date,msg);
                            ++Log_num;
                            break;
                        } else{
                            cout <<"��治��" << endl;
                        }
                    }
                }

                if (!flag) cout << "sorry���Ҳ����Ȿ��" << endl;
                break;
            }
            case 'R':
            {
                cout << "���������գ��Կո����" << endl;
                int year,month,day;
                cin >> year>> month >> day;
                Date date(year,month,day);
                string Title;
                int num;
                cout << "������������Ŀ���Կո����" << endl;
                cin >> Title >> num;
                for(int i = 0;i<Books.size();++i){
                    if (Books[i].getTitle() == Title){
                        schedule(Books[i]).Return(num);
                        cout << "����ɹ�" << endl;
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
                cout << "������ֹʱ���Կո����" << endl;
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
                cout<< "��ȫ�˳�" << endl;
                end = true;
                break;
            }
            default:{
                cout << "�Ƿ�ָ��" << endl;
                break;
            }
        }
    }
}
void AdmLoad(){
    //getchar();
    cout << "����������" <<endl;
    string key;

    getline(cin,key);
    if(key != KEY){
        cout << key;
        cout << KEY;
        cout << "��������"<< endl;
        return;
    }
    else{
        cout << "�������� ����A ��ɾ��ͼ�� ����D �����ȫ�� ����L,�˳�����E "<< endl;
        bool end = false;
        while (!end){
            char c;
            cin >> c;
            switch (c) {
                case 'A':
                {
                    cout << "�������������ߣ�����ţ��۸���Ŀ���Կո����" << endl;
                    string Title,writer,ISBN;
                    double price;
                    int num;
                    cin >> Title >> writer >> ISBN >> price >> num ;
                    //cout << Title;
                    Books.emplace_back(Title,writer,ISBN,price,num);
                    //Books.push_back(Book(Title,writer,ISBN,price,num));
                    //cout << Books[++Book_num];
                    cout << "��ӳɹ�" << endl;
                    break;
                }
                case 'D':
                {
                    cout << "����Ҫɾ��ͼ��������" << endl;
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
                    cout << "ɾ���ɹ�,ϵͳ�����Զ��ر�" <<endl;
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
                    cout << "��ȫ�˳�" ;
                    break;
                }
                default: {
                    //getchar();
                    cout << " �Ƿ�ָ��" << endl;
                    break;
                }
            }
        }
        return;
    }
}
void loadIn(){
    cout << "����Ƕ��������U,����ǹ����������A"<< endl;
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
            cout << "������������" << endl;
        }
    }
    //return;
}
int main() {
    if(!loadAccounts()){
        cout << "�����û���Ϣʧ�ܣ�����·��"<< endl;
    }else {
        cout << "�����û���Ϣ�ɹ�" << endl;
        logLoad();

        //����ͼ����Ϣ

        if (!loadBook()) {
            cout << "�����鼮��Ϣʧ�ܣ������ļ�·��" << endl;
        } else {
            cout << "ϵͳͼ����Ϣ�������" << endl;
            loadIn();
        }
    }
}