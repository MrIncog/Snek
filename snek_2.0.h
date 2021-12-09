#pragma once

typedef enum { LEFT, UP, RIGHT, DOWN, NOWAY } t_direction;
#include <vector>



class Cell
{
public:
	t_direction next_in_cycle;   // следующа€ клетка в гамильтоновом цикле
	size_t pos_in_cycle; // номер позиции в гамильтоновом цикле
	bool is_taken;   // зан€та ли клетка €блоком или частью змейки
	Cell* adjacent[4]; // соседние клетки
	Cell();
};

class Snake
{
protected:
	std::vector<Cell*> snake_body;
public:
	bool move(t_direction dir); // двигает змейку в направлении dir, если змейка съела €блоко - удлин€ет тело и возвращает 1, иначе 0
};



class Gamefield : public Snake
{
private:
	size_t n; // кол-во столбцов
	size_t m; // кол-во строк
	size_t field_size; // размер пол€
	size_t cur_field_size; // размер незан€того пол€	
	Cell** field; // двумерный массив клеток, где хранитс€ всЄ поле
	size_t apple_pos; // номер позиции €блока в гамильтоновом цикле


	t_direction dir_for_cell(size_t i, size_t j); // определ€ет направление к следующей в гам. цикле клетке дл€ клетки по еЄ номерам столбца (j) и строки (i)
	void set_directions(); // расставл€ет всем клеткам адреса их соседних клеток и направлени€ к следующим в гам. цикле клеткам
	void set_position_inner(Cell& a, size_t i);
	void set_positions(); // расставл€ет номера позиций в гамильтоновом цикле дл€ всех клеток на поле
	void place_snake(); // располагает змейку на игровом поле
	void place_apple(); // располагает €блоко в случайном месте на поле
	bool safe_to_go(Cell* f_cell); // возвращает знач. истина, если идти на клетку f_cell безопасно, иначе ложь
	t_direction get_direction(); // возвращает направление, в котором на данном этапе игры выгоднее всего двигатьс€

public:

	// конструктор класса Gamefield. ѕо кол-ву строк пол€ n_rows и кол-ву столбцов пол€ n_columns
	// размещает в динамической пам€ти поле, каждой клетке в св€зь ставит соседние клетки,
	// устанавливает каждой клетке направление (t_direction) к следующей в гам. цикле клетке;
	// размещает на игровом поле тело змейки и первое €блоко
	Gamefield(size_t n_rows, size_t n_columns);


	~Gamefield(); // деструктор класса Gamefield. ќсвобождает пам€ть, выделенную под игровое поле
	void print_field(); // выводит на экран текущее состо€ние игры

	// отображает всю партию виртуального игрока в змейку
	// delay - задержка между отображением ходов
	void play_the_game(size_t delay=0); 
};