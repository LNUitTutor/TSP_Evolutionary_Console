#pragma once
#include <iostream>
// структура поєднує абсцису та ординату точки на площині
struct Point
{
	double x;
	double y;
	Point(double a = 0, double b = 0) :x(a), y(b) {}
};
// оператор виведення перевантажено заради зручності
std::ostream& operator<<(std::ostream& os, const Point& p);