#pragma once

#include <vector>
#include "../controller/Coordinates.h"
#include "Snake.h"


class Level {
private:
    int height, width;
    std::vector<std::vector<char>> *level;
    Snake *snake;

    bool hasSnakeCollided();

public:

    Level(int height, int width);

    ~Level();

    void createLevel();

    bool update();

    Snake *getSnake();

    std::vector<std::vector<char>> *getLevel();

    void printLevel();

    void spawnFood();

    bool willSnakeEat();


    std::vector<int> getYAvailable();

    std::vector<int> getXAvailable(int x);
};


