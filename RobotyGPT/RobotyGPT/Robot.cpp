#include "Robot.h"

Robot::Robot(int id, Position position, int speed)
    : id(id), position(position), speed(speed) {
}

int Robot::getId() const {
    return id;
}

Position Robot::getPosition() const {
    return position;
}

int Robot::getSpeed() const {
    return speed;
}

void Robot::setPosition(Position newPosition) {
    position = newPosition;
}