### Java的运行模式



java code -编译-› class类 -runtime 运行->机器码





### java字节码

编译后得到，可以由jre执行，使用JIT执行的话可以把热点代码的解释后结果缓存起来、



### PC

如果虚拟机中的当前线程执行的是 Java 的[普通方法](https://javabetter.cn/oo/method.html)，那么 PC 寄存器中存储的是方法的第一条指令，当方法开始执行之后， PC 寄存器存储的是下一个字节码指令的地址。

如果虚拟机中的当前线程执行的是 [native 方法](https://javabetter.cn/oo/native-method.html)，那么 PC 寄存器中的值为 undefined。



### 虚拟机栈

![img](./assets/how-run-java-code-20231031142106.png)