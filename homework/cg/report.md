## 绘制基本图元

> 完成点，线，多线段，循环线，三角形，三角形条带的绘制

### 原理

OpenGL (Open Graphics Library) 是一种用于渲染2D、3D图像的跨语言、跨平台的编程接口。在OpenGL中，图元是可以被OpenGL直接处理的最小的几何图形单位，包括点、线、三角形等。

以下是OpenGL绘制基本图元的一般步骤：

1. **顶点数据**：首先，需要提供顶点数据。这些数据定义了图元的形状和位置。在你的代码中，这些数据被存储在数组中，例如 `pointPosition`、`linePositions` 等。

2. **颜色数据**：除了位置信息，还可以为每个顶点指定颜色。在你的代码中，颜色数据也被存储在数组中，例如 `pointColor`、`lineColors` 等。

3. **启用和指定顶点属性**：使用 `glEnableVertexAttribArray` 和 `glVertexAttribPointer` 函数启用并指定顶点属性。这些函数将顶点数据和颜色数据关联到顶点着色器中的属性。

4. **绘制图元**：最后，使用 `glDrawArrays` 函数绘制图元。这个函数需要指定图元类型（例如 `GL_POINTS`、`GL_LINES` 等）、起始顶点的索引和顶点数。

### 代码

1. 定义形状和颜色

```cpp
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
```

2. 绘制形状

```cpp
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
      }
```

更多代码参照附录

### 结果

| point                                                        | line                                                         | polyline                                                     | loop                                                         | triangle                                                     | strips                                                       |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![image-20240623080931348](D:\Code\CG\homework\assets\image-20240623080931348.png) | ![image-20240623080937522](D:\Code\CG\homework\assets\image-20240623080937522.png) | ![image-20240623080831453](D:\Code\CG\homework\assets\image-20240623080831453.png) | ![image-20240623080916570](D:\Code\CG\homework\assets\image-20240623080916570.png) | ![image-20240623080923271](D:\Code\CG\homework\assets\image-20240623080923271.png) | ![image-20240623080900983](D:\Code\CG\homework\assets\image-20240623080900983.png) |

## 实现空间转换

### 原理

在OpenGL中，空间坐标转换通常涉及到以下几个步骤：

1. **模型变换（Model Transformation）**：这个变换通常用于将物体从其自身的坐标系（也称为物体坐标系或局部坐标系）转换到世界坐标系。这个变换可以包括平移（Translation）、旋转（Rotation）和缩放（Scale）等操作。

2. **视图变换（View Transformation）**：这个变换用于将物体从世界坐标系转换到视图坐标系（也称为摄像机坐标系）。这个变换通常由摄像机的位置、朝向和上向量决定。

3. **投影变换（Projection Transformation）**：这个变换用于将物体从视图坐标系转换到裁剪坐标系。这个变换通常由视场角（Field of View）、长宽比（Aspect Ratio）、近裁剪面（Near Clipping Plane）和远裁剪面（Far Clipping Plane）决定。

在代码中，这些变换是通过以下方式实现的：

- **模型变换**：使用 `glm::translate`、`glm::rotate` 和 `glm::scale` 函数创建变换矩阵，然后将这些矩阵相乘得到最终的模型变换矩阵。

- **视图变换**：使用 `glm::lookAt` 函数创建视图变换矩阵。

- **投影变换**：使用 `glm::perspective` 函数创建投影变换矩阵。

最后，将模型变换矩阵、视图变换矩阵和投影变换矩阵相乘，得到最终的模型-视图-投影（Model-View-Projection，MVP）矩阵。这个MVP矩阵就可以用于将物体的顶点从物体坐标系转换到裁剪坐标系。

在顶点着色器中，MVP矩阵通常用于将物体的顶点坐标从模型空间转换到裁剪空间，如下所示：

```cpp
gl_Position = u_mvp * a_pos;
```

其中，`u_mvp` 是MVP矩阵，`a_pos` 是物体的顶点坐标。

### 代码

```cpp
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
```

### 结果

| origin/translation                                           | scale                                                        | rotation                                                     | shear                                                        | flip                                                         | combine                                                      |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![image-20240623082201250](D:\Code\CG\homework\assets\image-20240623082201250.png) | ![image-20240623082215320](D:\Code\CG\homework\assets\image-20240623082215320.png) | ![image-20240623082350839](D:\Code\CG\homework\assets\image-20240623082350839.png) | ![image-20240623082415807](D:\Code\CG\homework\assets\image-20240623082415807.png) | ![image-20240623082607278](D:\Code\CG\homework\assets\image-20240623082607278.png) | ![image-20240623082632985](D:\Code\CG\homework\assets\image-20240623082632985.png) |

## 四面体绘制

### 原理

