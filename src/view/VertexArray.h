#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private:
    unsigned int m_RendererID;
public:
    VertexArray();

    ~VertexArray();

    void AddBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &bufferLayout);

    void bind() const;

    void unbind() const;
};

