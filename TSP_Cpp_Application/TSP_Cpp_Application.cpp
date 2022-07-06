#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include "Point.h"
#include "Tour.h"
#include "Solver.h"

int main()
{
    SetConsoleOutputCP(1251);
    std::ifstream fin("input_data.txt");
    std::string comment;
    std::cout << " *** Еволюційне числення в задачі комівояжера\n\n";
    // завантаження вхідних даних
    int map_width, map_height, towns_number, population_size, mutations, turns, max_gen;
    fin >> map_width; std::getline(fin, comment);
    std::cout << map_width << '\t' << comment << '\n';
    fin >> map_height; std::getline(fin, comment);
    std::cout << map_height << '\t' << comment << '\n';
    fin >> towns_number; std::getline(fin, comment);
    std::cout << towns_number << '\t' << comment << '\n';
    fin >> population_size; std::getline(fin, comment);
    fin >> mutations; std::getline(fin, comment);
    fin >> turns; std::getline(fin, comment);
    fin >> max_gen; std::getline(fin, comment);
    std::cout << max_gen << '\t' << comment << '\n';
    // генерування координат міст на карті
    srand(time(0));
    Point* map = new Point[towns_number];
    std::cout << "Міста:\n";
    for (int i = 0; i < towns_number; ++i)
    {
        map[i] = Point(rand() % map_width + 1., rand() % map_height + 1.);
        std::cout << map[i];
    }
    std::cout << "\n\n";
    // розв'язування
    Solver* solver = new Solver(map, towns_number, population_size, mutations, turns, max_gen);
    bool need_stop = false;     // прапорець вимоги про зупинку обчислень
    solver->m_show = [&need_stop](int gen, double len)
    { 
        std::cout << " * покоління: " << gen << " довжина: " << len << '\n';
        need_stop = _kbhit();
    };
    std::cout << "Щоб зупинити обчислення, натисніть довільну клавішу...\n";
    max_gen = solver->Solve(need_stop);
    std::cout << "Досліджено " << max_gen << " поколінь. Знайдено розв'язок:\n" << solver->Best() << '\n';
    delete solver;
    delete[] map;
}
