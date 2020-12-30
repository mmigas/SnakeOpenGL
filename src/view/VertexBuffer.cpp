#include <GL/glew.h>
#include "VertexBuffer.h"
#include "ErrorCatcher.h"

VertexBuffer::VertexBuffer() {
    GlCall(glGenBuffers(1, &m_RendererID));
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GlCall(glBufferData(GL_ARRAY_BUFFER, 18 * 18 * 8 * sizeof(float), nullptr, GL_DYNAMIC_DRAW));
}


VertexBuffer::~VertexBuffer() {
    GlCall(glDeleteBuffers(1, &m_RendererID));
}


void VertexBuffer:: addData(const void *data, unsigned int size, unsigned int offset) const {
    bind();
    GlCall(glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(float), size, data));
}

void VertexBuffer::bind() const {
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::unBind() const {
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
