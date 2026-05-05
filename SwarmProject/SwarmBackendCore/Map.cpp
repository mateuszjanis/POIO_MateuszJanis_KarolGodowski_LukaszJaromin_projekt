#include "pch.h"
#include "Map.h"
#include <vector>

using namespace std;

Map::Map(int x_len, int y_len)
{
	this -> resize(x_len, y_len);
}

int Map::coord2id(int x, int y)
{
	int vec_id = this->size_y * x + y;

	return vec_id;
}

void Map::resize(int x_len, int y_len) {

	this->size_x = x_len;
	this->size_y = y_len;
	this->obj_map.resize(x_len * y_len);

	for (int i = 0; i < x_len; i++) {
		for (int j = 0; j < x_len; j++) {
			if (i == 0 || i == x_len - 1 || j == 0 || j == y_len - 1)
			{
				this->obj_map[coord2id(i, j)] = 1; // przeszkoda
			}
			else
			{
				this->obj_map[coord2id(i, j)] = 0; // puste pole
			}
		}
	}
}

int Map::get_size_x() {
	
	return this->size_x;

}

int Map::get_size_y() {

	return this->size_y;

}

std::vector<int> Map::get_map() {

	return this->obj_map;

}

void Map::put_on_map(int object, int x_coord, int y_coord)
{

};

