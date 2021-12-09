#include <iostream>
#include <windows.h>
#include "snek_1.1.h"


Cell::Cell() {
	is_taken = 0;
	next_in_cycle = NOWAY;
	adjacent;
	for (size_t i = 0; i < 4; ++i)
		adjacent[i] = NULL;
}


bool Snake::move(t_direction dir) {
	Cell* t = snake_body[0]->adjacent[dir];
	for (size_t i = 0; i < snake_body.size(); ++i) {
		std::swap(snake_body[i]->is_taken, t->is_taken);
		std::swap(snake_body[i], t);
	}

	if (t->is_taken) {
		snake_body.push_back(t);
		return 1;
	}
	return 0;
}


t_direction Gamefield::dir_for_cell(size_t i, size_t j) {
	size_t vert, horiz;
	bool is_altered = 0;
	vert = m;
	horiz = n;

	//�� ��������� ���-�� ����� - ������; 
	//���� ���-�� ����� - ��������, ��������� ������ �-�� �������� ����������� �����������, � ��������
	if (m % 2) {
		std::swap(vert, horiz);
		std::swap(i, j);
		is_altered = 1;
	}

	if (!(i || j) || (!(i % 2) && j != (horiz - 1) && j != 0))
		return (t_direction)(RIGHT + is_altered);
	if ((i % 2 && j > 1) || (j == 1 && i == vert - 1))
		return (t_direction)(LEFT + is_altered);
	if (j == 0 && i != 0)
		return (t_direction)(UP - is_altered);
	return (t_direction)(DOWN - is_altered);
}


void Gamefield::place_snake() {
	// ������ �� ����������� ������������ ���� ������ ������ ��� ������ ����, � ������� �� �������
	if (n > 2) { // �������� �� ����������� ������������
		snake_body.push_back(field[0] + 2);
	}
	else { // ���� �� ��������, ���������� ������ �� ������ �� ������ ������� ������ ������
		snake_body.push_back(field[1] + 1);
	}
	snake_body.push_back(field[0] + 1);
	snake_body.push_back(field[0]);

	snake_body[0]->is_taken = 1;
	snake_body[1]->is_taken = 1;
	snake_body[2]->is_taken = 1;

	field_size -= 3; // ���� ������ ������ ��� ������
}


int rng(int min_value, int max_value) {
	srand(time(0));
	return(min_value + (rand() % (max_value - min_value + 1)));
}


void Gamefield::place_apple() {
	int pos = rng(0, field_size - 1);
	size_t i, j;
	i = j = 0;
	while (pos) { // ����������� �������� ���-�� ������ ������ �� ������ ����

		j = (j + 1) % n;
		if (j == 0)
			++i;

		while (field[i][j].is_taken) { // ���������� ����������� ������
			j = (j + 1) % n;
			if (j == 0)
				++i;
		}

		--pos;
	}

	// ����� while(pos) i,j ����� ��������� �� ���� ���� (�������� ��� ��������� pos = 0)
	while (field[i][j].is_taken) {
		j = (j + 1) % n;
		if (j == 0)
			++i;
	}

	field[i][j].is_taken = 1;
	--field_size; // ��������� ���� ����������� ����� ������� ������ ������
}


Gamefield::Gamefield(size_t n_rows, size_t n_columns) {
	m = n_rows;
	n = n_columns;
	field_size = n * m;
	field = new Cell * [m];
	for (size_t i = 0; i < m; ++i)
		field[i] = new Cell[n];

	// ����������� ������� ������ �� �������� ������ � ����������� � ��������� � ���. ����� �������
	for (size_t i = 0; i < m; ++i)
		for (size_t j = 0; j < n; ++j) {
			if (i != 0)
				field[i][j].adjacent[UP] = &field[i - 1][j];
			if (i != m)
				field[i][j].adjacent[DOWN] = &field[i + 1][j];
			if (j != 0)
				field[i][j].adjacent[LEFT] = &field[i][j - 1];
			if (j != n)
				field[i][j].adjacent[RIGHT] = &field[i][j + 1];

			field[i][j].next_in_cycle = dir_for_cell(i, j);
		}

	place_snake();
	place_apple();
}


Gamefield::~Gamefield() {
	for (size_t i = 0; i < m; ++i)
		delete[] field[i];
	delete[] field;
}


void Gamefield::print_field() {
	for (size_t i = 0; i < n + 2; ++i)
		std::cout << char(205);
	std::cout << std::endl;
	for (size_t i = 0; i < m; ++i) {
		std::cout << char(186);
		for (size_t j = 0; j < n; ++j)
			if (field[i][j].is_taken)
				std::cout << 'O'; // char(223);
			else
				std::cout << ' ';
		std::cout << char(186) << std::endl;
	}
	for (size_t i = 0; i < n + 2; ++i)
		std::cout << char(205);
}


void Gamefield::play_the_game() {
	if (m % 2)
		if (n == 2 && move(LEFT))
			place_apple();
		else if (n > 2 && move(DOWN))
			place_apple();

	while (field_size) {
		print_field();

		if (move(snake_body[0]->next_in_cycle))// ���� ��� ���� ���� ������� ������
			place_apple(); // ����������� �����

		Sleep(0); // ��������� �������� ����� ������
		system("cls"); // ������� ����������� ����� ������� ����
	}

	print_field();
}