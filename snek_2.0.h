#pragma once

typedef enum { LEFT, UP, RIGHT, DOWN, NOWAY } t_direction;
#include <vector>



class Cell
{
public:
	t_direction next_in_cycle;   // ��������� ������ � ������������� �����
	size_t pos_in_cycle; // ����� ������� � ������������� �����
	bool is_taken;   // ������ �� ������ ������� ��� ������ ������
	Cell* adjacent[4]; // �������� ������
	Cell();
};

class Snake
{
protected:
	std::vector<Cell*> snake_body;
public:
	bool move(t_direction dir); // ������� ������ � ����������� dir, ���� ������ ����� ������ - �������� ���� � ���������� 1, ����� 0
};



class Gamefield : public Snake
{
private:
	size_t n; // ���-�� ��������
	size_t m; // ���-�� �����
	size_t field_size; // ������ ����
	size_t cur_field_size; // ������ ���������� ����	
	Cell** field; // ��������� ������ ������, ��� �������� �� ����
	size_t apple_pos; // ����� ������� ������ � ������������� �����


	t_direction dir_for_cell(size_t i, size_t j); // ���������� ����������� � ��������� � ���. ����� ������ ��� ������ �� � ������� ������� (j) � ������ (i)
	void set_directions(); // ����������� ���� ������� ������ �� �������� ������ � ����������� � ��������� � ���. ����� �������
	void set_position_inner(Cell& a, size_t i);
	void set_positions(); // ����������� ������ ������� � ������������� ����� ��� ���� ������ �� ����
	void place_snake(); // ����������� ������ �� ������� ����
	void place_apple(); // ����������� ������ � ��������� ����� �� ����
	bool safe_to_go(Cell* f_cell); // ���������� ����. ������, ���� ���� �� ������ f_cell ���������, ����� ����
	t_direction get_direction(); // ���������� �����������, � ������� �� ������ ����� ���� �������� ����� ���������

public:

	// ����������� ������ Gamefield. �� ���-�� ����� ���� n_rows � ���-�� �������� ���� n_columns
	// ��������� � ������������ ������ ����, ������ ������ � ����� ������ �������� ������,
	// ������������� ������ ������ ����������� (t_direction) � ��������� � ���. ����� ������;
	// ��������� �� ������� ���� ���� ������ � ������ ������
	Gamefield(size_t n_rows, size_t n_columns);


	~Gamefield(); // ���������� ������ Gamefield. ����������� ������, ���������� ��� ������� ����
	void print_field(); // ������� �� ����� ������� ��������� ����

	// ���������� ��� ������ ������������ ������ � ������
	// delay - �������� ����� ������������ �����
	void play_the_game(size_t delay=0); 
};