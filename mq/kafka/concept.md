---
title: Kafka topic 相关几个概念
type: page
---

## kafka概念

https://zhuanlan.zhihu.com/p/658751489



topic: 逻辑标签

partition：topic的物理 分区，每个topic可以分到多个partition，一对多关系。partition使得一个topic可以分散到不同broker上。partiiton还可以有冗余备份。

offset：offset是partition中每条消息的唯一标识，用于定位和记录消息在partition中的消费进度。

#### offset的作用

1. 定位消息，一条消息对应一个offset
2. 记录消费进度，消费者消费成功后提交offset

### 存储offset

##### 生产者

生产者生产一个消息后可以通过指定`partition key`或者自动分配的方式找到一个 partition 并且在发送消息成功后拿到这个消息的 offset

##### 消费者

消费者需要维护两个offset: 当前消费进度和已提交的消费进度

1. 自动提交
2. 手动提交 调用sdk 函数

offset存储位置：kafka的一个内置主题`__consumer_offsets`。每个消费者(组)共享一个topic的消费进度。

#### 重置offset

重置就是修改offset值

目的：调整消费位置，可以重新消费或者跳过某些消息

1. 手动重置：调用seek函数
2. 自动重置：消费者启动时根据`auto.offset.reset`决定从哪里开始消费。

### 消费保证

#### 顺序性

kafka保证分区顺序性，同一个分区的消息按照offset来消费，但是不保证跨partition的topic中的message的顺序。

#### 一致性

一致性是指消息的正确发送和接受，没有丢失或者重复。

1. At most once
2. At least once
3. exactly once: 适用于严格敏感的场景（金融）。

