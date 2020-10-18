#include "date.h"
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <time.h>
#define CLOCKS_PER_SEC  ((clock_t)1000)
using namespace std;

Date::Date() {}
void Date::count_clock()
{
    clock_t t1 = clock();
    for (int i = 0; i < 1000000; i++) 
    {
        pow(2, i);
    }
    //calculate the difference of the clock/ per second
    //times 1000 to get the microsecond
    cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
}
