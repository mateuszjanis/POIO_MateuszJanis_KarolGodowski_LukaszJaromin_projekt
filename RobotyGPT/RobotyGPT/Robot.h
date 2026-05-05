#pragma once
#ifndef ROBOT_H
#define ROBOT_H

#include "Position.h"

class Robot {
private:
    int id;
    Position position;
    int speed;

public:
    Robot(int id, Position position, int speed);

    int getId() const;
    Position getPosition() const;
    int getSpeed() const;

    void setPosition(Position newPosition);
};

#endif