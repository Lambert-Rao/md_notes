 

# Clion内置插件VCPkg使用方法。

clion已经内置了vcpkg插件，个人觉得很好用，但使用过程中遇到了许多问题，于是准备写一篇文章分享使用方法。

> 本文参考、翻译了这篇文章的内容：https://blog.jetbrains.com/clion/2023/01/support-for-vcpkg-in-clion/

我的开发环境是manjaro linux，本文可能不适用于windows使用环境！！

## 安装vcpkg

如果你还没有在电脑上安装过 vcpkg，CLion 可以帮助你安装。

> 我建议你使用英文clion IDE，因为我在使用中文插件的适合，vcpkg插件出现了问题。

> 我强烈建议你使用clion自动安装，因为我自行使用包管理安装vcpkg之后，clion会因为没有权限导致无法使用vcpkg。

 首先，转到 *View | Tool Windows* 并打开 *Vcpkg*：

![image-20230501175746208](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305011757310.png)

这里的vcpkg是clion的自带插件，如果你没有安装，可以在clion插件中安装。打开之后是这样的界面：

![Vcpkg tool window](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305011752447.png)

单击 + 图标，然后指定 vcpkg 存储库的名称和 URL，以及安装目录：

> 这里我建议不要修改默认安装目录。

![image-20230501175925966](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305011759050.png)
最后点击确定，等待仓库克隆完成。 这可能需要一些时间（可能需要很长时间，耐心等待，最后去打一把游戏)。 如果你已经安装了 vcpkg，只需在 *Installation directory* 字段中指定它所在的目录。 CLion 将在其中查找 *vcpkg* 文件夹。==不建议自己安装vcpkg。==

## 浏览和安装packages

安装成功后，可以浏览软件包列表，查看软件包详细信息，然后安装您需要的软件包。 让我们找到 Google Test 包并安装它，这样我们就可以在我们的项目中使用它了：

![Search for Google Test](https://blog.jetbrains.com/wp-content/uploads/2023/01/vcpkg_search_gte.png)

包安装成功后，可以要求 CLion 将其添加到项目根目录下的 *vcpkg.json* 中，这样别人就能安装同样的包了：
![Vcpkg notifications](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305011801871.png)

或者，你可以要求 CLion 自动执行此操作：
![Auto-upload](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305011801005.png)

因为vcpkg使用源码，所以安装过程可能会很慢，别急！

要在我们的项目中使用 Google Test，我们需要更新 CMakeLists.txt 文件。 CLion 可以帮助您编写所需的 CMake 代码。 只需在包安装后使用 *Add packages to CMakeLists.txt* 操作。 复制 CLion 建议的代码，将其粘贴到 *CMakeLists.txt* 文件中，并将目标链接名称 (`main`) 更新为您希望 Google Test 链接到的名称：
![Add package to CMake code](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305011801467.png)

我在这一步里没有得到自动链接，而且有时候使用`find_package`和`target_link_libraries`会无法找到包，你可能要自己研究下了。

这样应该就能使用了。

和
