#include "Map.h"
#include "WrapperMap.h"
#include <iostream>
#include <thread>
#include <chrono>

#include "Simulation.h"
#include <ctime>




using namespace std;

int main() {

	srand(static_cast<unsigned int>(time(nullptr)));

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
	
	SimulationSettings settings;

	cout << endl << "Podaj liczbe krokow symulacji: ";
	cin >> settings.stepCount;

	cout << "Podaj opoznienie miedzy krokami [ms]: ";
	cin >> settings.delayMs;

	settings.showRobotPositions = true;

	Simulation simulation(mapa, settings);
	simulation.run();

	return 0;
}