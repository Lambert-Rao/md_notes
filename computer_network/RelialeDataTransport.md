## 可靠数据传输

在应用层, 传输层, 数据链路层都是重要的问题.  

如何通过尽力而为提供不出错, 不乱序, 不丢失.

就算数据是单项的, `chanel`也需要是双向的, 这样才能反馈控制信息.

我们通过逐步设计来增加协议栈的可靠性.

我们用FSM(有限状态机)来描述这一过程.

> https://www.geeksforgeeks.org/reliable-data-transfer-rdt-1-0/
>
> https://www.bilibili.com/video/BV1JV411t7ow/?p=26

#### 不出错, 不丢失rdt1.0

封装和解封装, 相当于一层抽象.

![image-20230907140538143](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202309071405212.png)

#### 出错, 不丢失rdt2.0

校验和, 不出错`ACK`. 出错`NAK`.

![image-20230907140620458](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202309071406494.png)

![image-20230907140634681](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202309071406732.png)

#### ACK出错呢? rdt2.1

`package`中加入序号. 这里的序号只使用了0和1, 还不能校验分组顺序.

corrupt(ACK分组既不是ACK也不是NAK)视为和NAK一样处理.

![Reliable Data Transfer (2.1): Sender FSM](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202309071413176.png)

停止等待确认(stop and wait), 每次只有一个`package`在路上, 所以序号只有0/1足够了.

![Reliable Data Transfer (2.1) Receiver FSM](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202309071417554.png)

#### 无NAK协议 rdt2.2

给ACK编码, 也就是说:

当发送pkg1出错时, 正常应该回NAK1, 但是我们回他一个ACK0, 就表示出错了.

![image-20230907143525551](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202309071435665.png)

#### 超时重传 rdt3.0

超时时间如何确定? 不同层级不同方法确定.

定好时间, 防止效率下降.

但是信道容量大(通信距离远)时, `stop and wait`信道利用率太低.

### `pipeline`协议

slidwindow
