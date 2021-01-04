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

    VertexBuffer vertexBuffer;

    void createIndicesBuffer();

public:
    Renderer();


    void draw(Level *level);

};
