#include "VertexArray.h"
#include "ErrorCatcher.h"


VertexArray::VertexArray() {
    GlCall( glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray() {
    GlCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &bufferLayout) {
    bind();
    vertexBuffer.bind();
    const auto &elements = bufferLayout.getElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto &element = elements[i];
        GlCall(glEnableVertexAttribArray(0));
        GlCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, bufferLayout.getStride(),
                              (const void *) (offset)));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::bind() const {
    GlCall(glBindVertexArray(m_RendererID));
}

void VertexArray::unbind() const {
    GlCall(glBindVertexArray(0));
}
