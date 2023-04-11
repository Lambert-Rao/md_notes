 

# MySQL缓存策略

[toc]

用Redis给mysql做缓存

## 缓存方案干什么

缓存用户的热点数据，用户直接从缓存获取热点数据（读），降低数据库压力

### 场景分析

1. 内存访问速度快

2. 大多数需求是读而非写

3. mysql自身缓存层和业务无关

   MySQL缓存的是自认为的最近热点数据，我们用Redis自定义热点数据

4. mysql作为主要数据库，便于分析统计

   mysql数据安全性要高于Redis

5. 缓存数据库Redis作为辅助数据库，存放==热点数据==，不会因为宕机而影响主Server与MySQL通信

## 有哪些方式提升MySQL访问应纳性能

### 读写分离 （最终一致性）

设置多个从数据库，从数据库放在多个机器中

写操作只在主数据库

![image-20230317155814013](https://raw.githubusercontent.com/Lambert-Rao/image_host/main/img/202303171559434.png)

从数据库解决读压力

#### 原理

![image-20230317160108717](https://raw.githubusercontent.com/Lambert-Rao/image_host/main/img/202303171601829.png)

write:增删改修改数据后，会把数据变更写入二进制日志，binary log和redo log 一起写的，binary log 用来做主从复制和数据备份

redo log：事务持久化，确保本地数据一致

binary log：确保主从数据一致

二阶段提交：分布式事务

从服务器用IO/thread拉取日志，放入relay log，此时IOthread会告诉主数据库我搞好了，主数据库就返回了，然后 SQL Thread异步地刷入数据库，这可能造出主从数据不一致。主从最终是一致的，而不能保证实时一致性，对实时数据要求强一致，请读取主数据库。

### 连接池

服务器端有多个线程连接数据库

同步阻塞io效率低，创建多个连接，并发提升数据库访问性能

复用连接。避免建立和断开，以及安全验证的开销

#### 原理

mysql网络模型：mysql会执行多线程的命令

==注：==如果是一个**事务**，必须要把它在一个线程里执行

### 异步连接
