[java-简历 (canva.cn)](https://www.canva.cn/design/DAFh3eRyrLg/QJYQH3IYRr2WNjc_OpkOcQ/edit)

面试官您好，我是饶逸石，目前在中南大学读三年级。贵公司的服务平时给我带来了许多方便，所以我也非常想要参与到淘天集团后端开发的工作中。在刚进入大学时，我就对计算机网络很感兴趣，所以我就打算在毕业后进行后端开发的工作，为此我学习了计算机的知识和开发技术，并且参与了一些后端开发的项目，希望能够加入公司进行开发工作，谢谢。



#### 项目经历

项目简介：该项目是Apaceh Eventmesh的子项目，EventMesh 是一个用于构建分布式事件驱动应用的事件中间件。Dashoboard项目提供对Eventmesh集群（Eventmesh Runtime及其存储节点，如Rocketmq）的监测和简单控制能力，以协助运维人员降低维护集群的时间成本。



主要工作：

- 参与项目并进行协调：
  - 参与项目例会，与多名开发者对接需求，制定开发任务。
  - 开源项目人员流动频繁，新同学加入时对项目了解较少，我主动带领两位新同学了解项目并安排他们开发感兴趣的任务，当有同学退出时重新分配任务，保证项目如期推进。

> 两位新同学: Lee and Chow. Lee 做了表设计和MyBatis CRUD相关代码。Chow做了一些和 Lee 相同的工作之外还做了日志ASP和配置整合模块。

> 我通过编写在线文档以及腾讯会议指导的方式，帮助新同学了解项目和项目的开发流程（关于配置项目环境、基础开发流程、提交代码流程等内容），尽量让大家都有所收获。

> 重新分配：一名同学因个人原因退出项目工作后，为了如期完成先前制定好的开发任务（两周完成数据库CRUD），我主动联系了其他的开发者，通过腾讯会议商议，将该同学原本的开发任务分配给自己和其他同学，并对该同学的任务进行讲解（因为我自己有了解过他的内容），让其他同学能够顺利接手。

- 负责健康检查模块：

  - Eventmesh集群有多种服务节点，为了监测这些节点的健康状态，设计了三种检查方式：Nacos主动汇报，网络检查（如 Redis: PING）和链路功能检查（如 Topic: 创建并删除一条该Topic的消息）。实现对各种服务节点的健康状态覆盖检查。

  > HealthService是为了实现对Eventmesh所有节点覆盖式地健康检查而设计的。我先来介绍健康检查的三种方式。Nacos对节点有心跳连接，节点下线会将消息推送到dashboard，对于没有在Nacos注册的服务（比如Store: Rocketmq）我们通过主动发送请求的方式来确保每一个节点都是健康的，精准定位问题。另外一种检查方式是链路检查，它会向整个功能链路发送一次请求，我们这里涉及的就是Topic，我们会对一个预定义的Topic发送消息并消费消息来确保Eventmesh整个链路功能没有问题。

  - 面对大量检查结果，选择通过内存缓存的方式避免频繁操作数据库，每当新一轮检查开始时才将之前的检查结果写入数据库，完成对检查结果状态的更新。

  > 插拔式的检查服务：所有的检查实现了相同的接口，这样HealthService能够做出统一的管理，使用Map来管理所有的检查实现类，也就是说可以通过添加和删除map中的数据来增加或是删除检查任务。

  > HealthService它是一个定时任务，处理过程具有周期性，每次循环是一个完整的处理过程，这个过程中涉及对缓存结果的更新和两次对数据库的修改。循环开始时将上一轮的数据（超时、成功、失败）增量更新到数据库。之后异步地发布所有检查任务。发布任务后会把新的检查结果数据插入数据库中。

  - 对于相同的节点服务端，项目多个地方可能需要创建SDK客户端，造成不必要的性能开销，设计了单例类SDKManager统一管理SDK客户端，惰性创建，按需取用，并且为其他开发者提供简单的SDK创建接口，提高团队的开发效率。

  > SDKManager是为了解决SDK客户端频繁创建和销毁而设计的。只需要创建我封装好的配置文件就可以使用SDKManager来创建和管理客户端，创建后会返回一个unique key，再次使用unique key就可以找到之前创建好的客户端。

- 负责数据同步模块：

  - Dashboard 入口点是 Web 添加集群页面，当用户接入一个集群时，程序会将集群信息写入数据库。我们的数据同步模块会通过定时任务，自动拉取已知集群对应注册中心的 Runtime 数据，并将其更新到数据库中，这样在下次定时任务时便能够通过 Runtime 地址再获取其他相关数据。
  - 为了提高性能并避免对数据库的大量操作，我们使用了历史数据的缓存。每次获取到新数据时，会先与缓存中的历史数据进行对比，只向数据库写入发生变更的部分，从而减少对数据库的 IO 开销。

  > 第一次获取集群数据后会在本地创建缓存，每次定时任务触发获取到新的数据后，会先对比本地缓存，只向数据库更新变更的数据。

  

> 你在项目中遇到的最大挑战是什么？在我刚来到项目组的时候，我不了解Eventmesh项目，并且因为性格比较内向，不太敢于和其他开发者交流。但是我明白只有沟通和交流才能解决问题，所以我积极查阅文档，向负责人学长询问项目的概念和开发问题，克服内向的性格主动承担小组负责人的任务，在自己努力和团队成员的鼓励下，最终完成自己开发任务之余还能够指导新同学参与项目。我觉得对于我来说这是比学习技术更大的收获。



> 你在这个项目中学到了什么？这个项目是我第一次参与比较有实际应用的项目，我看到了这个项目和我之前自己练习项目的不同之处（更复杂，更需要团队配合）。我学到了之前不知道的开发技术。但更重要的是学到了如何沟通，如何团队合作。在一次次讨论要不要开发某个功能的会议上，我逐渐理解项目，逐渐融入开发团队。当我看到我写的代码被别人所使用，其他同学对我的代码做出改进并添加功能，收获的喜悦是之前自己写代码时从来没有体会过的。