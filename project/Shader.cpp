#include "Shader.h"

#include "GL/glew.h"

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
{
    std::string ArrayBuffer = readString(vertexShader);
    std::string FragmentCode = readString(fragmentShader);
    glGenBuffers(2,buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    RendererID = glCreateProgram();
}

uint32_t Shader::getId() const
{
    return RendererID;
}

const char* Shader::getError() const
{
    
}

void Shader::use() const
{
}

void Shader::setupAttribs() const
{
}

int Shader::getLocation(const char* name) const
{
}

void Shader::setInt(int loc, int val)
{
}

void Shader::setFloat(int loc, float val)
{
}

void Shader::setVec3(int loc, const glm::vec3& vec)
{
}

void Shader::setVec4(int loc, const glm::vec4& vec)
{
}

void Shader::setMatrix(int loc, const glm::mat4& matrix)
{
}

std::string Shader::readString(const std::string& filename)
{
    std::ifstream istream(filename.c_str(), std::ios_base::binary);
    std::stringstream sstream;
    sstream << istream.rdbuf();
    return sstream.str();
}
