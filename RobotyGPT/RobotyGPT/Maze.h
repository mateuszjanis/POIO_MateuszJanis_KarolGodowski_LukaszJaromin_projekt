#pragma once
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>

class Maze {
private:
    int width;
    int height;
    std::vector<std::string> grid;
    std::vector<std::vector<int>> visits;

public:
    Maze(int width, int height);

    void readFromConsole();

    bool isInside(int x, int y) const;
    bool isWall(int x, int y) const;

    int getWidth() const;
    int getHeight() const;

    char getCell(int x, int y) const;

    int getVisits(int x, int y) const;
    void incrementVisits(int x, int y);

    int countFreeFields() const;
    int countVisitedFields() const;
    double calculateCoverage() const;
};

#endif