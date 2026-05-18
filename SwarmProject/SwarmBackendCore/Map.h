#pragma once
#include "pch.h"
#include <vector>
#include "Robot.h"

class Map
{

	int size_x, size_y;
	std::vector<Robot> robot_list;
	std::vector<std::vector<int>> obj_map; 

public:
	Map();
	Map(int x_len, int y_len);

	int get_size_x();
	int get_size_y();
	int get_robot_num();
	std::vector<int> get_robot_pos(int id);
	std::vector<std::vector<int>> get_map();

	void resize(int x_len, int y_len);
	void update();
	int placeRobot(int x, int y);
	int placeObstacle(int x, int y);
	void moveRobot(int id, std::vector<int> move);
	void clearRobot(int id);

	int get_obstacle_num();

private:

};

