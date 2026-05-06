#include "Map.h"
#include "WrapperMap.h"
#include <iostream>

using namespace std;

int main() {

	int x, y, obstacleCount, robotCount;

	WrapperMap mapa(20, 20);
	mapa.show();
	cout << endl << "Podaj liczbe przeszkod: ";
	cin >> obstacleCount;

	for (int i = 0; i < obstacleCount; i++)
	{
		cout << endl << "Umiesc przeszkode" << endl;
		cout << "x: "; cin >> x;
		cout << "y: "; cin >> y; cout << y;
		if (mapa.placeObstacle(x, y))
		{
			i--;
		}
	}

	cout << endl << "Podaj liczbe robotów: ";
	cin >> robotCount;

	for (int i = 0; i < robotCount; i++)
	{
		cout << endl << "Umiesc robota" << endl;
		cout << "x: "; cin >> x;
		cout << "y: "; cin >> y;
		if (mapa.placeRobot(x, y))
		{
			i--;
		}
	}

	return 0;
}