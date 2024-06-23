#ifndef UNTITLED_VERTEXDATA_H
#define UNTITLED_VERTEXDATA_H

#include <glm/glm.hpp>
#include "glad/gl.h"

static const glm::vec3 kPositions[8] = {
    glm::vec3(-1.0f, -1.0f, 1.0f),
    glm::vec3(1.0f, -1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(-1.0f, 1.0f, 1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(1.0f, -1.0f, -1.0f),
    glm::vec3(1.0f, 1.0f, -1.0f),
    glm::vec3(-1.0f, 1.0f, -1.0f)
};

static const glm::vec4 kColors[8] = {
    glm::vec4(1, 0, 0, 1),
    glm::vec4(0, 1, 0, 1),
    glm::vec4(0, 0, 1, 1),
    glm::vec4(1, 1, 0, 1),
    glm::vec4(1, 0, 1, 1),
    glm::vec4(0, 1, 1, 1),
    glm::vec4(1, 1, 1, 1),
    glm::vec4(0, 0, 0, 1)
};

static const GLuint indices[48] = {
    0, 1, 2, 0xFFFFFFFF,
    0, 2, 3, 0xFFFFFFFF,
    4, 5, 6, 0xFFFFFFFF,
    4, 6, 7, 0xFFFFFFFF,
    0, 1, 5, 0xFFFFFFFF,
    0, 5, 4, 0xFFFFFFFF,
    2, 3, 7, 0xFFFFFFFF,
    2, 7, 6, 0xFFFFFFFF,
    0, 3, 7, 0xFFFFFFFF,
    0, 7, 4, 0xFFFFFFFF,
    1, 2, 6, 0xFFFFFFFF,
    1, 6, 5, 0xFFFFFFFF
};

#endif //UNTITLED_VERTEXDATA_H