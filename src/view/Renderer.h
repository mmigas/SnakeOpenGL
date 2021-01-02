#pragma once


#include <GL/glew.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "../model/Level.h"

class Renderer {
private:
    VertexArray *vertexArray;

    IndexBuffer *indexBuffer;

    VertexBufferLayout *bufferLayout;
    VertexBuffer vertexBuffer;

    void drawWalls(Level *level);

    void drawSnake(Level *level);

    void drawFood(Level *level);

    void createIndicesBuffer();

public:
    Renderer();


    void draw(Level *level);

};
