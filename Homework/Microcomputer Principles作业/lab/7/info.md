![img](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305211011060.gif)

![img](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305211101938.gif)

双精度移位就是把两个数拼起来在移位, 然后存入DST寄存器![image-20230521101501550](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305211015607.png)

SHRD  count, source, dest(不知道上哪查语法捏, 自己试出来的, 不过仔细想想AT&T的语法, 都是src在前面)



![image-20230521103221750](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305211032094.png)

ax(DST) - 111000111010010

cx(SRC) - 101110111110001

![image-20230521104505632](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305211045941.png)

result - 10~1110001110100

1011101111100==01== - ==1110001110100==10



![image-20230521104655889](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305211046213.png)

ax(SRC) - 111000111010010

cx(DST) - 101110111110001

![image-20230521104740193](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305211047495.png)

cx - 110111110001~0111

0101==110111110001== - ==1110==00111010010