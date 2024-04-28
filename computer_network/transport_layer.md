### 多路复用/解复用

IP提供主机到主机, 传输层提供进程到进程. 

传输层服务将IP提供的数据解复用, 通过`port`识别目标`PID`. port是关键.

TCP有链接, 创建时向操作系统提供了`source IP/port`&`dest IP/port` 所以只需要向IP提供socket id就可以发送数据.

而UDP无连接, 创建socket时只设置了本地IP/port. 所以必须向IP提供目标IP/port才能发送数据.

![image-20230907093652403](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202309070936451.png)

![image-20230907094102913](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202309070941969.png) 