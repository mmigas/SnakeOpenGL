#pragma once


#include "../model/Level.h"

#include <GLFW/glfw3.h>
#include "../controller/Coordinates.h"

class Inputs {

public:

    Inputs();

    static void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
};


