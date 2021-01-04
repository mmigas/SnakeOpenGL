#include <GL/glew.h>

#pragma once

struct Vertex {
    float x, y;
    float r, g, b, a;
};

class VertexBuffer {
private:
    unsigned int m_RendererID{};
public:
    VertexBuffer();

    ~VertexBuffer();

    void bind() const;

    void unBind() const;

    void addData(const void *data, unsigned int size, unsigned int offset) const;
};
