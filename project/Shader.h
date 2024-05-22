#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Vertex.h"
#include "GL/glew.h"

class Shader
{
public:
    Shader(const std::string& vertexShader, const std::string& fragmentShader);
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
    

    std::string readString(const std::string& filename);
    
    uint32_t RendererID;
    const char* Error;
    std::string ReadString;
    GLuint buffers[2];
    


};
