## UDP

应用: DNS  SNMP

UDP提供的功能不多, 只是增加了一些解复用. 

丢包, 乱序

流媒体, 简单事务

校验失败就丢掉报文

无流量控制, 拥塞控制![image-20230907094102913](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202309070941969.png)

校验和不是`100%`准确的, 检验和与数据都出错, 但是校验成功, 这种错误叫残存错误.

#### 检验和

将待校验部分切成16bit, 相加. 同时应用如下规则:

进位回滚: 进`1`之后, 将结果取首位之后的, 再$+1$, 获取新的和. 然后, 校验和取结果的反码, 接收端检验时, 将结果和校验和相加, 如果结果为全`F`, 校验通过.
![image-20230907110304715](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202309071103901.png)