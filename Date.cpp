#include "Date.h"
#include <time.h>
#include <iostream>

using namespace std;


int Date::getDays() 
{ 
	clock_t start, end;
	double x = 1.5;

	start = clock();
	end = clock();
	cout << "time generate" << (double)(end - start) / CLOCKS_PER_SEC << endl;
	return (clock() / CLOCKS_PER_SEC) / dayUnit; 
}
