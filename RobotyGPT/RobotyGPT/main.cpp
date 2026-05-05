#include <iostream>
#include <vector>

#include "Maze.h"
#include "Robot.h"
#include "Simulation.h"

int main() {
    int width;
    int height;

    std::cout << "SYMULACJA ROJU ROBOTOW W LABIRYNCIE" << std::endl;
    std::cout << "==================================" << std::endl;

    std::cout << "Podaj szerokosc labiryntu: ";
    std::cin >> width;

    std::cout << "Podaj wysokosc labiryntu: ";
    std::cin >> height;

    Maze maze(width, height);
    maze.readFromConsole();

    int robotCount;

    std::cout << std::endl;
    std::cout << "Podaj liczbe robotow: ";
    std::cin >> robotCount;

    std::vector<Robot> robots;

    for (int i = 0; i < robotCount; i++) {
        Position position;
        int speed;

        std::cout << std::endl;
        std::cout << "Robot " << i << std::endl;

        while (true) {
            std::cout << "Podaj pozycje startowa x: ";
            std::cin >> position.x;

            std::cout << "Podaj pozycje startowa y: ";
            std::cin >> position.y;

            if (!maze.isInside(position.x, position.y)) {
                std::cout << "Blad: pozycja poza labiryntem." << std::endl;
                continue;
            }

            if (maze.isWall(position.x, position.y)) {
                std::cout << "Blad: robot nie moze startowac na scianie." << std::endl;
                continue;
            }

            bool occupied = false;

            for (const Robot& robot : robots) {
                Position robotPos = robot.getPosition();

                if (robotPos.x == position.x && robotPos.y == position.y) {
                    occupied = true;
                    break;
                }
            }

            if (occupied) {
                std::cout << "Blad: na tym polu stoi juz inny robot." << std::endl;
                continue;
            }

            break;
        }

        std::cout << "Podaj predkosc robota, czyli liczbe ruchow na krok symulacji: ";
        std::cin >> speed;

        if (speed < 1) {
            speed = 1;
        }

        robots.emplace_back(i, position, speed);
    }

    int steps;
    int delayMs;

    std::cout << std::endl;
    std::cout << "Podaj liczbe krokow symulacji: ";
    std::cin >> steps;

    std::cout << "Podaj opoznienie miedzy krokami w ms, np. 300: ";
    std::cin >> delayMs;

    Simulation simulation(maze, robots, steps, delayMs);
    simulation.run();

    return 0;
}





