### 什么是RPC

解决分布式通信问题的，想服务端请求就像调用本地函数

需要一个服务端和一个客户端

基于`HTTP2`的流式传输

![image-20230717101845377](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202307171020534.png)

`HTTP2`也支持乱序请求(一个HTTP的升级)

每个包用一个唯一ID来解析

![image-20230911090455157](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202309110904282.png)

### 使用

```protobuf
syntax = "proto3";
package IM.Login;
// 定义服务
service ImLogin {
// 定义服务函数
rpc Regist (IMRegistReq) returns (IMRegistRes) {}
rpc Login (IMLoginReq) returns (IMLoginRes){}
}
// 注册账号
message IMRegistReq{
string user_name = 1; // 用户名
string password = 2;
 // 密码
}
message IMRegistRes{
string user_name = 1;
uint32 user_id = 2;
uint32 result_code = 3;
}
// 返回0的时候注册正常
// 登录账号
message IMLoginReq{
string user_name = 1;
string password = 2;
}
message IMLoginRes{
uint32 user_id = 1;
uint32 result_code = 2;
 // 返回0的时候正确
}
```

传入传出参数只有一个，你可以用`message`封装起来多个参数。

## 四种gRPC模式

### 一元RPC

一次请求一次相应

### 服务端流

一次请求，多次响应，持续回复

### 客户端流

多次请求，一次相应，持续请求

### 双向流

![image-20230720160128193](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202307201601275.png)

### 逻辑

`proto`文件提供给


## 代码

https://grpc.io/docs/languages/cpp/quickstart/

### 同步

```protobuf
// The greeting service definition.
service Greeter {
  // Sends a greeting
  rpc SayHello (HelloRequest) returns (HelloReply) {}
}

// The request message containing the user's name.
message HelloRequest {
  string name = 1;
}

// The response message containing the greetings
message HelloReply {
  string message = 1;
}
```

#### 流模式

流模式通过添加`stream`关键字来表示客户端或者服务器流.

```protobuf
// Interface exported by the server.
service RouteGuide {
  // A simple RPC.
  //
  // Obtains the feature at a given position.
  //
  // A feature with an empty name is returned if there's no feature at the given
  // position.
  rpc GetFeature(Point) returns (Feature) {}

  // A server-to-client streaming RPC.
  //
  // Obtains the Features available within the given Rectangle.  Results are
  // streamed rather than returned at once (e.g. in a response message with a
  // repeated field), as the rectangle may cover a large area and contain a
  // huge number of features.
  rpc ListFeatures(Rectangle) returns (stream Feature) {}

  // A client-to-server streaming RPC.
  //
  // Accepts a stream of Points on a route being traversed, returning a
  // RouteSummary when traversal is completed.
  rpc RecordRoute(stream Point) returns (RouteSummary) {}

  // A Bidirectional streaming RPC.
  //
  // Accepts a stream of RouteNotes sent while a route is being traversed,
  // while receiving other RouteNotes (e.g. from other users).
  rpc RouteChat(stream RouteNote) returns (stream RouteNote) {}
}
```

