#include <iostream>
#include "snek_2.0.h"
#include <clocale>

int main() {
	/*
	setlocale(LC_ALL, "Russian");
	std::cout << "������� ���������� ����� � �������� ����." << std::endl <<
		"���� �� ���� ��������� ������ ���� ������." << std::endl <<
		"��� ��������� ������ ���� ������ 1." << std::endl;
	setlocale(LC_ALL, "C");
	*/
	size_t m, n;
	// std::cin >> m >> n;
	m = 6;
	n = 6;
	Gamefield myfield(m, n);

	myfield.play_the_game(75);
}