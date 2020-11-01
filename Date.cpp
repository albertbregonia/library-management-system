#include "Date.h"

int Date::getDays() { return (clock() / CLOCKS_PER_SEC) / dayUnit; }