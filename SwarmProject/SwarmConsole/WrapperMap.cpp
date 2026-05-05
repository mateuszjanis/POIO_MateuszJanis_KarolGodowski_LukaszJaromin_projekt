#include "WrapperMap.h"
#include <iostream>
#include <vector>
using namespace std;

WrapperMap::~WrapperMap()
{
	delete mapa;
	mapa = nullptr;
}

WrapperMap::WrapperMap(int x_len, int y_len)
{
	mapa->resize(x_len, y_len);
}

void WrapperMap::show()
{
	std::vector<int> obj_map = mapa->get_map();

	for (int i = 0; i < mapa->get_size_x(); i++) {
		for (int j = 0; j < mapa->get_size_x(); j++) {
			switch (obj_map[mapa->coord2id(i, j)])
			{
			case 0:
				cout << "  ";
				break;
			case 1:
				cout << "x ";
				break;
			case 2:
				cout << "R ";
				break;
			}
		}
		cout << endl;
	}
};