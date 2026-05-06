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

int Map::placeRobot(int x, int y)
{
	int com;

	if (x > 0 && y > 0) {
		if (x < size_x) {
			if (y < size_y) {
				switch (obj_map[coord2id(x, y)])
				{
				case 0:
					obj_map[coord2id(x, y)] = 2;
					com = 0; // jest ok
					break;
				case 1:
					com = -1; // przeszkoda
					break;
				case 2:
					com = -2; // robot
					break;
				}
			}
			else {
				com = 1; // y poza granicą
			}
		}
		else {
			com = 2; // x poza granicą
		}
	}
	else {
		com = 3; // współrzędne ujemne
	}

	return com;
}

int Map::placeObstacle(int x, int y)
{
	int com;

	if (x > 0 && y > 0) {
		if (x < size_x) {
			if (y < size_y) {
				switch (obj_map[coord2id(x, y)])
				{
				case 0:
					obj_map[coord2id(x, y)] = 1;
					com = 0; // jest ok
					break;
				case 1:
					com = -1; // przeszkoda
					break;
				case 2:
					com = -2; // robot
					break;
				}
			}
			else {
				com = 1; // y poza granicą
			}
		}
		else {
			com = 2; // x poza granicą
		}
	}
	else {
		com = 3; // współrzędne ujemne
	}

	return com;
}

