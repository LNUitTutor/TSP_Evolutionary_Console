#pragma once
#include "Point.h"

// ���� ���������� ����������� m_order �������� ���, ���������� m_towns ���� ������ ����.
// �� ������ "���������" ��� ��������� ����� ����, �쳺 ��������� � ������ ������� ��������.
// ���� ��������� �� ��������.

class Tour
{
private:
	static Point* m_towns;   // ���������� ���
	static int m_towns_count;

	int* m_order;            // ������������ ������
	double m_length;         // �������� �������
	void CalcLength();      // ����� ���������� �������
	// ����� ��� ������ ������������, ��������� ����
	Tour(int* permutation) :m_order(permutation)
	{
		CalcLength();
	}
public:
	// ����� ���������� ����� �������� ������������ �����
	static void InitTowns(Point* t, int n)
	{
		m_towns = t; m_towns_count = n;
	}
	~Tour() { delete[] m_order; }
	// �� ������������� ������� �������� - ����������: m_order[i] = i
	// �� ������� ����� ��������� ������� �������� ���������� �����
	Tour(bool permuted = false);
	// ��������� �� ��������� ������ ��� ������ � ������������
	Tour(const Tour& t);
	Tour& operator=(const Tour& t);
	// ����� ��������� ������� ��������� ��� ��������� ��������
	double Length() const { return m_length; }
	// ������ ������� ����: ���� � �������
	Tour Mutate();
	Tour Rotate();
	// ��������� ���������� ������������ ���������� �����
	bool operator<(const Tour& other) const
	{
		return this->m_length < other.m_length;
	}
	friend std::ostream& operator<<(std::ostream& os, const Tour& t);

	// ��������� - ���������� ����������� ���
	Point* Route() const;
};

