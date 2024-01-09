# 数据库实践报告:网络聊天室设计







































> 智能2103班 饶逸石 

























## 一、实验名称

在线聊天室的设计与实现

## 二、实验目的

1. 掌握和应用POCO库
2. 运用数据库知识构建数据模型，实现对数据的高效管理
3. 练习和提高C++网络编程能力

## 三、实验内容与步骤

### 实验内容

本项目是一个在线聊天室的设计与实现，主要包含一个在Linux服务器上运行的后端，以及在任何网络浏览器上运行的前端。

### 实验步骤

1. #### 环境配置：首先，我们需要在环境中安装POCO库，这可以通过[手动安装](https://cppsecrets.com/users/36681111069711511910546971161041031049711497575664103109971051084699111109/Ubuntu-install-poco-C00-library-Linux.php)在Linux系统中完成。

2. #### 数据库设计：我们使用MySQL作为项目的数据库。设计包含用户、聊天室和消息等表，用来储存相应的数据。具体的数据库设计内容和SQL语句可以参考项目的docs/db.sql文件。

    2.1 用户表(user): 用户表主要存储用户的基本信息，包括用户名，密码，邮箱等。

    <img src="https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202306082310806.png" alt="image-20230608231022737" style="zoom: 67%;" />

    2.2 聊天室表(chatroom): 聊天室表用来记录聊天室的相关信息，例如聊天室的名称，创建时间，创建者等。

    <img src="https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202306082310261.png" alt="image-20230608231044205" style="zoom:67%;" />

    2.3 消息表(message): 消息表用于存储用户在聊天室中发送的所有消息，包含消息内容，发送时间，发送者等。

    > 这张表会使用Redis做缓存，加速读取

    <img src="https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202306082311858.png" alt="image-20230608231123788" style="zoom:67%;" />

    2.4 关系表(user_room_relation): 关系表记录用户和聊天室的关系，一个用户可以加入多个聊天室。

    <img src="https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202306082313784.png" alt="image-20230608231322728" style="zoom:67%;" />

3. #### 后端开发：后端应用主要在server文件夹下，这包括以下几个主要组件：

    3.1 activeRecordModel：这是我们实现的Active Record设计模式，用于执行数据库操作。

    3.2 data：数据管理器类，用于处理数据。

    3.3 message：消息管理器类，用于处理消息。

    3.4 net：网络相关文件，包括主要的HTTP服务器实现。

    3.5 support：支持文件，包括错误代码和POCO头文件。

4. #### 前端开发：前端部分主要是HTML文件，这些文件位于front文件夹中。我们采用了HTML5和CSS3来设计和实现前端界面，实现了用户友好的交互体验。

5. #### 项目部署：为了运行这个项目，我们需要在环境变量中设置MySQL配置。可以参考项目的docs/env_var.md文件了解更多详细信息。

## 四、实验结果&使用过程

通过本次实验，我们成功实现了一个在线聊天室的设计与实现。用户可以创建聊天室，加入聊天室，并在聊天室中发送消息。所有的消息和聊天室信息都会被存储在MySQL数据库中。此外，我们还优化了用户体验，改进了前端设计，提高了页面的交互性。

界面设计简单清晰明了，想必不需要过多介绍。

<img src="https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202306082245680.png" alt="image-20230608224557623" style="zoom:50%;" /><img src="https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202306082246857.png" alt="image-20230608224609810" style="zoom:50%;" /><img src="https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202306082246268.png" alt="image-20230608224650223" style="zoom:50%;" /><img src="https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202306082245432.png" alt="image-20230608224517870" style="zoom:50%;" /><img src="https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202306082248564.png" alt="image-20230608224814462"  />![image-20230608224833501](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202306082257407.png)<img src="https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202306082257146.png" alt="image-20230608225750844" style="zoom:80%;" />

## 五、实践要点

在整个在线聊天室设计与实现的过程中，我运用了一系列的技术和工具，以下是其中的一些重要部分：

1. **版本管理和开源协作**：在开发过程中，我采用了Git进行版本管理，这样能够方便地进行代码的历史版本回溯，以及多人并行开发（虽然只有我一人开发）。并且，我将项目托管在了Github上，旨在推广开源精神，也为我们自己和其他开发者提供了一个代码审查和协作的平台。

