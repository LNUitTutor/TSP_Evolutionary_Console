#pragma once
#include <iostream>
// ��������� ����� ������� �� �������� ����� �� ������
struct Point
{
	double x;
	double y;
	Point(double a = 0, double b = 0) :x(a), y(b) {}
};
// �������� ��������� ������������� ������ ��������
std::ostream& operator<<(std::ostream& os, const Point& p);