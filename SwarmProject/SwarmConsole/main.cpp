#include "Map.h"
#include "WrapperMap.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

using namespace std;

void prepareNewMap(WrapperMap& mapa)
{
    int x, y, obstacleCount, robotCount;

    mapa.show();
    cout << endl << "Podaj liczbe przeszkod: ";
    cin >> obstacleCount;

    for (int i = 0; i < obstacleCount; i++)
    {
        cout << endl << "Umiesc przeszkode" << endl;
        cout << "x: "; cin >> x;
        cout << "y: "; cin >> y;

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
}

int main() {

// 	int x, y, obstacleCount, robotCount;

// 	WrapperMap mapa(20, 20);
// 	mapa.show();
// 	cout << endl << "Podaj liczbe przeszkod: ";
// 	cin >> obstacleCount;

// 	for (int i = 0; i < obstacleCount; i++)
// 	{
// 		cout << endl << "Umiesc przeszkode" << endl;
// 		cout << "x: "; cin >> x;
// 		cout << "y: "; cin >> y; cout << y;
// 		if (mapa.placeObstacle(x, y))
// 		{
// 			i--;
// 		}
// 	}

// 	cout << endl << "Podaj liczbe robotow: ";
// 	cin >> robotCount;

// 	for (int i = 0; i < robotCount; i++)
// 	{
// 		cout << endl << "Umiesc robota" << endl;
// 		cout << "x: "; cin >> x;
// 		cout << "y: "; cin >> y;
// 		if (mapa.placeRobot(x, y))
// 		{
// 			i--;
// 		}
// 	}
	
// 	bool click = 1;
// 	string command = "";

// 	for (int i = 0; i < 100; i++)
// 	{
// 		system("CLS");
// 		cout << "==============" << " SYMULACJA " << "==============\n";
// 		mapa.show();
// 		mapa.showRobotPos();
// 		mapa.update();
// 		//std::this_thread::sleep_for(std::chrono::seconds(1));
// 		while (click)
// 		{
// 			cin >> command;
// 			if (command != "") { click = 0; }
// 		}
// 		command = "";
// 		click = 1;
		
// 	}

// 	return 0;
  
    WrapperMap mapa(20, 20);
    string fileName = "save.txt";
    int choice;

    cout << "1. Utworz nowa mape" << endl;
    cout << "2. Wczytaj mape z pliku" << endl;
    cout << "Wybor: ";
    cin >> choice;

    if (choice == 2)
    {
        cout << "Podaj nazwe pliku: ";
        cin >> fileName;

        if (mapa.loadFromFile(fileName))
        {
            cout << "Wczytano zapis z pliku: " << fileName << endl;
            mapa.show();
        }
        else
        {
            cout << "Nie udalo sie wczytac pliku. Tworzenie nowej mapy." << endl;
            prepareNewMap(mapa);
        }
    }
    else
    {
        prepareNewMap(mapa);
    }

    bool runProgram = true;

    while (runProgram)
    {
        cout << endl;
        cout << "============ MENU ============" << endl;
        cout << "1. Wykonaj jeden krok symulacji" << endl;
        cout << "2. Wykonaj 100 krokow symulacji" << endl;
        cout << "3. Zapisz mape i roboty" << endl;
        cout << "4. Wczytaj mape i roboty" << endl;
        cout << "5. Pokaz mape" << endl;
        cout << "0. Wyjdz" << endl;
        cout << "Wybor: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("CLS");
            cout << "============= SYMULACJA ==============" << endl;
            mapa.show();
            mapa.showRobotPos();
            mapa.update();
            break;

        case 2:
            for (int i = 0; i < 100; i++)
            {
                system("CLS");
                cout << "============= SYMULACJA ==============" << endl;
                mapa.show();
                mapa.showRobotPos();
                mapa.update();
                this_thread::sleep_for(chrono::seconds(1));
            }
            break;

        case 3:
            cout << "Podaj nazwe pliku: ";
            cin >> fileName;
            if (mapa.saveToFile(fileName))
            {
                cout << "Zapisano mape i roboty do pliku: " << fileName << endl;
            }
            else
            {
                cout << "Blad zapisu do pliku." << endl;
            }
            break;

        case 4:
            cout << "Podaj nazwe pliku: ";
            cin >> fileName;
            if (mapa.loadFromFile(fileName))
            {
                cout << "Wczytano mape i roboty z pliku: " << fileName << endl;
                mapa.show();
            }
            else
            {
                cout << "Blad wczytywania pliku." << endl;
            }
            break;

        case 5:
            mapa.show();
            mapa.showRobotPos();
            break;

        case 0:
            runProgram = false;
            break;

        default:
            cout << "Nieznana opcja." << endl;
            break;
        }
    }

    return 0;
}