2. **文档查询和API工具**：在遇到问题和技术疑难时，我们经常会查询相关的技术文档，如MDN、Cpp Referrence等。同时，我也使用了ApiFox等API工具进行API的测试，并生成API文档（虽然前后端都是我一个人）。

3. **网关、日志和配置管理**：为了保证系统的健壮性和可维护性，我们在项目中加入了网关（Nginx）进行请求的转发和负载均衡，利用Poco自带的日志库记录日志，利用配置文件以及环境变量设定参数。

4. **缓存和数据库**：在数据存储方面，我们主要使用了MySQL数据库，并用Redis进行数据缓存，提高数据的读取速度。

5. **安全机制**：我们对用户密码进行了哈希和加盐处理，防止彩虹表攻击。同时，使用JWT（Json Web Token）进行用户身份验证，确保了系统的安全性。

6. **前后端协同**：前后端通过RESTFUL API进行数据交互，前端主要负责页面的展示和交互，后端负责数据的处理和存储。同时，我们也利用了WebSocket技术，实现了实时聊天的功能。

7. **设计模式**：在代码设计上，我们运用了Facade、单例等设计模式，使得代码结构更加清晰，也提高了代码的可读性和可维护性。


通过这次项目，我们不仅掌握了各种技术的应用，也对整个网站开发的流程有了更深的理解，为今后的工作和学习奠定了坚实的基础。

## 六、开源项目README

#### Chat Room

[![license](https://img.shields.io/github/license/Lambert-Rao/chatroom?style=plastic)](LICENSE)[![code size](https://img.shields.io/github/languages/code-size/Lambert-Rao/chatroom?style=plastic)]()[![platform](https://img.shields.io/badge/server-Linux-yellow?style=plastic)](https://en.wikipedia.org/wiki/Linux)[![platform](https://img.shields.io/badge/client-WebBrowser-lightblue?style=plastic)]()

This project is a simple online chat room, built as a learning experience with the POCO library. The chat room consists of both a server, built on Linux, and a client that operates in any web browser.

#### Project Structure

The project is organized as follows:

```
.
├── docs: Documentation files including database schemas, state codes, etc.
├── front: HTML files for the client-side user interface.
├── server: Server-side application.
    ├── activeRecordModel: Implementation of the Active Record Design Pattern for database operations.
    ├── data: Manager classes for handling data.
    ├── message: Manager class for handling messages.
    ├── net: Network related files, including the main HTTP server implementation.
    └── support: Supporting files, including error codes and POCO headers.
```

#### Background

The motivation behind this project was to learn and gain hands-on experience with the POCO library, a collection of open-source C++ class libraries that simplify and accelerate the development of network-centric, portable applications in C++.

#### Installation

Firstly, you need to install POCO:

you can get some help [here](https://cppsecrets.com/users/36681111069711511910546971161041031049711497575664103109971051084699111109/Ubuntu-install-poco-C00-library-Linux.php).

Then you can build the project:

```bash
mkdir build
cd build
cmake ..
make
```

#### Usage

Set MySQL configuration in environment variables. Refer to the [env_var.md](./docs/env_var.md) file in the docs directory for more details.

#### Contributing

Issues and Pull Requests are accepted. Feel free to contribute to this project.

#### License

[MIT © LambertRao.](*./LICENSE*)

## 七、实验总结

本实验是一个完整的网络应用开发过程，涉及到前端、后端和数据库的交互。通过本次实验，不仅提高了编程技巧，还学习到了如何运用数据库知识构建数据模型，如何实现对数据的高效管理，以及C++网络编程等相关技术。我们的代码遵循了良好的编程规范，使得代码更易读、易维护。

其他未尽事项，尽在[源码](https://github.com/Lambert-Rao/chatroom)

本项目的代码已经上传到Github，并且持续更新中，我愿意接受任何形式的建议和协作，期待在开源社区中创造更多价值。

<img src="../../../Downloads/QRcode_A — a1.svg" alt="QRcode_A — a1" style="zoom:50%;" />
