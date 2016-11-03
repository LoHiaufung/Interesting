#include <time.h> 
#include <iostream>
#include "Date.h"

using namespace std;

int main( void ) 
{ 
    time_t t = time(0); 
	tm* curTime = localtime(&t); 
	int curYear = curTime -> tm_year  + 1900;
    int curMon =  curTime -> tm_mon  + 1;
    int curDay = curTime -> tm_mday;

    // current date
    Date curDate(curYear, curMon, curDay);
    // the date when the current term begin
    Date beginDate(2016, 8, 29);


    cout << "The term begin on:" << beginDate.toString() << endl;
    int diff = 0;
    while (curDate != beginDate) {beginDate++; diff++;}
    cout << "Today is in the " << (diff / 7)+1 << "th week";
    return 0; 
}