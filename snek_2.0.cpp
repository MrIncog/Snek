#include <iostream>
#include <windows.h>
#include "snek_2.0.h"


Cell::Cell() {
	is_taken = 0;
	next_in_cycle = NOWAY;
	for (t_direction i_dir = (t_direction)0; i_dir < NOWAY; i_dir = t_direction(i_dir + 1))
		adjacent[i_dir] = NULL;
	pos_in_cycle = 0;
}


bool Snake::move(t_direction dir) {
	Cell* t = snake_body[0]->adjacent[dir];
	for (size_t i = 0; i < snake_body.size(); ++i) {
		std::swap(snake_body[i]->is_taken, t->is_taken);
		std::swap(snake_body[i], t);
	}

	if (t->is_taken && t != snake_body[0]) {
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

void Gamefield::set_directions() {
	for (size_t i = 0; i < m; ++i)
		for (size_t j = 0; j < n; ++j) {
			if (i != 0)
				field[i][j].adjacent[UP] = &field[i - 1][j];
			if (i != m - 1)
				field[i][j].adjacent[DOWN] = &field[i + 1][j];
			if (j != 0)
				field[i][j].adjacent[LEFT] = &field[i][j - 1];
			if (j != n - 1)
				field[i][j].adjacent[RIGHT] = &field[i][j + 1];

			field[i][j].next_in_cycle = dir_for_cell(i, j);
		}
}

void Gamefield::set_position_inner(Cell &a, size_t i) {
	if (i == field_size)
		return;
	a.pos_in_cycle = i;
	set_position_inner(*a.adjacent[a.next_in_cycle], i + 1);
}

void Gamefield::set_positions() {
	set_position_inner(field[0][0], 0);
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

	cur_field_size -= 3; // ���� ������ ������ ��� ������
}


int rng(int min_value, int max_value) {
	srand(time(0));
	return(min_value + (rand() % (max_value - min_value + 1)));
}


void Gamefield::place_apple() {
	int pos = rng(0, cur_field_size - 1);
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
	apple_pos = field[i][j].pos_in_cycle;
	--cur_field_size; // ��������� ���� ����������� ����� ������� ������ ������
}


bool Gamefield::safe_to_go(Cell* f_cell)
{
	//f_cell ��������� �� ������
	if (f_cell == NULL)
		return false;

	//���� �� ���. ����� ������ ���������
	if (snake_body[0]->adjacent[snake_body[0]->next_in_cycle] == f_cell)
		return true;

	size_t c_turns = 0; // ������� ����� �� ������
	while (!f_cell->is_taken) {
		f_cell = f_cell->adjacent[f_cell->next_in_cycle];
		++c_turns;
	}

	// ���� �� ��������� ������, ������� �������, � �� �������,
	// �� ����������� ����� �����, �.�. ���� ������ ����� ���������� �� 1
	if (f_cell->pos_in_cycle == apple_pos) {
		f_cell = f_cell->adjacent[f_cell->next_in_cycle];
		// ���������� ������ �����, ���� ��������� ������
		while (!f_cell->is_taken) {
			f_cell = f_cell->adjacent[f_cell->next_in_cycle];
			//++c_turns;
		}
	}

	// ����� ������ ������ f_cell ����� ������� ������ � ������� snake_body
	// i_tailcell = ������ f_cell � snake_body
	size_t i_tailcell = 0; 
	while (snake_body[i_tailcell] != f_cell)
		++i_tailcell;

	// �� ���� ���� ���������, ���� �� c_turns ����� 
	// ����� ���� ��������� ������, ��� ����� �� f_cell �� ��������� ������ ������
	return c_turns >= snake_body.size() - 1 - i_tailcell;
}

t_direction Gamefield::get_direction()
{
	// ����������� ����� ������ ���� �� ������, ������� � ����� �� ����� ������
	// ���������������� �������� ����, �.�. ����� ����� ����� ������ �����
	size_t min_waylen = field_size; 
	// �����������, ������ ���������� ����
	t_direction min_waydir = NOWAY;

	
	for (t_direction i_dir = (t_direction)0; i_dir < NOWAY; i_dir = t_direction(i_dir + 1)) {
		size_t dir_waylen; // ����� ���� � ����������� i_dir
		Cell* cell_in_dir = snake_body[0]->adjacent[i_dir]; // ������ � ����������� i_dir

		
		// ���� ������ ����. i_dir ���������
		if (safe_to_go(cell_in_dir)){
			if (cell_in_dir->pos_in_cycle > apple_pos) // ������� ������ ������ ������ � ���. �����
				dir_waylen = field_size - cell_in_dir->pos_in_cycle + apple_pos;
			else // ������� ������ �� ������ � ���.�����
				dir_waylen = apple_pos - cell_in_dir->pos_in_cycle;

			if (dir_waylen < min_waylen) {
				min_waylen = dir_waylen;
				min_waydir = i_dir;
			}
		}
		
	}


	return min_waydir;
} 


Gamefield::Gamefield(size_t n_rows, size_t n_columns) {
	m = n_rows;
	n = n_columns;
	apple_pos = 0;
	cur_field_size = field_size= n * m;
	field = new Cell*[m];
	for (size_t i = 0; i < m; ++i)
		field[i] = new Cell[n];


	set_directions();
	set_positions();
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
				if (&(field[i][j]) == snake_body[0])
					std::cout << 'H';
				else if (field[i][j].pos_in_cycle == apple_pos)
					std::cout << 'A';
				else 
					std::cout << 'B'; // char(223);

			else
				std::cout << ' ';
		std::cout << char(186) << std::endl;
	}

	for (size_t i = 0; i < n + 2; ++i)
		std::cout << char(205);
}


void Gamefield::play_the_game(size_t delay) {
	if (m % 2)
		if (n == 2 && move(LEFT))
			place_apple();
		else if (n > 2 && move(DOWN))
			place_apple();

	while (cur_field_size) {
		print_field();

		if (move(get_direction()))// ���� ��� ���� ���� ������� ������
			place_apple(); // ����������� �����

		Sleep(delay); // ��������� �������� ����� ������
		system("cls"); // ������� ����������� ����� ������� ����
	}

	print_field();
}