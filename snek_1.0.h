#pragma once

typedef enum {LEFT, UP, RIGHT, DOWN, NOWAY } t_direction;
#include <vector>



class Cell
{
public:
	t_direction next_in_cycle;   // ��������� ������ � ������������� �����
	bool is_taken;   // ������ �� ������ ������� ��� ������ ������
	Cell* adjacent[4]; // �������� ������
	Cell();
};

class Snake
{
protected:
	std::vector<Cell*> snake_body;
public:
	// ������� ������ � ����������� dir, ���� ������ ����� ������ - 
	// �������� ���� � ���������� 1, 
	//����� 0
	bool move(t_direction dir); 
};



class Gamefield : public Snake
{
private:
	size_t n; // ���-�� ��������
	size_t m; // ���-�� �����
	size_t field_size; // ������ ���������� ����	
	Cell** field; // ��������� ������ ������, ��� �������� �� ����

	// ���������� ����������� � ��������� � ���. ����� ������ ��� ������ �� � ������� ������� (j) � ������ (i)
	t_direction dir_for_cell(size_t i, size_t j);
	
	void place_snake(); // ����������� ������ �� ������� ����
	void place_apple(); // ����������� ������ � ��������� ����� �� ����


public:

	// ����������� ������ Gamefield. �� ���-�� ����� ���� n_rows � ���-�� �������� ���� n_columns
	// ��������� � ������������ ������ ����, ������ ������ � ����� ������ �������� ������,
	// ������������� ������ ������ ����������� (t_direction) � ��������� � ���. ����� ������;
	// ��������� �� ������� ���� ���� ������ � ������ ������
	Gamefield(size_t n_rows, size_t n_columns);


	~Gamefield(); // ���������� ������ Gamefield. ����������� ������, ���������� ��� ������� ����
	void print_field(); // ������� �� ����� ������� ��������� ����
	void play_the_game(); // ���������� ��� ������ ������������ ������ � ������
};