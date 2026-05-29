#include "Map.h"
#include "WrapperMap.h"
#include <iostream>
#include <thread>
#include <chrono>

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

	cout << endl << "Podaj liczbe robotow: ";
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
	
	bool click = 1;
	string command = "";

	for (int i = 0; i < 100; i++)
	{
		system("CLS");
		cout << "==============" << " SYMULACJA " << "==============\n";
		mapa.show();
		mapa.showRobotPos();
		mapa.update();
		//std::this_thread::sleep_for(std::chrono::seconds(1));
		while (click)
		{
			cin >> command;
			if (command != "") { click = 0; }
		}
		command = "";
		click = 1;
		
	}

	return 0;
}