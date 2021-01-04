#include "VertexBuffer.h"

class VertexArray {
private:
    unsigned int m_RendererID;
public:
    VertexArray();

    ~VertexArray();

    void AddNewBuffer(const VertexBuffer &vertexBuffer) const;

    void bind() const;

    void unbind() const;
};

