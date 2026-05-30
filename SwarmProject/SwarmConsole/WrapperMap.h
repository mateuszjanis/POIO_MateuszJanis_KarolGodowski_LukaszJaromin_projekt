#pragma once
#include "Map.h"
#include <string>

class WrapperMap
{
    Map* mapa = new Map(20, 20);

public:
    ~WrapperMap();
    WrapperMap(int x_len, int y_len);
    void show();
    int placeRobot(int x, int y);
    int placeObstacle(int x, int y);
    void update();
    void showRobotPos();
    bool saveToFile(const std::string& fileName);
    bool loadFromFile(const std::string& fileName);
    
    void setInitialForces();

private:

};