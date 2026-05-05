#pragma once
#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "Maze.h"
#include "Robot.h"
#include "Position.h"

class Simulation {
private:
    Maze maze;
    std::vector<Robot> robots;
    int steps;
    int delayMs;

public:
    Simulation(Maze maze, std::vector<Robot> robots, int steps, int delayMs);

    void run();

private:
    void clearConsole() const;
    void draw(int step) const;

    bool isRobotAt(int x, int y, int ignoredRobotId = -1) const;

    double calculatePotential(int x, int y, const Robot& currentRobot) const;
    Position chooseBestMove(const Robot& robot) const;

    void moveRobot(Robot& robot);
};

#endif