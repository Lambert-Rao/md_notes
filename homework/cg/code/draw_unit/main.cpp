#include <iostream>
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/transform2.hpp>
#include<glm/gtx/euler_angles.hpp>

#include <stdlib.h>
#include <stdio.h>

#include "VertexData.h"
#include "ShaderSource.h"

using namespace std;

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow* window;
GLuint vertex_shader, fragment_shader, program;
GLint mvp_location, vpos_location, vcol_location;

/// 初始化OpenGL
void init_opengl()
{
    cout<<"init opengl"<<endl;

    //设置错误回调
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    //创建窗口
    window = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);


}

/// 编译、链接Shader
void compile_shader()
{
    //创建顶点Shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    //指定Shader源码
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    //编译Shader
    glCompileShader(vertex_shader);
    //获取编译结果
    GLint compile_status=GL_FALSE;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(vertex_shader, sizeof(message), 0, message);
        cout<<"compile vs error:"<<message<<endl;
    }

    //创建片段Shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    //指定Shader源码
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    //编译Shader
    glCompileShader(fragment_shader);
    //获取编译结果
    compile_status=GL_FALSE;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(fragment_shader, sizeof(message), 0, message);
        cout<<"compile fs error:"<<message<<endl;
    }


    //创建GPU程序
    program = glCreateProgram();
    //附加Shader
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    //Link
    glLinkProgram(program);
    //获取编译结果
    GLint link_status=GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE)
    {
        GLchar message[256];
        glGetProgramInfoLog(program, sizeof(message), 0, message);
        cout<<"link error:"<<message<<endl;
    }
}

int main()
{
    init_opengl();

    compile_shader();

    //获取shader属性ID
    mvp_location = glGetUniformLocation(program, "u_mvp");
    vpos_location = glGetAttribLocation(program, "a_pos");
    vcol_location = glGetAttribLocation(program, "a_color");

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glm::mat4 model,view, projection, mvp;

        //获取画面宽高
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f/255,77.f/255,121.f/255,1.f);

        //坐标系变换
        glm::mat4 trans = glm::translate(glm::vec3(0,0,0)); //不移动顶点坐标;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(0.f), glm::radians(0.f), glm::radians(0.f)); //使用欧拉角旋转;
        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)); //缩放;
        model = trans*scale*rotation;

        view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0,0), glm::vec3(0, 1, 0));

        projection=glm::perspective(glm::radians(60.f),ratio,1.f,1000.f);

        mvp=projection*view*model;

      // 指定GPU程序(就是指定顶点着色器、片段着色器)
      glUseProgram(program);

      // 启用顶点Shader属性(a_pos)，指定与顶点坐标数据进行关联
      glEnableVertexAttribArray(vpos_location);

      // 启用顶点Shader属性(a_color)，指定与顶点颜色数据进行关联
      glEnableVertexAttribArray(vcol_location);

      // 上传mvp矩阵
      glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);

      // 在每一帧中更改要绘制的图形类型
      double time = glfwGetTime(); // 获取当前时间
      int shapeType = static_cast<int>(time) % 6; // 每秒钟更改一次图形类型

      if (shapeType == 0) {
        // 绘制点
        glPointSize(10.0f); // 设置点的大小为10.0
        glVertexAttribPointer(vpos_location,
                              3,
                              GL_FLOAT,
                              false,
                              sizeof(glm::vec3),
                              pointPosition);
        glVertexAttribPointer(vcol_location,
                              4,
                              GL_FLOAT,
                              false,
                              sizeof(glm::vec4),
                              pointColor);
        glDrawArrays(GL_POINTS, 0, 1);
      } else if (shapeType == 1) {
      // 绘制线
      glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(glm::vec3), linePositions);
      glVertexAttribPointer(vcol_location, 4, GL_FLOAT, false, sizeof(glm::vec4), lineColors);
      glDrawArrays(GL_LINES, 0, 2);
      } else if (shapeType == 2) {
      // 绘制多线段
      glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(glm::vec3), polylinePositions);
      glVertexAttribPointer(vcol_location, 4, GL_FLOAT, false, sizeof(glm::vec4), polylineColors);
      glDrawArrays(GL_LINE_STRIP, 0, 4);
      } else if (shapeType == 3) {
      // 绘制循环线
            glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(glm::vec3), looplinePositions);
            glVertexAttribPointer(vcol_location, 4, GL_FLOAT, false, sizeof(glm::vec4), looplineColors);
            glDrawArrays(GL_LINE_LOOP, 0, 4);
      } else if (shapeType == 4) {
      // 绘制三角形
      glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(glm::vec3), trianglePositions);
      glVertexAttribPointer(vcol_location, 4, GL_FLOAT, false, sizeof(glm::vec4), triangleColors);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      } else if (shapeType == 5) {
        // 绘制三角形条带
        glVertexAttribPointer(vpos_location,
                              3,
                              GL_FLOAT,
                              false,
                              sizeof(glm::vec3),
                              triangleStripPositions);
        glVertexAttribPointer(vcol_location,
                              4,
                              GL_FLOAT,
                              false,
                              sizeof(glm::vec4),
                              triangleStripColors);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
      }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}