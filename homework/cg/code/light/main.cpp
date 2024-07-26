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

// 定义一个全局变量来跟踪当前的投影模式
bool isPerspective = true;
int lightingModel = 0; // 0 for Gouraud, 1 for Phong

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
  {
    lightingModel = 1 - lightingModel; // Switch between 0 and 1
  }
}
// 鼠标按钮回调函数
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
  {
    // 当鼠标左键被按下时，切换投影模式
    isPerspective = !isPerspective;
  }
}

//初始化OpenGL
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
    window = glfwCreateWindow(960, 640, "Cude and project", NULL, NULL);
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

int main(void)
{
    init_opengl();
    glfwSetKeyCallback(window, key_callback);

    // 设置鼠标按钮回调函数
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    compile_shader();

    //获取shader属性ID
    mvp_location = glGetUniformLocation(program, "u_mvp");
    vpos_location = glGetAttribLocation(program, "a_pos");
    vcol_location = glGetAttribLocation(program, "a_color");

    // 创建一个索引缓冲对象（IBO）并将索引数组上传到GPU
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
        static float rotate_eulerAngle=0.f;
        rotate_eulerAngle+=1;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle)); //使用欧拉角旋转;
        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)); //缩放;
        model = trans*scale*rotation;

        view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0,0), glm::vec3(0, 1, 0));
        glUniform1i(glGetUniformLocation(program, "u_lightingModel"), lightingModel);
        if (isPerspective)
        {
          projection = glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f);
        }
        else
        {
          // 正投影
          float scale = 4.0f; // 调整这个值来放大或缩小视图
          projection = glm::ortho(-ratio * scale, ratio * scale, -1.f * scale, 1.f * scale, 1.f, 1000.f);
        }

        mvp=projection*view*model;

        //指定GPU程序(就是指定顶点着色器、片段着色器)
        glUseProgram(program);
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);//开启背面剔除

      //启用顶点Shader属性(a_pos)，指定与顶点坐标数据进行关联
      glEnableVertexAttribArray(vpos_location);
      glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(glm::vec3), kPositions);

      //启用顶点Shader属性(a_color)，指定与顶点颜色数据进行关联
      glEnableVertexAttribArray(vcol_location);
      glVertexAttribPointer(vcol_location, 3, GL_FLOAT, false, sizeof(glm::vec4), kColors);

      //上传mvp矩阵
      glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);

      // 在开始绘制之前，启用图元重启功能并设置图元重启索引
      glEnable(GL_PRIMITIVE_RESTART);
      glPrimitiveRestartIndex(0xFFFFFFFF);

      // 使用glDrawElements函数代替glDrawArrays函数
      glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

      glfwSwapBuffers(window);
      glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}