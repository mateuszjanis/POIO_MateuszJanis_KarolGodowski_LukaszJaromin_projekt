#include "Simulation.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

Simulation::Simulation(WrapperMap& mapa, SimulationSettings settings)
    : mapa(mapa), settings(settings)
{
}

void Simulation::run()
{
    for (currentStep = 0; currentStep < settings.stepCount; currentStep++)
    {
        mapa.update();
        drawFrame();
        wait();
    }

    drawFrame();
    std::cout << std::endl << "Symulacja zakonczona." << std::endl;
}

void Simulation::clearConsole()
{
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

void Simulation::drawHeader()
{
    std::cout << "============= SYMULACJA =============" << std::endl;
    std::cout << "Krok: " << currentStep + 1 << " / " << settings.stepCount << std::endl;
    std::cout << std::endl;
}

void Simulation::drawFrame()
{
    clearConsole();
    drawHeader();

    mapa.show();

    if (settings.showRobotPositions)
    {
        std::cout << std::endl;
        mapa.showRobotPos();
    }
}

void Simulation::wait()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(settings.delayMs));
}