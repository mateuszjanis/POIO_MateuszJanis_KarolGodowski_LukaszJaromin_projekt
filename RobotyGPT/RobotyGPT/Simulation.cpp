#include "Simulation.h"
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>
#include <cstdlib>

Simulation::Simulation(Maze maze, std::vector<Robot> robots, int steps, int delayMs)
    : maze(maze), robots(robots), steps(steps), delayMs(delayMs) {

    for (const Robot& robot : this->robots) {
        Position pos = robot.getPosition();
        this->maze.incrementVisits(pos.x, pos.y);
    }
}

void Simulation::run() {
    for (int step = 0; step <= steps; step++) {
        clearConsole();
        draw(step);

        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));

        for (Robot& robot : robots) {
            moveRobot(robot);
        }
    }

    std::cout << std::endl;
    std::cout << "Symulacja zakonczona." << std::endl;
    std::cout << "Koncowe pokrycie labiryntu: "
        << maze.calculateCoverage()
        << " %" << std::endl;
}

void Simulation::clearConsole() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Simulation::draw(int step) const {
    std::vector<std::string> display;

    for (int y = 0; y < maze.getHeight(); y++) {
        std::string row;

        for (int x = 0; x < maze.getWidth(); x++) {
            if (maze.isWall(x, y)) {
                row += '#';
            }
            else if (maze.getVisits(x, y) > 0) {
                row += '+';
            }
            else {
                row += '.';
            }
        }

        display.push_back(row);
    }

    for (const Robot& robot : robots) {
        Position pos = robot.getPosition();

        if (maze.isInside(pos.x, pos.y)) {
            if (robot.getId() < 10) {
                display[pos.y][pos.x] = char('0' + robot.getId());
            }
            else {
                display[pos.y][pos.x] = 'R';
            }
        }
    }

    std::cout << "Krok symulacji: " << step << std::endl;
    std::cout << "Pokrycie labiryntu: "
        << maze.calculateCoverage()
        << " %" << std::endl;
    std::cout << std::endl;

    for (const std::string& row : display) {
        std::cout << row << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Legenda:" << std::endl;
    std::cout << "# - sciana" << std::endl;
    std::cout << ". - pole nieodwiedzone" << std::endl;
    std::cout << "+ - pole odwiedzone" << std::endl;
    std::cout << "0-9 / R - robot" << std::endl;
}

bool Simulation::isRobotAt(int x, int y, int ignoredRobotId) const {
    for (const Robot& robot : robots) {
        if (robot.getId() == ignoredRobotId) {
            continue;
        }

        Position pos = robot.getPosition();

        if (pos.x == x && pos.y == y) {
            return true;
        }
    }

    return false;
}

double Simulation::calculatePotential(int x, int y, const Robot& currentRobot) const {
    if (!maze.isInside(x, y)) {
        return std::numeric_limits<double>::max();
    }

    if (maze.isWall(x, y)) {
        return std::numeric_limits<double>::max();
    }

    double potential = 0.0;

    // Kara za często odwiedzane pole
    potential += maze.getVisits(x, y) * 10.0;

    // Odpychanie od innych robotów
    for (const Robot& otherRobot : robots) {
        if (otherRobot.getId() == currentRobot.getId()) {
            continue;
        }

        Position otherPos = otherRobot.getPosition();

        int dx = x - otherPos.x;
        int dy = y - otherPos.y;

        double distanceSquared = dx * dx + dy * dy;

        if (distanceSquared == 0) {
            potential += 10000.0;
        }
        else {
            potential += 20.0 / distanceSquared;
        }
    }

    return potential;
}

Position Simulation::chooseBestMove(const Robot& robot) const {
    Position current = robot.getPosition();

    std::vector<Position> possibleMoves = {
        {current.x, current.y},
        {current.x + 1, current.y},
        {current.x - 1, current.y},
        {current.x, current.y + 1},
        {current.x, current.y - 1}
    };

    Position bestMove = current;
    double bestPotential = std::numeric_limits<double>::max();

    for (const Position& move : possibleMoves) {
        double potential = calculatePotential(move.x, move.y, robot);

        if (potential < bestPotential) {
            bestPotential = potential;
            bestMove = move;
        }
    }

    return bestMove;
}

void Simulation::moveRobot(Robot& robot) {
    for (int i = 0; i < robot.getSpeed(); i++) {
        Position newPosition = chooseBestMove(robot);

        robot.setPosition(newPosition);
        maze.incrementVisits(newPosition.x, newPosition.y);
    }
}