在OpenGL中，背面剪裁（Back-face Culling）和深度测试（Depth Testing）是两种常用的性能优化技术。

1. **背面剪裁**：在3D图形渲染中，有些面是用户无法看到的，例如一个立方体的背面。这些面在渲染过程中没有任何意义，但是会消耗计算资源。背面剪裁就是在渲染之前剔除这些面，以提高渲染效率。OpenGL通过检查面的法线方向和观察方向来确定是否为背面。如果两者方向相同，则认为是背面，会被剔除。在OpenGL中，可以通过以下代码开启背面剪裁：

```cpp
glEnable(GL_CULL_FACE); // 开启背面剪裁
glCullFace(GL_BACK); // 指定剔除背面
```

2. **深度测试**：在3D图形渲染中，有些物体可能会遮挡其他物体，这就涉及到物体的前后关系，或者说深度关系。深度测试就是用来确定一个像素是否被遮挡的技术。在OpenGL中，每个像素都有一个深度值，当绘制一个像素时，会将其深度值与深度缓冲区中的当前深度值进行比较，只有当新像素的深度值小于（即更靠近观察者）当前深度值时，才会更新像素颜色和深度值。在OpenGL中，可以通过以下代码开启深度测试：

```cpp
glEnable(GL_DEPTH_TEST); // 开启深度测试
```

这两种技术在实际的3D图形渲染中非常重要，可以大大提高渲染效率，提升用户体验。

### 代码

```cpp
if (state == 0) {
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
      } else if (state == 1) {
        glEnable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
      } else if (state == 2) {
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
      } else if (state == 3) {
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
      }
```

### 结果

| !GL_CULL_FACE<br />!GL_DEPTH_TEST                            | GL_CULL_FACE<br />!GL_DEPTH_TEST                             | !GL_CULL_FACE<br />GL_DEPTH_TEST                             | GL_CULL_FACE<br />GL_DEPTH_TEST                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![image-20240623083642894](D:\Code\CG\homework\assets\image-20240623083642894.png) | ![image-20240623083654244](D:\Code\CG\homework\assets\image-20240623083654244.png) | ![image-20240623083712730](D:\Code\CG\homework\assets\image-20240623083712730.png) | ![image-20240623083722832](D:\Code\CG\homework\assets\image-20240623083722832.png) |

## 立方体绘制

### 原理

图元重启（Primitive Restart）是一种在绘制图元序列时插入特殊索引来标记新图元开始的技术。这种技术主要用于优化图形渲染，特别是在绘制复杂的三维模型时。

在OpenGL中，我们通常使用索引缓冲区（Index Buffer）来定义图元的顶点顺序。例如，当绘制三角形时，我们可以使用索引缓冲区来指定每个三角形的三个顶点。然而，当我们需要绘制多个独立的三角形时，我们需要为每个三角形都提供三个索引。这就意味着，如果两个相邻的三角形共享一个边，那么这个边的两个顶点就会在索引缓冲区中被重复定义。

图元重启就是为了解决这个问题。通过在索引缓冲区中插入一个特殊的索引值，我们可以告诉OpenGL新的图元开始了。这样，我们就可以在绘制多个独立的图元时共享顶点，从而减少索引缓冲区的大小，提高渲染效率。

在OpenGL中，可以通过以下方式启用图元重启：

```cpp
glEnable(GL_PRIMITIVE_RESTART);
```

然后，可以通过以下方式设置图元重启索引：

```cpp
glPrimitiveRestartIndex(restartIndex);
```

其中，`restartIndex` 是你选择的特殊索引值。当OpenGL在索引缓冲区中遇到这个值时，它就会知道新的图元开始了。

需要注意的是，图元重启索引必须在你的索引范围内。例如，如果你的索引是`GL_UNSIGNED_BYTE`类型，那么图元重启索引就不能超过255。

### 代码

定义八个顶点和三角形元素

```cpp
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
```

绘制元素

```cpp
	  // 在开始绘制之前，启用图元重启功能并设置图元重启索引
      glEnable(GL_PRIMITIVE_RESTART);
      glPrimitiveRestartIndex(0xFFFFFFFF);

      // 使用glDrawElements函数代替glDrawArrays函数
      glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
```

控制投影

```cpp
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
```



| 透视投影                                                     | 正交投影                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![image-20240623084107995](D:\Code\CG\homework\assets\image-20240623084107995.png) | ![image-20240623084603469](D:\Code\CG\homework\assets\image-20240623084603469.png) |

## 材质

### 原理

