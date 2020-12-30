
#include <iostream>
#include "Snake.h"

Snake::Snake(int x, int y) {
    this->segments = new std::vector<Coordinates *>;
    this->changeQueue = new std::vector<Coordinates *>;
    this->position = new Coordinates(x, y);
    this->segments->push_back(this->position);

    Coordinates *tempSegment = new Coordinates(x - 1, y);
    this->segments->push_back(tempSegment);
    Coordinates *tempSegment2 = new Coordinates(x - 2, y);
    this->segments->push_back(tempSegment2);
    this->direction = new Coordinates(1, 0);
}

Snake::~Snake() {
    delete (this->position);
    delete (this->segments);
}

void Snake::changeDirection() {
    if (changeQueue->empty()) {
        return;
    }

    Coordinates *tempDirection = changeQueue->at(0);
    changeQueue->erase(changeQueue->begin());
    if (this->direction->getX() == 1 && tempDirection->getX() == -1 ||
        this->direction->getX() == -1 && tempDirection->getX() == 1 ||
        this->direction->getY() == -1 && tempDirection->getY() == 1 ||
        this->direction->getY() == 1 && tempDirection->getY() == -1) {
        return;
    }

    this->direction->setX(tempDirection->getX());
    this->direction->setY(tempDirection->getY());
    delete (tempDirection);
}

void Snake::moveSnake() {
    for (unsigned int i = this->segments->size() - 1; i > 0; i--) {
        this->segments->at(i)->setX(this->segments->at(i - 1)->getX());
        this->segments->at(i)->setY(this->segments->at(i - 1)->getY());
    }

    position->setX(position->getX() + direction->getX());
    position->setY(position->getY() + direction->getY());
}

void Snake::grow() {
    Coordinates *coordinates = new Coordinates();
    coordinates->setX(position->getX() + direction->getX());
    coordinates->setY(position->getY() + direction->getY());
    this->segments->insert(segments->begin(), coordinates);
    this->position = coordinates;
}

Coordinates *Snake::getPosition() {
    return position;
}

Coordinates *Snake::getDirection() {
    return direction;
}

std::vector<Coordinates *> *Snake::getSegments() {
    return segments;
}

std::vector<Coordinates *> *Snake::getChangeQueue() {
    return this->changeQueue;
}