/*
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

// ===============================
// Struktura przechowująca pozycję
// ===============================
struct Position {
    int x;
    int y;
};

// ===============================
// Struktura robota
// ===============================
struct Robot {
    int id;
    Position position;
    int speed;
};

// ===============================
// Czyszczenie konsoli
// ===============================
void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ===============================
// Sprawdzenie, czy pole jest w labiryncie
// ===============================
bool isInside(int x, int y, int width, int height) {
    return x >= 0 && x < width && y >= 0 && y < height;
}

// ===============================
// Sprawdzenie, czy pole jest ścianą
// ===============================
bool isWall(const vector<string>& maze, int x, int y) {
    return maze[y][x] == '#';
}

// ===============================
// Sprawdzenie, czy na danym polu stoi robot
// ===============================
bool isRobotAt(const vector<Robot>& robots, int x, int y, int ignoredRobotId = -1) {
    for (const Robot& robot : robots) {
        if (robot.id == ignoredRobotId) {
            continue;
        }

        if (robot.position.x == x && robot.position.y == y) {
            return true;
        }
    }

    return false;
}

// ===============================
// Obliczanie liczby pól możliwych do odwiedzenia
// ===============================
int countFreeFields(const vector<string>& maze) {
    int counter = 0;

    for (int y = 0; y < maze.size(); y++) {
        for (int x = 0; x < maze[y].size(); x++) {
            if (maze[y][x] != '#') {
                counter++;
            }
        }
    }

    return counter;
}

// ===============================
// Obliczanie liczby odwiedzonych pól
// ===============================
int countVisitedFields(const vector<vector<int>>& visits, const vector<string>& maze) {
    int counter = 0;

    for (int y = 0; y < visits.size(); y++) {
        for (int x = 0; x < visits[y].size(); x++) {
            if (maze[y][x] != '#' && visits[y][x] > 0) {
                counter++;
            }
        }
    }

    return counter;
}

// ===============================
// Obliczanie procentowego pokrycia labiryntu
// ===============================
double calculateCoverage(const vector<vector<int>>& visits, const vector<string>& maze) {
    int freeFields = countFreeFields(maze);
    int visitedFields = countVisitedFields(visits, maze);

    if (freeFields == 0) {
        return 0.0;
    }

    return 100.0 * visitedFields / freeFields;
}

// ===============================
// Obliczanie potencjału danego pola
// Im mniejszy potencjał, tym lepsze pole
// ===============================
double calculatePotential(
    int x,
    int y,
    const Robot& currentRobot,
    const vector<Robot>& robots,
    const vector<string>& maze,
    const vector<vector<int>>& visits
) {
    int height = maze.size();
    int width = maze[0].size();

    // Pole poza labiryntem jest niedozwolone
    if (!isInside(x, y, width, height)) {
        return numeric_limits<double>::max();
    }

    // Ściana jest niedozwolona
    if (isWall(maze, x, y)) {
        return numeric_limits<double>::max();
    }

    double potential = 0.0;

    // Kara za często odwiedzane pole
    // Roboty będą chętniej wybierać pola rzadziej odwiedzone
    potential += visits[y][x] * 10.0;

    // Odpychanie od innych robotów
    for (const Robot& otherRobot : robots) {
        if (otherRobot.id == currentRobot.id) {
            continue;
        }

        int dx = x - otherRobot.position.x;
        int dy = y - otherRobot.position.y;

        double distanceSquared = dx * dx + dy * dy;

        if (distanceSquared == 0) {
            // Bardzo duża kara za wejście na pole zajęte przez innego robota
            potential += 10000.0;
        }
        else {
            // Im bliżej innego robota, tym większa kara
            potential += 20.0 / distanceSquared;
        }
    }

    return potential;
}

// ===============================
// Wybór najlepszego ruchu robota
// ===============================
Position chooseBestMove(
    const Robot& robot,
    const vector<Robot>& robots,
    const vector<string>& maze,
    const vector<vector<int>>& visits
) {
    Position current = robot.position;

    vector<Position> possibleMoves = {
        {current.x, current.y},       // pozostanie w miejscu
        {current.x + 1, current.y},   // prawo
        {current.x - 1, current.y},   // lewo
        {current.x, current.y + 1},   // dół
        {current.x, current.y - 1}    // góra
    };

    Position bestMove = current;
    double bestPotential = numeric_limits<double>::max();

    for (const Position& move : possibleMoves) {
        double potential = calculatePotential(
            move.x,
            move.y,
            robot,
            robots,
            maze,
            visits
        );

        if (potential < bestPotential) {
            bestPotential = potential;
            bestMove = move;
        }
    }

    return bestMove;
}

// ===============================
// Rysowanie labiryntu w konsoli
// ===============================
void drawMaze(
    const vector<string>& maze,
    const vector<vector<int>>& visits,
    const vector<Robot>& robots,
    int step
) {
    vector<string> display = maze;

    for (int y = 0; y < display.size(); y++) {
        for (int x = 0; x < display[y].size(); x++) {
            if (display[y][x] != '#') {
                if (visits[y][x] > 0) {
                    display[y][x] = '+';
                }
                else {
                    display[y][x] = '.';
                }
            }
        }
    }

    for (const Robot& robot : robots) {
        int x = robot.position.x;
        int y = robot.position.y;

        if (isInside(x, y, display[0].size(), display.size())) {
            if (robot.id < 10) {
                display[y][x] = char('0' + robot.id);
            }
            else {
                display[y][x] = 'R';
            }
        }
    }

    cout << "Krok symulacji: " << step << endl;
    cout << "Pokrycie labiryntu: " << calculateCoverage(visits, maze) << " %" << endl;
    cout << endl;

    for (const string& row : display) {
        cout << row << endl;
    }

    cout << endl;
    cout << "Legenda:" << endl;
    cout << "# - sciana" << endl;
    cout << ". - pole nieodwiedzone" << endl;
    cout << "+ - pole odwiedzone" << endl;
    cout << "0-9 / R - robot" << endl;
}

// ===============================
// Program główny
// ===============================
int main() {
    int width, height;

    cout << "SYMULACJA ROJU ROBOTOW W LABIRYNCIE" << endl;
    cout << "==================================" << endl;

    cout << "Podaj szerokosc labiryntu: ";
    cin >> width;

    cout << "Podaj wysokosc labiryntu: ";
    cin >> height;

    vector<string> maze(height);

    cout << endl;
    cout << "Wprowadz labirynt." << endl;
    cout << "Uzyj znaku # jako sciany oraz . jako wolnego pola." << endl;
    cout << "Kazdy wiersz musi miec dokladnie " << width << " znakow." << endl;
    cout << endl;

    for (int y = 0; y < height; y++) {
        while (true) {
            cout << "Wiersz " << y << ": ";
            cin >> maze[y];

            if (maze[y].size() == width) {
                break;
            }

            cout << "Blad: wiersz musi miec dokladnie " << width << " znakow." << endl;
        }
    }

    vector<vector<int>> visits(height, vector<int>(width, 0));

    int robotCount;

    cout << endl;
    cout << "Podaj liczbe robotow: ";
    cin >> robotCount;

    vector<Robot> robots;

    for (int i = 0; i < robotCount; i++) {
        Robot robot;
        robot.id = i;

        cout << endl;
        cout << "Robot " << i << endl;

        while (true) {
            cout << "Podaj pozycje startowa x: ";
            cin >> robot.position.x;

            cout << "Podaj pozycje startowa y: ";
            cin >> robot.position.y;

            if (!isInside(robot.position.x, robot.position.y, width, height)) {
                cout << "Blad: pozycja poza labiryntem." << endl;
                continue;
            }

            if (isWall(maze, robot.position.x, robot.position.y)) {
                cout << "Blad: robot nie moze startowac na scianie." << endl;
                continue;
            }

            if (isRobotAt(robots, robot.position.x, robot.position.y)) {
                cout << "Blad: na tym polu stoi juz inny robot." << endl;
                continue;
            }

            break;
        }

        cout << "Podaj predkosc robota, czyli liczbe ruchow na krok symulacji: ";
        cin >> robot.speed;

        if (robot.speed < 1) {
            robot.speed = 1;
        }

        robots.push_back(robot);

        visits[robot.position.y][robot.position.x]++;
    }

    int simulationSteps;

    cout << endl;
    cout << "Podaj liczbe krokow symulacji: ";
    cin >> simulationSteps;

    int delayMs;

    cout << "Podaj opoznienie miedzy krokami w ms, np. 300: ";
    cin >> delayMs;

    // ===============================
    // Główna pętla symulacji
    // ===============================
    for (int step = 0; step <= simulationSteps; step++) {
        clearConsole();

        drawMaze(maze, visits, robots, step);

        this_thread::sleep_for(chrono::milliseconds(delayMs));

        for (Robot& robot : robots) {
            for (int move = 0; move < robot.speed; move++) {
                Position newPosition = chooseBestMove(
                    robot,
                    robots,
                    maze,
                    visits
                );

                robot.position = newPosition;
                visits[robot.position.y][robot.position.x]++;
            }
        }
    }

    cout << endl;
    cout << "Symulacja zakonczona." << endl;
    cout << "Koncowe pokrycie labiryntu: "
        << calculateCoverage(visits, maze)
        << " %" << endl;

    return 0;
}
*/