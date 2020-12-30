#pragma once

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
