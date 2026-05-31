#pragma once
#include "Map.h"

class WrapperMap
{
private:
    Map* mapa = nullptr;

public:
    WrapperMap(int x_len, int y_len);
    ~WrapperMap();

    void show();
    int placeRobot(int x, int y);
    int placeObstacle(int x, int y);
    void update();
    void showRobotPos();
    void setInitialForces();

    bool saveToFile(const std::string& fileName);
    bool loadFromFile(const std::string& fileName);

    int getSizeX();
    int getSizeY();
    int getRobotNum();
    int getObstacleNum();

    std::vector<std::vector<int>> getMap();
    std::vector<int> getRobotPos(int id);

    int getRobotMoveCount(int id);
    int getRobotLastMoveX(int id);
    int getRobotLastMoveY(int id);

    bool undoLastState();
};
