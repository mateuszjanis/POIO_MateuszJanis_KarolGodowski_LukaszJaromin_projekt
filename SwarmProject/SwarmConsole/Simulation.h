#pragma once

#include "WrapperMap.h"

struct SimulationSettings
{
    int stepCount = 100;
    int delayMs = 1000;
    bool showRobotPositions = true;
};

class Simulation
{
private:
    WrapperMap& mapa;
    SimulationSettings settings;
    int currentStep = 0;

public:
    Simulation(WrapperMap& mapa, SimulationSettings settings);

    void run();

private:
    void clearConsole();
    void drawHeader();
    void drawFrame();
    void wait();
};
