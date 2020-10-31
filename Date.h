#pragma once
#include <ctime>

class Date {
private:
	const static int dayUnit = 5; // 5 seconds = 1 day
public:
	static int getDays();
};