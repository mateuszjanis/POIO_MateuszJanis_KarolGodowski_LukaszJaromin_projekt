#include "Maze.h"
#include <iostream>

Maze::Maze(int width, int height)
    : width(width), height(height) {
    grid.resize(height);
    visits.resize(height, std::vector<int>(width, 0));
}

void Maze::readFromConsole() {
    std::cout << std::endl;
    std::cout << "Wprowadz labirynt." << std::endl;
    std::cout << "Uzyj znaku # jako sciany oraz . jako wolnego pola." << std::endl;
    std::cout << "Kazdy wiersz musi miec dokladnie " << width << " znakow." << std::endl;
    std::cout << std::endl;

    for (int y = 0; y < height; y++) {
        while (true) {
            std::cout << "Wiersz " << y << ": ";
            std::cin >> grid[y];

            if (grid[y].size() == static_cast<size_t>(width)) {
                break;
            }

            std::cout << "Blad: wiersz musi miec dokladnie "
                << width << " znakow." << std::endl;
        }
    }
}

bool Maze::isInside(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

bool Maze::isWall(int x, int y) const {
    return grid[y][x] == '#';
}

int Maze::getWidth() const {
    return width;
}

int Maze::getHeight() const {
    return height;
}

char Maze::getCell(int x, int y) const {
    return grid[y][x];
}

int Maze::getVisits(int x, int y) const {
    return visits[y][x];
}

void Maze::incrementVisits(int x, int y) {
    visits[y][x]++;
}

int Maze::countFreeFields() const {
    int counter = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x] != '#') {
                counter++;
            }
        }
    }

    return counter;
}

int Maze::countVisitedFields() const {
    int counter = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x] != '#' && visits[y][x] > 0) {
                counter++;
            }
        }
    }

    return counter;
}

double Maze::calculateCoverage() const {
    int freeFields = countFreeFields();
    int visitedFields = countVisitedFields();

    if (freeFields == 0) {
        return 0.0;
    }

    return 100.0 * visitedFields / freeFields;
}