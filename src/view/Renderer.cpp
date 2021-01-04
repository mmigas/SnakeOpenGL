#include "Renderer.h"
#include "ErrorCatcher.h"

const float SQUARE_WIDTH = 30.0f;
const float SQUARE_HEIGHT = 30.0f;

Renderer::Renderer() {
    vertexArray = new VertexArray();
    vertexArray->AddNewBuffer(vertexBuffer);
    createIndicesBuffer();

    Shader shader("../res/shaders/basic.shader");
    shader.bind();
}

void createVertex(Vertex *vertex, float x, float y, float r, float g, float b, float a) {
    vertex->x = x;
    vertex->y = y;
    vertex->r = r;
    vertex->g = g;
    vertex->b = b;
    vertex->a = a;
}

void createSquare(Vertex positions[], int offset, int x, int y, float r, float g, float b) {
    createVertex(&positions[0 + offset], x * SQUARE_WIDTH, y * SQUARE_HEIGHT, r, g, b, 1.0f);
    createVertex(&positions[1 + offset], x * SQUARE_WIDTH + SQUARE_WIDTH, y * SQUARE_HEIGHT, r, g, b, 1.0f);
    createVertex(&positions[2 + offset], x * SQUARE_WIDTH + SQUARE_WIDTH, y * SQUARE_HEIGHT + SQUARE_HEIGHT, r, g,
                 b, 1.0f);
    createVertex(&positions[3 + offset], x * SQUARE_WIDTH, y * SQUARE_HEIGHT + SQUARE_HEIGHT, r, g, b, 1.0f);
}

void Renderer::draw(Level *level) {
    Vertex positions[18 * 18 * 4];
    int offset = 0;
    int counter = 0;
    for (int y = 0; y < level->getLevel()->size(); y++) {
        for (int x = 0; x < level->getLevel()->at(y).size(); x++) {
            if (level->getLevel()->at(y).at(x) == 'w') {
                createSquare(positions, offset, x, y, 0.8f, 0.8f, 0.8f);
                offset += 4;
                counter += 1;
            } else if (level->getLevel()->at(y).at(x) == 's') {
                createSquare(positions, offset, x, y, 0, 0, 1);
                offset += 4;
                counter += 1;
            } else if (level->getLevel()->at(y).at(x) == 'a') {
                createSquare(positions, offset, x, y, 1, 0, 0);
                offset += 4;
                counter += 1;
            }
        }
    }

    vertexBuffer.addData(positions, sizeof(positions), 0 * sizeof(Vertex));
    vertexArray->bind();
    indexBuffer->bind();
    glDrawElements(GL_TRIANGLES, counter * 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer::createIndicesBuffer() {
    unsigned int indices[18 * 18 * 6];
    int offset = 0;
    for (int i = 0; i < 18 * 18 * 6; i += 6) {
        indices[i] = offset;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;

        indices[i + 3] = offset + 0;
        indices[i + 4] = offset + 2;
        indices[i + 5] = offset + 3;
        offset += 4;
    }
    indexBuffer = new IndexBuffer(indices, 18 * 18 * 6);
}




