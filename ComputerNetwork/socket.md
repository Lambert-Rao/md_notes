### TCP socket program

报文一层层下沉到达对面再上浮，传输层提供`socket api`.

> socket和file handle有点像, 对socket发数据/对handle写数据.

![img](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202309060852871.jpeg)

![UDPsockets](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202309070915024.jpg)

> https://www.bilibili.com/video/BV1JV411t7ow
>
> https://www.cs.dartmouth.edu/~campbell/cs60/socketprogramming.html

socket是一个`fd`

```c
struct socketaddr_in{
    sin_family //地址族tcpip
    sin_port
    sin_addr //IP address
    
}
//域名解析用的
struct hostent:  
　　h_name – 地址的正式名称。 
　　h_aliases – 空字节-地址的预备名称的指针。 
　　h_addrtype –地址类型; 通常是AF_INET。  
　　h_length – 地址的比特长度。 
　　h_addr_list – 零字节-主机网络地址指针。网络字节顺序。 
　　h_addr - h_addr_list中的第一地址。 
gethostbyname() 成 功时返回一个指向结构体 hostent 的指针，或者 是个空 (NULL) 指针。
```

> 两个进程可以守护同一个端口

### UDP socket

UDP没有握手， 每一个报文指明对方位置。不可靠，无连接，可以叫数据报。

| socket | IP   | port | PID,etc |
| ------ | ---- | ---- | ------- |
|        |      |      |         |
|        |      |      |         |
|        |      |      |         |

1. server socket(UDP) -> int
2. bind(socket,IP,port)//local
3. recvfrom(socket,from,recv) 

1. client socket(UDP)
2. bind()
3. sendto(socket,from)
