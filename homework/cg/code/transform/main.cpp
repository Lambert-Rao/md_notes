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
  window = glfwCreateWindow(960, 640, "transformation", NULL, NULL);
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

    // 在每一帧中更改要绘制的图形类型
    double time = glfwGetTime(); // 获取当前时间
    int transformType = static_cast<int>(time) % 7; // 每秒钟更改一次变换类型

    // 根据当前的变换类型来选择使用哪种变换方式
    if (transformType == 0) {
      // 原图
      std::cout << "Displaying original image." << std::endl;
      model = glm::mat4(1.0f); // 单位矩阵，不进行任何变换
    } else if (transformType == 1) {
      // 平移
      std::cout << "Applying translation transformation." << std::endl;
      glm::vec4 transVec = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); // 齐次坐标
      model = glm::translate(glm::mat4(1.0f), glm::vec3(transVec));
    } else if (transformType == 2) {
      // 旋转
      std::cout << "Applying rotation transformation around point (0,0)." << std::endl;
      float angle = glm::radians(90.0f);
      glm::vec4 axis = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f); // 齐次坐标
      model = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(axis));
    } else if (transformType == 3) {
      // 缩放
      std::cout << "Applying scale transformation." << std::endl;
      glm::vec4 scaleVec = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f); // 齐次坐标
      model = glm::scale(glm::mat4(1.0f), glm::vec3(scaleVec));
    } else if (transformType == 4) {
      // 组合操作
      std::cout << "Applying combined transformation." << std::endl;
      glm::vec4 transVec = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); // 齐次坐标
      glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(transVec));
      float angle = glm::radians(90.0f);
      glm::vec4 axis = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f); // 齐次坐标
      glm::mat4 rot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(axis));
      glm::vec4 scaleVec = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f); // 齐次坐标
      glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleVec));
      model = trans * rot * scale;
    } else if (transformType == 5) {
      // 错切
      std::cout << "Applying shear transformation." << std::endl;
      model = glm::shearX3D(glm::mat4(1.0f), 1.0f, 0.0f);
    } else if (transformType == 6) {
      // 翻转
      std::cout << "Applying flip transformation." << std::endl;
      glm::vec4 flipVec = glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f); // 齐次坐标
      model = glm::scale(glm::mat4(1.0f), glm::vec3(flipVec));
    }

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

    // 绘制三角形
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(glm::vec3), trianglePositions);
    glVertexAttribPointer(vcol_location, 4, GL_FLOAT, false, sizeof(glm::vec4), triangleColors);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);

  glfwTerminate();
  exit(EXIT_SUCCESS);
}