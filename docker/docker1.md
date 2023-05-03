docker不同于虚拟机，只有一个启动入口，容器应该遵循单一原则——一个容器只部署一个应用程序

docker管理着它启动的进程：各个容器；docker利用了进程的隔离机制

![image-20230503100735669](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305031400942.png)

docker分为`server`端和`client`端，它们通过`http`api通讯，容器和镜像都在Server上，我们的docker命令比如`docker run`是client端使用http操作host端，registry就是我们的存储库，比如docker hub，每一个repository存储着软件image的不同版本。

1. 镜像(Image):Docker 镜像是用于创建 Docker 容器的模板,比如 Ubuntu 系统
2. 容器(Container):容器是独立运行的一个或一组应用,是镜像运行时的实体
3. 客户端(client):Docker 客户端通过命令行或者其他工具使用 Docker SDK(https://docs.docker.com/develop/sdk/)) 与 Docker 的守护进程通信
4. 主机(host):一个物理或者虚拟的机器用于执行 Docker 守护进程和容器
5. 注册中心(Registry):Docker 仓库用来保存镜像,可以理解为代码控制中的代码仓库。Docker Hub(https://hub.docker.com)) 提供了庞大的镜像集合供使用。''
6. Docker Machine:Docker Machine是一个简化Docker安装的命令行工具,通过一个简单的命令行即可在相应的平台上安装Docker。

### docker命令

https://docs.docker.com/reference/

参考docker1第四个文档

![image-20230503150247474](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305031503308.png)

![image-20230503150006077](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305031500123.png)

![img](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305031557483.png)

```bash
docker run -p 81:80 nginx #端口映射，-P随机分配端口
#健康检查
docker run --rm --health-cmd "curl XXX" --health-interval 2s --health-retiries 5 
docker run -d -it#有的镜像没有运行的进程，比如Ubuntu，使用it保持交互，不会退出
```

```bash
docker -f [options] #-f根据条件过滤
docker rm `docker -f stauts=exit -q` #-q只显示编号
```

