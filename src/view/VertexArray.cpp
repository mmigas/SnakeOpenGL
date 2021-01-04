#include "VertexArray.h"
#include "ErrorCatcher.h"


VertexArray::VertexArray() {
    GlCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray() {
    GlCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddNewBuffer(const VertexBuffer &vertexBuffer) const {
    bind();
    vertexBuffer.bind();
    GlCall(glEnableVertexAttribArray(0));
    GlCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) nullptr));

    GlCall(glEnableVertexAttribArray(1));
    GlCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) (2 * sizeof(float))));
}

void VertexArray::bind() const {
    GlCall(glBindVertexArray(m_RendererID));
}

void VertexArray::unbind() const {
    GlCall(glBindVertexArray(0));
}
