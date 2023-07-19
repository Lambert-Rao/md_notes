## 协议设计

序列化与反序列化（也即编码与反编码）

比如常用的`json`, 把`struct`序列化为`json`, 然后服务端反序列成`struct`

#### header + body 设计

`header`里存储`length`等信息。采用指针偏移扫描数据。判断消息起止位置。

> 这些字段组成一个class, 可以用protocol序列化

`magic_num`用来检测开始。

`length`[区分好谁的长度], `version`[版本号尽量放前边，方便解析], `appid`[不同的应用使用同一个服务器]

`check_sum`

`service_id`[login/msg], `comman_id`[login request/login response]反序列化用来区分对象的。

`seq_num`标记消息编号的，和`TCP`里的编号类似。

`reserve`保留空间，正好用于对齐。

#### 使用场景

xml: 本地，UI，游戏信息

json: http_api

protobuf: rpc, 即时通讯，游戏通讯

##  protobuf

语言中立，平台无关，可扩展

![image-20230717162616783](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202307171626079.png)

1. 编写`proto`文件，Interface Description Language

```protobuf
syntax = "proto3";
package IM.Login;//类似namespace
import "IM.BaseDefine.proto";//引入另一个文件
//lite牺牲了反射功能，提升了性能。
option optimize_for = LITE_RUNTIME;
//class
message IMLoginReq{
	//cmd id:		0x0103
	string user_name = 1;
	string password = 2;
	IM.BaseDefine.UserStatType online_status = 3;
	IM.BaseDefine.ClientType client_type = 4;
	string client_version = 5;
	string client = 6;
	string tails = 7;
}
```

2. 使用proto生成代码文件

```shell
protoc -I=/1 --cpp_out=./2
g++ -std=c++ 11 -o lib_msg lib_msg.cc msg.pb.cc -lprotobuf -
lpthread
```

客户端，服务端共用proto文件

#### 反射

lite模式只能把每个字段的`value`取出，但是无法得知编号对应的`key`.

#### 变长编码`Varints`

[具体看文档](https://github.com/Limpol-Rao/2207_docs/blob/main/3.3.3%E5%BA%94%E7%94%A8%E5%B1%82%E5%8D%8F%E8%AE%AE%E8%AE%BE%E8%AE%A1ProtoBuf/%E5%BA%94%E7%94%A8%E5%B1%82%E5%8D%8F%E8%AE%AE%E8%AE%BE%E8%AE%A1ProtoBuf-20221011v1.1.pdf)

每个byte, 用7个储存数据，1个表示是否结束。1 没结束 0 结束。

`proto`中有三种数字编码：

1. uint32 表示无符号可变长
2. int32 表示有符号可变长（常规编码）
3. sint32 表示`ZigZag`编码的有符号整数.
4. fixed32 表示固定4`bytes`编码

proto用这样一种方式来储存数据: `field_num << 3 | wire type`. filed_num就是我们赋予的数字编号, 而type就表示Varints, 固定, 还是可变类型.

而当type是可变的时候, 我们需要编码长度信息, 其他几种情况均不需要, 这就提高了传输效率. 

> 不要使用默认值！

#### 非完全自描述

protobuf无法得到字段名, 而是只能拿出一个数字编号, 这有助于压缩传输空间. 另外, 尽量把字段控制在$$0-15$$个, 避免额外的字节用来表示长度. 

#### proto的扩充

不要复用废弃的编号, 使用新的编号空间. 
