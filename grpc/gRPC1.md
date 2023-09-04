### 什么是RPC

解决分布式通信问题的，想服务端请求就像调用本地函数

需要一个服务端和一个客户端

基于`HTTP2`的流式传输

![image-20230717101845377](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202307171020534.png)

`HTTP2`也支持乱序请求

##### ![image-20230720155901282](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202307201559371.png)

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

## 异步同步

### 同步

```protobuf
rpc RouteChat(stream RouteNote) returns (stream RouteNote) {}
```
