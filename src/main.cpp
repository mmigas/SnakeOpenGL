#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include "model/Level.h"
#include "controller/Inputs.h"
#include "view/Renderer.h"

int main() {

    Level *level = new Level(18, 18);
    level->createLevel();

    Inputs *inputs = new Inputs();

    GLFWwindow *window;
    double lastTime = glfwGetTime();
    int frames = 0;
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(window, Inputs::glfw_key_callback);
    glfwSetWindowUserPointer(window, level);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
    }
    {
        Renderer *renderer = new Renderer();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            double currentTime = glfwGetTime();
            frames++;

            if (currentTime - lastTime >= 0.15) {
                printf("%f ms/frame\n", 150.0 / double(frames));
                if (!level->update()) {
                    break;
                }
                frames = 0;
                lastTime += 0.150;
            }

            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);
            renderer->draw(level);
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

        }

    }
    glfwTerminate();
    return 0;
}

