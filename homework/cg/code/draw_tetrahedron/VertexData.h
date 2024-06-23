//
// Created by captain on 2021/3/25.
// 顶点坐标 顶点颜色
//

#ifndef UNTITLED_VERTEXDATA_H
#define UNTITLED_VERTEXDATA_H

#include <glm/glm.hpp>

// 定义四面体的顶点位置
static const glm::vec3 tetrahedronPositions[4] = {
    glm::vec3{0.0f, 1.0f, 0.0f},
    glm::vec3{0.0f, 0.0f, 1.0f},
    glm::vec3{1.0f, 0.0f, 0.0f},
    glm::vec3{-1.0f, 0.0f, 0.0f}
};
// 定义四面体的顶点颜色
static const glm::vec4 tetrahedronColors[4] = {
    glm::vec4{250.0f / 255.0f, 250.0f/ 255.0f, 250.0f / 255.0f, 1.0f},
    glm::vec4{170.0f / 255.0f, 0.0f/ 255.0f, 0.0f / 255.0f, 1.0f},
    glm::vec4{10.0f / 255.0f, 20.0f/ 255.0f, 60.0f / 255.0f, 1.0f},
    glm::vec4{223.0f / 255.0f, 170.0f/ 255.0f, 66.0f / 255.0f, 1.0f},
};

#endif //UNTITLED_VERTEXDATA_H
