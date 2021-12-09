#include <iostream>
#include "snek_2.0.h"
#include <clocale>

int main() {
	/*
	setlocale(LC_ALL, "Russian");
	std::cout << "Введите количество строк и столбцов поля." << std::endl <<
		"Хотя бы одно измерение должно быть чётным." << std::endl <<
		"Оба измерения должны быть больше 1." << std::endl;
	setlocale(LC_ALL, "C");
	*/
	size_t m, n;
	// std::cin >> m >> n;
	m = 6;
	n = 6;
	Gamefield myfield(m, n);

	myfield.play_the_game(75);
}