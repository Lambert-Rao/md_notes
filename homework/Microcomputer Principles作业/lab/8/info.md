我们使用组合BCD码, 也就是1byte表示一个两位数

https://www.osgeo.cn/post/3130g

按照16位计算之后, 使用daa来自动调整. 

64位不支持daa, 我使用32位计算

### BCD组合码计算

![image-20230523221454470](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305232214737.png)

### BCD不压缩

![image-20230523221705916](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305232217238.png)