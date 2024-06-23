#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glext.h>

#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/transform2.hpp>
#include<glm/gtx/euler_angles.hpp>

#include <stdlib.h>
#include <stdio.h>

#include "vertex_data.h"
#include "shader_source.h"
#include "texture2d.h"

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow* window;
GLuint vertex_shader, fragment_shader, program;
GLint mvp_location, vpos_location, vcol_location,u_diffuse_texture_location,a_uv_location;
Texture2D* texture2d= nullptr;
// 全局变量，用于存储缩放级别
float zoomLevel = 1.0f;
// 滚轮回调函数
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  // 根据滚轮的偏移量来调整缩放级别
  zoomLevel -= yoffset * 0.1f;
  // 限制缩放级别在一定范围内
  if (zoomLevel < 0.1f) zoomLevel = 0.1f;
  if (zoomLevel > 3.0f) zoomLevel = 3.0f;
}
//初始化OpenGL
void init_opengl()
{

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  // 创建一个更大的窗口
  window = glfwCreateWindow(1920, 1080, "Simple example", NULL, NULL);

  // 设置滚轮回调函数
  glfwSetScrollCallback(window, scroll_callback);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

}

//编译、链接Shader
void compile_shader()
{
    //创建顶点Shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    //指定Shader源码
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    //编译Shader
    glCompileShader(vertex_shader);

    //创建片段Shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    //指定Shader源码
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    //编译Shader
    glCompileShader(fragment_shader);

    //创建GPU程序
    program = glCreateProgram();
    //附加Shader
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    //Link
    glLinkProgram(program);
}

//创建Texture
void CreateTexture(std::string image_file_path)
{
    texture2d=Texture2D::LoadFromFile(image_file_path);
}
// 定义一个全局变量来记录当前的展示状态
int displayState = 0;
// 鼠标按钮回调函数
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
  // 检查鼠标左键是否被按下
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
  {
    // 切换展示状态
    displayState = (displayState + 1) % 2;
  }
}
GLint wrapMode = GL_REPEAT;
GLint filterMode = GL_NEAREST;

// 全局变量，用于存储暂停状态
bool isPaused = false;
// 全局变量，用于存储mip图层的使用状态
bool useMipmap = false;
// 全局变量，用于存储各向异性过滤的状态
bool useAnisotropic = false;
// 键盘按键回调函数
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  // 检查哪个键被按下
  if (action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_R:
        wrapMode = GL_REPEAT;
        break;
      case GLFW_KEY_C:
        wrapMode = GL_CLAMP_TO_EDGE;
        break;
      case GLFW_KEY_N:
        filterMode = GL_NEAREST;
        break;
      case GLFW_KEY_L:
        filterMode = GL_LINEAR;
        break;
      case GLFW_KEY_SPACE:
        isPaused = !isPaused;
        break;
      case GLFW_KEY_M:
        // 切换mip图层的使用状态
        useMipmap = !useMipmap;
        break;
      case GLFW_KEY_A:
        // 切换各向异性过滤的状态
        useAnisotropic = !useAnisotropic;
        break;
    }
  }
}

int main(void)
{

    init_opengl();

    CreateTexture("../data/images/img.png");

    compile_shader();

    mvp_location = glGetUniformLocation(program, "u_mvp");
    vpos_location = glGetAttribLocation(program, "a_pos");
    vcol_location = glGetAttribLocation(program, "a_color");
    a_uv_location = glGetAttribLocation(program, "a_uv");
    u_diffuse_texture_location= glGetUniformLocation(program, "u_diffuse_texture");
    // 设置键盘按键回调函数
      glfwSetKeyCallback(window, keyCallback);

    //glfwSetErrorCallback(error_callback);
  while (!glfwWindowShouldClose(window))
    {
      if (useMipmap) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        if (useAnisotropic) {
          GLfloat maxAnisotropy;
          glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
          glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
        }
      } else {
        // 设置纹理环绕方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

        if (useAnisotropic) {
          GLfloat maxAnisotropy;
          glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
          glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
        } else {
          // 设置纹理过滤方式
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
        }
      }
        float ratio;
        int width, height;
        glm::mat4 model,view, projection, mvp;
        view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0,0), glm::vec3(0, 1, 0));
        view = glm::scale(view, glm::vec3(zoomLevel, zoomLevel, zoomLevel));

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f/255,77.f/255,121.f/255,1.f);
        glm::mat4 trans = glm::translate(glm::vec3(0,0,0)); //不移动顶点坐标;

        static float rotate_eulerAngle=0.f;
      if (!isPaused)
        rotate_eulerAngle+=1.f;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle)); //使用欧拉角旋转;

        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)); //缩放;
        model = trans*scale*rotation;


        projection=glm::perspective(glm::radians(60.f),ratio,1.f,1000.f);

        mvp=projection*view*model;

        //指定GPU程序(就是指定顶点着色器、片段着色器)
        glUseProgram(program);
        {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);//开启背面剔除

            //启用顶点Shader属性(a_pos)，指定与顶点坐标数据进行关联
            glEnableVertexAttribArray(vpos_location);
            glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(glm::vec3), kPositions);

            //启用顶点Shader属性(a_color)，指定与顶点颜色数据进行关联
            glEnableVertexAttribArray(vcol_location);
            glVertexAttribPointer(vcol_location, 3, GL_FLOAT, false, sizeof(glm::vec4), kColors);

            //启用顶点Shader属性(a_uv)，指定与顶点UV数据进行关联
            glEnableVertexAttribArray(a_uv_location);
            glVertexAttribPointer(a_uv_location, 2, GL_FLOAT, false, sizeof(glm::vec2), kUvs);


            //上传mvp矩阵
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);

            //贴图设置
            //激活纹理单元0
            glActiveTexture(GL_TEXTURE0);
            //将加载的图片纹理句柄，绑定到纹理单元0的Texture2D上。
            glBindTexture(GL_TEXTURE_2D,texture2d->gl_texture_id_);
            //设置Shader程序从纹理单元0读取颜色数据
            glUniform1i(u_diffuse_texture_location,0);

            //void glDrawArrays(GLenum mode,GLint first,GLsizei count);
            glDrawArrays(GL_TRIANGLES, 0, 6*6);//表示从第0个顶点开始画，总共画6个面，每个面6个顶点。
        }
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}