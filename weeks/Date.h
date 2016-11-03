#include<iostream>
#include<string>
 
using namespace std;
 
class Date {
    public:
        Date(int = 0, int = 0 , int = 0);
        Date(const Date&);
        ~Date();
        std::string toString() const;
        Date after(int day);
        int& operator[] (int index);
        friend ostream& operator<<(ostream& out, const Date&);
        friend istream& operator>>(istream& in , Date&);
        bool operator< (const Date&);
        bool operator>(const Date& in);
        bool operator==(const Date& in);
        bool operator!=(const Date& in);
        Date& operator= (const Date&);
        Date& operator++();  // ++x
        Date operator++(int);  //  x++
        void setDay(const int&);
        bool isValid();
    private:
        int max_date(int y, int m);
        int year;
        int month;
        int day;
};