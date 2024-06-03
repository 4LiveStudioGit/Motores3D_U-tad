#include "Shader.h"
#include "Vertex.h"
#include "GL/glew.h"



Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode = readShaderFile(vertexPath);
    std::string fragmentCode = readShaderFile(fragmentPath);

    uint32_t vertexShaderId = compileShader(vertexCode, GL_VERTEX_SHADER);
    uint32_t fragmentShaderId = compileShader(fragmentCode, GL_FRAGMENT_SHADER);

    m_id = linkProgram(vertexShaderId, fragmentShaderId);

    // Obtener y almacenar las localizaciones de todas las variables attribute
    GLint numAttributes;
    glGetProgramiv(m_id, GL_ACTIVE_ATTRIBUTES, &numAttributes);
    for (int i = 0; i < numAttributes; ++i) {
        char name[256];
        GLsizei length;
        GLint size;
        GLenum type;
        glGetActiveAttrib(m_id, i, sizeof(name), &length, &size, &type, name);
        int loc = glGetAttribLocation(m_id, name);
        m_attributeLocations.push_back(loc);
    }
}

Shader::~Shader() {
    glDeleteProgram(m_id);
}


uint32_t Shader::getId() const {
    return m_id;
}

const char* Shader::getError() const {
    return m_error.c_str();
}

void Shader::use() const {
    glUseProgram(m_id);
}

void Shader::setupAttribs() const {
    for (int loc : m_attributeLocations) {
        if (loc != -1) {
            glEnableVertexAttribArray(loc);
        }
    }
}

int Shader::getLocation(const char* name) const {
    return glGetUniformLocation(m_id, name);
}

void Shader::setInt(int loc, int val) {
    if (loc != -1) {
        glUniform1i(loc, val);
    }
}

void Shader::setFloat(int loc, float val) {
    if (loc != -1) {
        glUniform1f(loc, val);
    }
}

void Shader::setVec3(int loc, const glm::vec3& vec) {
    if (loc != -1) {
        glUniform3fv(loc, 1, &vec[0]);
    }
}

void Shader::setVec4(int loc, const glm::vec4& vec) {
    if (loc != -1) {
        glUniform4fv(loc, 1, &vec[0]);
    }
}

void Shader::setMatrix(int loc, const glm::mat4& matrix) {
    if (loc != -1) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
    }
}

std::string Shader::readShaderFile(const std::string& filePath) {
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

uint32_t Shader::compileShader(const std::string& source, GLenum type) {
    uint32_t shaderId = glCreateShader(type);
    const char* sourcePtr = source.c_str();
    glShaderSource(shaderId, 1, &sourcePtr, nullptr);
    glCompileShader(shaderId);

    GLint success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
        m_error = "Shader compilation error:\n" + std::string(infoLog);
        glDeleteShader(shaderId);
        return 0;
    }

    return shaderId;
}

uint32_t Shader::linkProgram(uint32_t vertexShaderId, uint32_t fragmentShaderId) {
    uint32_t programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    GLint success;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(programId, 512, nullptr, infoLog);
        m_error = "Shader linking error:\n" + std::string(infoLog);
        glDeleteProgram(programId);
        return 0;
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
}

