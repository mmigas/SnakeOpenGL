//
// Created by Miguel Faria on 12/26/2020.
//

#include "Inputs.h"

Inputs::Inputs() = default;

void Inputs::glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS) {
        return;
    }
    Coordinates *direction = new Coordinates;
    Level *level = static_cast<Level *>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_W) {
        direction->setX(0);
        direction->setY(-1);
    }
    if (key == GLFW_KEY_S) {
        direction->setX(0);
        direction->setY(1);
    }
    if (key == GLFW_KEY_D) {
        direction->setX(1);
        direction->setY(0);
    }
    if (key == GLFW_KEY_A) {
        direction->setX(-1);
        direction->setY(0);
    }


    if (!level->getSnake()->getChangeQueue()->empty() &&
        (level->getSnake()->getChangeQueue()->at(level->getSnake()->getChangeQueue()->size() - 1)->getX() ==
         direction->getX() ||
         level->getSnake()->getChangeQueue()->at(level->getSnake()->getChangeQueue()->size() - 1)->getY() ==
         direction->getY())) {
        return;
    }
    level->getSnake()->getChangeQueue()->push_back(direction);
}
