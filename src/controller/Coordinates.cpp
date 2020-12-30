//
// Created by Miguel Faria on 12/25/2020.
//

#include "Coordinates.h"

Coordinates::Coordinates(int x, int y) {
    this->x = x;
    this->y = y;
}

Coordinates::~Coordinates() {

}

void Coordinates::setX(int x) {
    this->x = x;
}

int Coordinates::getX() {
    return x;
}

void Coordinates::setY(int y) {
    this->y = y;
}

int Coordinates::getY() {
    return y;
}
