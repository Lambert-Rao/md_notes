//
// Created by captain on 2021/3/25.
//

#ifndef UNTITLED_SHADERSOURCE_H
#define UNTITLED_SHADERSOURCE_H

//顶点着色器代码
static const char* vertex_shader_text =
    "#version 110\n"

    "uniform mat4 u_mvp;\n"
    "uniform vec3 u_lightPos;\n"
    "uniform int u_lightingModel;\n" // 0 for Gouraud, 1 for Phong

    "attribute  vec3 a_pos;\n"
    "attribute  vec3 a_normal;\n"
    "attribute  vec4 a_color;\n"

    "varying vec4 v_color;\n"
    "varying vec3 v_normal;\n"
    "varying vec3 v_lightDir;\n"

    "void main()\n"
    "{\n"
    "    gl_Position = u_mvp * vec4(a_pos, 1.0);\n"
    "    v_normal = a_normal;\n"
    "    v_lightDir = normalize(u_lightPos - a_pos);\n"
    "    if (u_lightingModel == 0) {"
    "        float diff = max(dot(v_normal, v_lightDir), 0.0);\n"
    "        v_color = diff * a_color;\n"
    "    } else {"
    "        v_color = a_color;\n"
    "    }"
    "}\n";

//片段着色器代码
static const char* fragment_shader_text =
    "#version 110\n"
    "uniform int u_lightingModel;\n" // 0 for Gouraud, 1 for Phong

    "varying vec4 v_color;\n"
    "varying vec3 v_normal;\n"
    "varying vec3 v_lightDir;\n"

    "void main()\n"
    "{\n"
    "    if (u_lightingModel == 1) {"
    "        float diff = max(dot(v_normal, v_lightDir), 0.0);\n"
    "        gl_FragColor = diff * v_color;\n"
    "    } else {"
    "        gl_FragColor = v_color;\n"
    "    }"
    "}\n";

#endif //UNTITLED_SHADERSOURCE_H