1. **使用repeat 和clamp参数来进行多面绘制**：在OpenGL中，纹理坐标通常在[0, 1]范围内。当纹理坐标超出这个范围时，OpenGL需要知道如何处理。这就是纹理环绕方式的作用。`GL_REPEAT`和`GL_CLAMP_TO_EDGE`是两种常用的纹理环绕方式。`GL_REPEAT`表示重复纹理图像，这通常用于平铺纹理。`GL_CLAMP_TO_EDGE`表示将纹理坐标限制在[0, 1]范围内，超出范围的坐标会被设置为边缘的纹理坐标，这通常用于防止纹理边缘的重复。

2. **对比nearest 和 linear 过滤方式**：这两种都是纹理过滤方式。`GL_NEAREST`（最近邻过滤）是OpenGL默认的纹理过滤方式，它选择纹理坐标最接近的一个纹理元素，然后直接使用该纹理元素的颜色作为纹理颜色，这种方式简单快速，但可能会导致纹理放大时的马赛克效果。`GL_LINEAR`（线性过滤）则会选择纹理坐标附近的四个纹理元素，然后根据距离进行加权平均，得到纹理颜色，这种方式可以得到更平滑的纹理效果，但计算量稍大。

3. **实现 mip图层**：Mipmapping是一种纹理过滤技术，用于处理纹理在远离观察者时的显示问题。在OpenGL中，可以通过`glGenerateMipmap`函数自动生成mipmap。在纹理过滤时，OpenGL会根据纹理的显示大小选择合适的mipmap级别，这可以避免远离观察者的纹理出现混乱的视觉效果。

4. **实现各向异性过滤方式**：各向异性过滤是一种高级的纹理过滤技术，它可以在保持纹理细节的同时，减少远离观察者的纹理的混乱视觉效果。在OpenGL中，可以通过设置`GL_TEXTURE_MAX_ANISOTROPY_EXT`参数来启用各向异性过滤。

5. **对比各种过滤的组合效果**：不同的纹理过滤方式和组合会产生不同的视觉效果。例如，`GL_NEAREST`过滤方式可能会产生马赛克效果，`GL_LINEAR`过滤方式可以得到平滑的纹理效果，但可能会导致纹理模糊。mipmap可以改善远离观察者的纹理的视觉效果，但可能会导致纹理细节丢失。各向异性过滤可以在保持纹理细节的同时，减少远离观察者的纹理的混乱视觉效果，但计算量较大。在实际应用中，需要根据具体需求选择合适的纹理过滤方式和组合。

### 代码

```cpp
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
```

### 结果

| repeat                                                       | clamp                                                        |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![image-20240623084734521](D:\Code\CG\homework\assets\image-20240623084734521.png) | ![image-20240623084750611](D:\Code\CG\homework\assets\image-20240623084750611.png) |

| nearest                                                      | linear                                                       |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![image-20240623084822409](D:\Code\CG\homework\assets\image-20240623084822409.png) | ![image-20240623084834346](D:\Code\CG\homework\assets\image-20240623084834346.png) |

| mip远                                                        | mip近                                                        | 非mip远                                                      | 非mip近                                                      |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![image-20240623084940189](D:\Code\CG\homework\assets\image-20240623084940189.png) | ![image-20240623084949907](D:\Code\CG\homework\assets\image-20240623084949907.png) | ![image-20240623084928988](D:\Code\CG\homework\assets\image-20240623084928988.png) | ![image-20240623085002123](D:\Code\CG\homework\assets\image-20240623085002123.png) |

## 光照

### 原理

Phong和Gouraud都是计算机图形学中的光照模型，用于模拟光线如何与物体表面交互，从而产生逼真的视觉效果。

1. Gouraud光照模型：Gouraud模型是一种较为简单的光照模型，它在每个顶点处计算光照效果，然后在这些顶点之间进行线性插值以得到整个面的光照效果。这种方法的优点是计算速度快，但是在光照变化剧烈的情况下可能会出现不够真实的效果。在代码中，Gouraud模型的实现可以在顶点着色器中看到，当`u_lightingModel`为0时，顶点颜色就是顶点法线和光线方向的点积与顶点原始颜色的乘积。

2. Phong光照模型：Phong模型是一种更为复杂的光照模型，它在每个像素处计算光照效果，从而能够产生更为逼真的视觉效果，特别是在处理镜面反射时。但是，Phong模型的计算量比Gouraud模型大，因此需要更多的计算资源。在代码中，Phong模型的实现可以在片段着色器中看到，当`u_lightingModel`为1时，片段颜色就是顶点法线和光线方向的点积与顶点颜色的乘积。

总的来说，Gouraud和Phong模型都是用来模拟光照的，但是它们的计算精度和计算量是不同的，具体使用哪种模型取决于你的需求和资源限制。

### 代码

```cpp
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
```

### 结果

| Gouraud                                                      | Phong                                                        |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![image-20240623090328546](D:\Code\CG\homework\assets\image-20240623090328546.png) | ![image-20240623090350810](D:\Code\CG\homework\assets\image-20240623090350810.png) |

