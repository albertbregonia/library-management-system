#pragma once
#include <ctime>

class Date {
private:
	const static int dayUnit = 60; // 1 minute = 1 day
public:
	static int getDays();
};