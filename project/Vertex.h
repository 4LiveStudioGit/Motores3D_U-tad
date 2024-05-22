#pragma once
#include "../lib/glm/glm.hpp"

struct Vertex {
        glm::vec3 position;

        Vertex(const glm::vec3& pos) : position(pos) {}
    };
    

