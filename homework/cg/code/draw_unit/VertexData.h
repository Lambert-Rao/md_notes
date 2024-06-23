//
// Created by captain on 2021/3/25.
// 顶点坐标 顶点颜色
//

#ifndef UNTITLED_VERTEXDATA_H
#define UNTITLED_VERTEXDATA_H

#include <glm/glm.hpp>


// 点
static const glm::vec3 pointPosition[1] = {glm::vec3{0.0f, 0.0f, 0.0f}};
static const glm::vec4 pointColor[1] = {glm::vec4{0.5f, 0.0f, 0.5f, 1.0f}};// 紫色

// 线
static const glm::vec3 linePositions[2] = {
    glm::vec3{-0.5f, -0.5f, 0.0f},
    glm::vec3{0.5f, 0.5f, 0.0f}
};
static const glm::vec4 lineColors[2] = {
    glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}, // 绿色
    glm::vec4{0.5f, 0.0f, 0.5f, 1.0f}, // 紫色
};

// 多线段
static const glm::vec3 polylinePositions[4] = {
    glm::vec3{-0.5f, -0.5f, 0.0f},
    glm::vec3{0.0f, 0.5f, 0.0f},
    glm::vec3{0.5f, -0.5f, 0.0f},
    glm::vec3{-0.5f, 0.0f, 0.0f}
};
static const glm::vec4 polylineColors[4] = {
    glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}, // 绿色
    glm::vec4{0.5f, 0.0f, 0.5f, 1.0f}, // 紫色
    glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}, // 绿色
    glm::vec4{0.5f, 0.0f, 0.5f, 1.0f}  // 紫色
};

// 循环线
static const glm::vec3 looplinePositions[4] = {
    glm::vec3{-0.5f, -0.5f, 0.0f},
    glm::vec3{0.0f, 0.5f, 0.0f},
    glm::vec3{0.5f, -0.5f, 0.0f},
    glm::vec3{-0.5f, -0.5f, 0.0f}
};
static const glm::vec4 looplineColors[4] = {
    glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}, // 绿色
    glm::vec4{0.5f, 0.0f, 0.5f, 1.0f}, // 紫色
    glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}, // 绿色
    glm::vec4{0.5f, 0.0f, 0.5f, 1.0f}  // 紫色
};

// 三角形
static const glm::vec3 trianglePositions[3] = {
    glm::vec3{-0.5f, -0.5f, 0.0f},
    glm::vec3{0.5f, -0.5f, 0.0f},
    glm::vec3{0.0f, 0.5f, 0.0f}
};
static const glm::vec4 triangleColors[3] = {
    glm::vec4{0.5f, 0.0f, 0.5f, 1.0f}, // 紫色
    glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}, // 绿色
    glm::vec4{0.5f, 0.0f, 0.5f, 1.0f}  // 紫色
};

// 三角形条带
static const glm::vec3 triangleStripPositions[4] = {
    glm::vec3{-0.4f, -0.5f, 0.0f},
    glm::vec3{0.5f, -0.7f, 0.0f},
    glm::vec3{-0.3f, 0.5f, 0.0f},
    glm::vec3{0.5f, 1.0f, 0.0f}
};
static const glm::vec4 triangleStripColors[4] = {
    glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}, // 绿色
    glm::vec4{0.5f, 0.0f, 0.5f, 1.0f}, // 紫色
    glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}, // 绿色
    glm::vec4{0.5f, 0.0f, 0.5f, 1.0f}, // 紫色
};

#endif //UNTITLED_VERTEXDATA_H
