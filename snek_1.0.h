#pragma once

typedef enum {LEFT, UP, RIGHT, DOWN, NOWAY } t_direction;
#include <vector>



class Cell
{
public:
	t_direction next_in_cycle;   // следующа€ клетка в гамильтоновом цикле
	bool is_taken;   // зан€та ли клетка €блоком или частью змейки
	Cell* adjacent[4]; // соседние клетки
	Cell();
};

class Snake
{
protected:
	std::vector<Cell*> snake_body;
public:
	// двигает змейку в направлении dir, если змейка съела €блоко - 
	// удлин€ет тело и возвращает 1, 
	//иначе 0
	bool move(t_direction dir); 
};



class Gamefield : public Snake
{
private:
	size_t n; // кол-во столбцов
	size_t m; // кол-во строк
	size_t field_size; // размер незан€того пол€	
	Cell** field; // двумерный массив клеток, где хранитс€ всЄ поле

	// определ€ет направление к следующей в гам. цикле клетке дл€ клетки по еЄ номерам столбца (j) и строки (i)
	t_direction dir_for_cell(size_t i, size_t j);
	
	void place_snake(); // располагает змейку на игровом поле
	void place_apple(); // располагает €блоко в случайном месте на поле


public:

	// конструктор класса Gamefield. ѕо кол-ву строк пол€ n_rows и кол-ву столбцов пол€ n_columns
	// размещает в динамической пам€ти поле, каждой клетке в св€зь ставит соседние клетки,
	// устанавливает каждой клетке направление (t_direction) к следующей в гам. цикле клетке;
	// размещает на игровом поле тело змейки и первое €блоко
	Gamefield(size_t n_rows, size_t n_columns);


	~Gamefield(); // деструктор класса Gamefield. ќсвобождает пам€ть, выделенную под игровое поле
	void print_field(); // выводит на экран текущее состо€ние игры
	void play_the_game(); // отображает всю партию виртуального игрока в змейку
};