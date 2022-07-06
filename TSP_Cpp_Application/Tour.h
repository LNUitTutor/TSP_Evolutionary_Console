#pragma once
#include "Point.h"

// Клас інкапсулює послідовність m_order відвідання міст, координати m_towns яких задано зовні.
// Має методи "мутування" для створення нових турів, вміє обчислити і зберігає довжину маршруту.
// Тури порівнюють за довжиною.

class Tour
{
private:
	static Point* m_towns;   // координати міст
	static int m_towns_count;

	int* m_order;            // перестановка номерів
	double m_length;         // відповідна довжина
	void CalcLength();      // метод обчислення довжини
	// новий тур містить перестановку, обчислену зовні
	Tour(int* permutation) :m_order(permutation)
	{
		CalcLength();
	}
public:
	// метод викликають перед початком використання класу
	static void InitTowns(Point* t, int n)
	{
		m_towns = t; m_towns_count = n;
	}
	~Tour() { delete[] m_order; }
	// за замовчуванням порядок відвідання - послідовний: m_order[i] = i
	// за бажання можна перемішати порядок відвідання випадковим чином
	Tour(bool permuted = false);
	// копіювання та присвоєння потрібні для роботи з контейнерами
	Tour(const Tour& t);
	Tour& operator=(const Tour& t);
	// метод отримання довжини повідомляє вже обчислене значення
	double Length() const { return m_length; }
	// методи мутації турів: обмін і поворот
	Tour Mutate();
	Tour Rotate();
	// оператори полегшують використання екземплярів класу
	bool operator<(const Tour& other) const
	{
		return this->m_length < other.m_length;
	}
	friend std::ostream& operator<<(std::ostream& os, const Tour& t);

	// Результат - побудована послідовність міст
	Point* Route() const;
};

