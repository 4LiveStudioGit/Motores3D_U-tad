#pragma once


#include <cstdint>
#include <GL/glew.h>
#include "Shader.h"


class Buffer {
public:
    Buffer(const float* vertices, int numVertices, const int* indices, int numIndices);
    ~Buffer();

    void draw(const Shader& shader) const;

private:
    GLuint m_vertexBufferId;
    GLuint m_indexBufferId;
    int m_numIndices;
};