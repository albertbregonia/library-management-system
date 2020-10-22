//Sample Program to Exemplify <ctime>

#include <ctime>
#include <iostream>
using namespace std;

int main() {
	int last(-1);
	while (1) {
		int current(clock() / CLOCKS_PER_SEC);
		// CLOCK_PER_SEC is a constant built into C++, 'current' is the current runtime in seconds
		if (last != current) //Print out the runtime every second
			cout << current << endl;
		last = current;
	}
}