[网际协议版本4](https://zh.wikipedia.org/zh-cn/IPv4)（英语：Internet Protocol version 4，缩写：IPv4，又称互联网通信协议第四版）是网际协议开发过程中的第四个修订版本.

> 这里的v4是`version`, 笑.

一般来说常见的是`ABC`类三种地址,其区别是子网掩码分割地址的位置.子网掩码(CIDR)把IP分为网络位和主机位两个部分.
ABC是单播,D是多播.

#### 专用网络
在IPv4所允许的大约四十亿地址中，三个地址块被保留作专用网络。这些地址块在专用网络之外不可路由，专用网络之内的主机也不能直接与公共网络通信。但通过网络地址转换（NAT），使用这些地址的主机可以像拥有共有地址的主机在互联网上通信。

| 名字   | 地址范围                    | 地址数量   | 有类别的描述   | 最大的[CIDR](https://zh.wikipedia.org/wiki/CIDR)地址块 |
| ------ | --------------------------- | ---------- | -------------- | ------------------------------------------------------ |
| 24位块 | 10.0.0.0–10.255.255.255     | 16,777,216 | 一个A类        | 10.0.0.0/8                                             |
| 20位块 | 172.16.0.0–172.31.255.255   | 1,048,576  | 连续的16个B类  | 172.16.0.0/12                                          |
| 16位块 | 192.168.0.0–192.168.255.255 | 65,536     | 连续的256个C类 | 192.168.0.0/16                                         |

另外参加wiki上更多的特殊用途地址
回环地址127.0.0.0/8

### NAT
NAT下属设备之间不能互相访问

### IPv6
IPv6很简单的把128bit地址空间分成两半, 前64是网络部分,后64是接口ID.而网络部分的前48是ISP提供的,后16是子网划分,比如子公司网络.IPv6没有子网掩码,够用.