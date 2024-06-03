#include "Buffer.h"


Buffer::Buffer(const float* vertices, int numVertices, const int* indices, int numIndices)
: m_numIndices(numIndices) {
    glGenBuffers(1, &m_vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(float), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &m_indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(uint16_t), indices, GL_STATIC_DRAW);
}
Buffer::~Buffer() {
    glDeleteBuffers(1, &m_vertexBufferId);
    glDeleteBuffers(1, &m_indexBufferId);
}

void Buffer::draw(const Shader& shader) const {
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);

    shader.setupAttribs();
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_SHORT, nullptr);
}
