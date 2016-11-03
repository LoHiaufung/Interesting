#include<iostream>
#include<sstream>
#include"Date.h"
 
using namespace std;
/*
 
    private:
        int year;
        int month;
        int day;
*/
        Date::Date(int y, int m, int d) {year = y; month = m; day = d;}
        Date::Date(const Date& in) {
            year = in.year;
            month = in.month;
            day = in.day;
        }
        Date::~Date() {
            // cout << "Destructor: " << toString() <<endl;
        }
        std::string Date::toString() const {
            stringstream out;
            out << "[" << year << "-" << month << "-" << day << "]";
            return out.str();
        }
        Date Date::after(int day) {
            Date ans = *this;
            while (day--) ++ans;
            return ans;
        }
        int& Date::operator[] (int index) {
            if (index == 0) return year;
            else if (index == 1) return month;
            else return day;
        }
        bool Date::operator< (const Date& other) {
            if (year < other.year) {
                return true;
            } else if (year > other.year) {
                return false;
            } else {
                if (month < other.month) {
                    return true;
                } else if (month > other.month) {
                    return false;
                } else {
                    if (day < other.day)
                        return true;
                    return false;
                }
            }
        }
        bool Date::operator>(const Date& other) {
            if (year == other.year && month == other.month
            && day == other.day) return false;
            return !((*this) < other);
        }
        bool Date::operator==(const Date& other) {
            if (year == other.year && month == other.month
            && day == other.day) return true;
            return false;
        }
        bool Date::operator!=(const Date& in) {
            return !((*this) == in);
        }
        Date& Date::operator= (const Date& in) {
            year = in.year;
            month = in.month;
            day = in.day;
            return *this;
        }
        Date& Date::operator++() {
            day++;
            if (isValid()) {
                return *this;
            } else {
                int temp = max_date(year, month);
                month += day / temp;
                day %= temp;
                while (month > 12) { year++; month -= 12;}
            }
            return *this;
        }  //  ++x
        Date Date::operator++(int n) {
            Date temp = *this;
            ++(*this);
            return temp;
        }  // x++
        void Date::setDay(const int& in) {
            day = in;
        }
        bool Date::isValid() {
            if (day <= max_date(year, month) && day >= 1
            && month >= 1 && month <= 12 && year > 0)
                return true;
            return false;
        }
 
        ostream& operator<<(ostream& out, const Date& obj) {
            out << obj.toString()<< endl;
            return out;
        }
        istream& operator>>(istream& in , Date& obj) {
            int temp = 0;
            in >> temp; obj.year = temp;
            in >> temp; obj.month = temp;
            in >> temp; obj.day = temp;
            return in;
        }
        int Date::max_date(int y, int m) {
            if (m != 2) {
                if (m == 4 || m == 6 || m == 9 || m == 11)
                    return 30;
                return 31;
            } else {
                if ((y % 100 != 0 && y % 4 == 0) ||
                (y % 100 == 0 && y % 400 == 0))  // 闰年
                    return 29;
                return 28;
            }
        }