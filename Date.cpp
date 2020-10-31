#include "Date.h"
#include <ctime>
#include <iostream>

using namespace std;


int Date::getDays() 
{ 
	clock_t time1 = clock();
	double sum = 0;
	for (int i = 0; i < 100000000; i++) {
		sum += sqrt(i);
	}
	clock_t time2 = clock();

	double t = ((double)(time2 - time1)) / CLOCKS_PER_SEC;
	cout << "CLOCKS_PER_SEC: " << CLOCKS_PER_SEC << endl;
	cout << "Process running time: " << t << "s" << endl;
	return (clock() / CLOCKS_PER_SEC) / dayUnit; 
}
