#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Vertex.h"
#include "GL/glew.h"
#include <string>

#include <vector>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    uint32_t getId() const;
    const char* getError() const;
    void use() const;
    void setupAttribs() const;
    int getLocation(const char* name) const;
    void setInt(int loc, int val);
    void setFloat(int loc, float val);
    void setVec3(int loc, const glm::vec3& vec);
    void setVec4(int loc, const glm::vec4& vec);
    void setMatrix(int loc, const glm::mat4& matrix);

private:
    uint32_t m_id;
    std::string m_error;
    std::vector<int> m_attributeLocations;

    std::string readShaderFile(const std::string& filePath);
    uint32_t compileShader(const std::string& source, GLenum type);
    uint32_t linkProgram(uint32_t vertexShaderId, uint32_t fragmentShaderId);
};