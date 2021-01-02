
#include <iostream>
#include <random>
#include <ctime>
#include "Level.h"


Level::Level(int height, int width) {
    this->height = height;
    this->width = width;
    level = new std::vector<std::vector<char>>(height, std::vector<char>(width, 'f'));
    this->snake = new Snake(5, 5);
}


Level::~Level() {
    delete (snake);
    delete (level);
}

void Level::createLevel() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (y == 0 || x == 0 || x == height - 1 || y == width - 1) {
                level->at(y).at(x) = 'w';
            } else {
                level->at(y).at(x) = 'f';
            }
        }
    }

    for (Coordinates *i : *snake->getSegments()) {
        level->at(i->getY()).at(i->getX()) = 's';
    }
    spawnFood();
}

bool Level::hasSnakeCollided() {
    Coordinates *headCoords = snake->getPosition();

    if (level->at(headCoords->getY()).at(headCoords->getX()) == 'w' ||
        level->at(headCoords->getY()).at(headCoords->getX()) == 's') {
        return true;
    }
    return false;
}

std::vector<int> Level::getYAvailable() {
    std::vector<int> vector;
    for (int y = 0; y < level->size(); y++) {
        for (int x = 0; x < level->at(y).size(); x++) {
            if (level->at(y).at(x) == 'f') {
                vector.push_back(y);
                break;
            }
        }
    }
    return vector;
}

std::vector<int> Level::getXAvailable(int y) {
    std::vector<int> vector;
    for (int x = 0; x < level->at(y).size(); x++) {
        if (level->at(y).at(x) == 'f') {
            vector.push_back(x);
        }
    }
    return vector;
}


void Level::spawnFood() {
    int x;
    int y;
    std::vector<int> yPossibilities = getYAvailable();
    srand((unsigned) time(nullptr));
    y = yPossibilities.at(rand() % (yPossibilities.size() - 1));
    std::vector<int> xPossibilities = getXAvailable(y);
    srand((unsigned) time(nullptr));
    x = xPossibilities.at(rand() % (xPossibilities.size() - 1));
    level->at(y).at(x) = 'a';
}

bool Level::willSnakeEat() {
    int x = snake->getPosition()->getX() + snake->getDirection()->getX();
    int y = snake->getPosition()->getY() + snake->getDirection()->getY();
    return level->at(y).at(x) == 'a';
}


bool Level::update() {
    snake->changeDirection();

    if (willSnakeEat()) {
        snake->grow();
        level->at(snake->getPosition()->getY()).at(snake->getPosition()->getX()) = 's';
        spawnFood();
        return true;
    } else {
        level->at(snake->getSegments()->at(snake->getSegments()->size() - 1)->getY()).at(
                snake->getSegments()->at(snake->getSegments()->size() - 1)->getX()) = 'f';
        snake->moveSnake();
    }

    if (hasSnakeCollided()) {
        return false;
    }

    level->at(snake->getPosition()->getY()).at(snake->getPosition()->getX()) = 's';
    return true;
}

void Level::printLevel() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << level->at(y).at(x);
        }
        std::cout << "" << std::endl;
    }
}

Snake *Level::getSnake() {
    return this->snake;
}

std::vector<std::vector<char>> *Level::getLevel() {
    return level;
}

