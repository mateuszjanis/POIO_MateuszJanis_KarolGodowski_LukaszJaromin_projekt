#pragma once
#include "Map.h"

class WrapperMap
{
	Map* mapa = new Map(20,20);

public:
	~WrapperMap();
	WrapperMap(int x_len, int y_len);
	void show();
private:

};
