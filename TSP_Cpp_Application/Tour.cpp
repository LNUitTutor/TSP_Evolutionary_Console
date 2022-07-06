#include "Tour.h"
#include <algorithm>
#include <random>
#include <exception>

Point* Tour::m_towns = nullptr;
int Tour::m_towns_count = 0;

// Довжина маршруту - сума довжин прямолінійних відрізків між сусідніми містами маршруту.
// Довжина відрізку - відстань між точками на координатній площині.
void Tour::CalcLength()
{
	if (m_towns == nullptr || m_towns_count == 0)
	{
		m_length = 0.0;
		throw std::runtime_error(
			"The static members of Tour class are not initialized properly");
	}
	m_length = sqrt(pow(m_towns[m_order[m_towns_count - 1]].x - m_towns[m_order[0]].x, 2)
		+ pow(m_towns[m_order[m_towns_count - 1]].y - m_towns[m_order[0]].y, 2));
	for (int i = 1; i < m_towns_count; ++i)
		m_length += sqrt(pow(m_towns[m_order[i - 1]].x - m_towns[m_order[i]].x, 2)
			+ pow(m_towns[m_order[i - 1]].y - m_towns[m_order[i]].y, 2));
}

// За замовчуванням міста відвідують послідовно від першого до останнього
// або Випадкова перестановка послідовності міст
Tour::Tour(bool permuted)
{
	m_order = new int[m_towns_count];
	for (int i = 0; i < m_towns_count; ++i) m_order[i] = i;
	if (permuted) std::random_shuffle(m_order, m_order + m_towns_count);
	CalcLength();
}

Tour::Tour(const Tour& t) :m_length(t.m_length)
{
	m_order = new int[m_towns_count];
	for (int i = 0; i < m_towns_count; ++i) m_order[i] = t.m_order[i];
}

Tour& Tour::operator=(const Tour& t)
{
	if (this != &t)
	{
		for (int i = 0; i < m_towns_count; ++i) m_order[i] = t.m_order[i];
		m_length = t.m_length;
	}
	return *this;
}

// Проста мутація: обмін місцями двох випадкових міст у послідовності
Tour Tour::Mutate()
{
	int* ord = new int[m_towns_count];
	for (int i = 0; i < m_towns_count; ++i) ord[i] = m_order[i];
	int k = std::rand() % m_towns_count;
	int n = std::rand() % m_towns_count;
	int to_swap = ord[k];
	ord[k] = ord[n];
	ord[n] = to_swap;
	return Tour(ord);
}

// Мутація напрямку: змінює на протилежний напрям руху між двома випадковими містами
Tour Tour::Rotate()
{
	int* ord = new int[m_towns_count];
	for (int i = 0; i < m_towns_count; ++i) ord[i] = m_order[i];
	int k = std::rand() % m_towns_count;
	int n = std::rand() % m_towns_count;
	if (k == n) return Tour(true);
	while (k > n)
	{
		int to_swap = ord[k];
		ord[k] = ord[n];
		ord[n] = to_swap;
		++k; k %= m_towns_count;
		--n; n = (n < 0) ? m_towns_count - 1 : n;
	}
	while (k < n)
	{
		int to_swap = ord[k];
		ord[k] = ord[n];
		ord[n] = to_swap;
		++k; --n;
	}
	return Tour(ord);
}

Point* Tour::Route() const
{
	Point* r = new Point[m_towns_count + 1];
	for (int i = 0; i < m_towns_count; ++i)
		r[i] = m_towns[m_order[i]];
	r[m_towns_count] = r[0];
	return r;
}

std::ostream& operator<<(std::ostream& os, const Tour& t)
{
	os << " Length = " << t.m_length << "\n[";
	for (int i = 0; i < Tour::m_towns_count; ++i) os << ' ' << t.m_order[i];
	os << " ]\n";
	return os;
}
