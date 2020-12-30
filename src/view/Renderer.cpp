#include <iostream>
#include "Renderer.h"
#include "ErrorCatcher.h"


Renderer::Renderer() {
    bufferLayout = new VertexBufferLayout();
    vertexArray = new VertexArray();
    bufferLayout->Push<float>(2);
    vertexArray->AddBuffer(vertexBuffer, *bufferLayout);

    createIndicesBuffer();
}

void Renderer::draw(Level *level) {
    float positions[18 * 18 * 8];
    int offset = 0;
    counter = 0;
    for (int yy = 0; yy < level->getLevel()->size(); yy++) {
        for (int xx = 0; xx < level->getLevel()->at(yy).size(); xx++) {
            if (level->getLevel()->at(yy).at(xx) == 'w' || level->getLevel()->at(yy).at(xx) == 's' ||
                level->getLevel()->at(yy).at(xx) == 'a') {
                float x = (xx + 1) * 30;
                float y = (yy + 1) * 30;

                positions[offset] = x - 15;
                positions[offset + 1] = y - 15;
                positions[offset + 2] = x + 15;
                positions[offset + 3] = y - 15;
                positions[offset + 4] = x + 15;
                positions[offset + 5] = y + 15;
                positions[offset + 6] = x - 15;
                positions[offset + 7] = y + 15;
                offset += 8;
                counter += 1;
            }
        }
    }
    vertexBuffer.addData(positions, sizeof(positions), 0);
    Shader shader("../res/shaders/basic.shader");
    shader.bind();
    shader.setUniform4f("u_Color", 0.8f, 0.8f, 0.8f, 1.0f);
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




