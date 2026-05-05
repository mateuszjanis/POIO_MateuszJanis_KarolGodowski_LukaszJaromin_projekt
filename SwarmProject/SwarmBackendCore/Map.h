#pragma once
#include "pch.h"
#include <vector>

class Map
{

	int size_x, size_y;
	std::vector<int> obj_map; // mapa przechowywana w wektorze 
							  // (dodatkowa metoda ... przeliczająca x,y na miejsce w wektorze)
							  // {x0y0, x0y1, x0y2, x1y0, x1y1, x1y2, x2y0,...}
							  // |________________|
							  //    jeden wiersz
public:
	Map();
	Map(int x_len, int y_len);
	//void show();
	void resize(int x_len, int y_len);
	int get_size_x();
	int get_size_y();
	std::vector<int> get_map();
	int coord2id(int x, int y);

private:
	void put_on_map(int object, int x_coord, int y_coord);

};

