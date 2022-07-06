#include "Solver.h"

void Solver::StartPopulation()
{
	for (int i = 0; i < m_population_size; ++i) m_top_tours[i] = Tour(true);
}

void Solver::NextGeneration()
{
    for (int i = 0; i < m_population_size; ++i)
    {
        // Початкові члени популяції мають шанс продовжити існування в наступному поколінні
        m_population.insert(m_top_tours[i]);
        // Кожен член популяції є джерелом для мутованих "нащадків":
        // для нього потрібно виконати задане число простих мутацій ...
        for (int k = 0; k < m_mutation_number; ++k)
        {
            m_population.emplace(m_top_tours[i].Mutate());
        }
        // ... і мутацій напрямку
        for (int k = 0; k < m_rotation_number; ++k)
        {
            m_population.emplace(m_top_tours[i].Rotate());
        }
    }
}

void Solver::Survive()
{
    std::multiset<Tour>::iterator it = m_population.begin();
    for (int i = 0; i < m_population_size && it != m_population.end(); ++i, ++it)
    {
        m_top_tours[i] = *it;
    }
    m_population.clear();
}

Solver::Solver(Point* map, int size) :m_towns(map), m_towns_count(size)
{
    Tour::InitTowns(m_towns, m_towns_count);
	m_population_size = size / 2;
	m_mutation_number = size / 2;
	m_rotation_number = size / 3;
	m_generations_limit = 200;
	m_top_tours = new Tour[m_population_size];
    m_show = nullptr;
}

Solver::Solver(Point* map, int size, int population_size, int mutations, int turns, int max_generation)
	:m_towns(map), m_towns_count(size), m_population_size(population_size),
	m_mutation_number(mutations), m_rotation_number(turns), m_generations_limit(max_generation)
{
    Tour::InitTowns(m_towns, m_towns_count);
	m_top_tours = new Tour[m_population_size];
    m_show = nullptr;
}

int Solver::Solve(const bool& stop_required)
{
    StartPopulation();
    int generation_number = 0;
    while (!stop_required && generation_number < m_generations_limit)
    {
        NextGeneration();
        Survive();
        ++generation_number;
        if (generation_number % 50 == 0)
        {
            if (m_show != nullptr) m_show(generation_number, Best().Length());
        }
    }
    return generation_number;
}
