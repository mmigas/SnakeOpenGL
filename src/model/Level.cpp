
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
        std::cout << level->at(i->getY()).at(i->getX()) << std::endl;
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

std::vector<int> Level::getXAvailable() {
    std::vector<int> vector;
    for (int i = 0; i < level->size(); i++) {
        for (int j = 0; j < level->at(i).size(); j++) {
            if (level->at(i).at(j) == 'f') {
                vector.push_back(i);
                break;
            }
        }
    }
    return vector;
}

std::vector<int> Level::getYAvailable(int x) {
    std::vector<int> vector;
    for (int j = 0; j < level->at(x).size(); j++) {
        if (level->at(x).at(j) == 'f') {
            vector.push_back(j);
        }
    }
    return vector;
}


void Level::spawnFood() {
    int x;
    int y;
    std::vector<int> xPossibilities = getXAvailable();
    srand((unsigned) time(0));
    x = xPossibilities.at(rand() % (xPossibilities.size() - 1));
    std::vector<int> yPossibilities = getYAvailable(x);
    srand((unsigned) time(0));
    y = yPossibilities.at(rand() % (yPossibilities.size() - 1));

    level->at(y).at(x) = 'a';
}

bool Level::willSnakeEat() {
    int x = snake->getPosition()->getX() + snake->getDirection()->getX();
    int y = snake->getPosition()->getY() + snake->getDirection()->getY();
    return level->at(y).at(x) == 'a';
}


bool Level::update() {
    level->at(snake->getSegments()->at(snake->getSegments()->size() - 1)->getY()).at(
            snake->getSegments()->at(snake->getSegments()->size() - 1)->getX()) = 'f';
    snake->changeDirection();

    if (willSnakeEat()) {
        snake->grow();
        level->at(snake->getPosition()->getY()).at(snake->getPosition()->getX()) = 's';
        spawnFood();
        return true;
    } else {
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

