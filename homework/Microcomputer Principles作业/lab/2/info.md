 

 98 - 40

![enter description here](https://data2.liuin.cn/story-writer/2018_1_25_1516883691695.jpg)

```sh
PF（Parity Flag）：表示奇偶校验标志位。当结果中低 8 位的二进制 1 的数量为奇数时，该标志位被设置为 1；否则，被清零为 0。

ZF（Zero Flag）：表示零标志位。当结果为零时，该标志位被设置为 1；否则，被清零为 0。

IF（Interrupt Flag）：表示中断标志位。当该标志位被设置为 1 时，允许可屏蔽中断的处理；当被清零为 0 时，禁止可屏蔽中断的处理。

OF（Overflow Flag）：表示溢出标志位。当算术运算产生结果超出所能表示的范围时，该标志位被设置为 1；否则，被清零为 0。

CF（Carry Flag）：表示进位标志位。当无符号数运算产生进位时，该标志位被设置为 1；否则，被清零为 0。

SF（Sign Flag）：表示符号标志位。当结果为负数时，该标志位被设置为 1；否则，被清零为 0。
```



```sh
Breakpoint 1, main () at main.s:4
4           pushq   %rbp
(gdb) n
5           movq    %rsp, %rbp
(gdb) n
7           movb    $0b10011000, %al
(gdb) i r
rax            0x555555555119      93824992235801
rbx            0x7fffffffd9b8      140737488345528
eflags         0x246               [ PF ZF IF ]
(gdb) n
8           movb    $0b01000000, %bl
(gdb) i r
rax            0x555555555198      93824992235928
rbx            0x7fffffffd9b8      140737488345528
eflags         0x246               [ PF ZF IF ]
(gdb) n
10          subb    %bl, %al
(gdb) i r
rax            0x555555555198      93824992235928
rbx            0x7fffffffd940      140737488345408
eflags         0x246               [ PF ZF IF ]
(gdb) n
11          subb    %bl, %al
(gdb) i r
rax            0x555555555158      93824992235864
rbx            0x7fffffffd940      140737488345408
eflags         0xa02               [ IF OF ]

12          subb    %bl, %al
(gdb) i r
rax            0x555555555118      93824992235800
rbx            0x7fffffffd940      140737488345408
eflags         0x206               [ PF IF ]
(gdb) n
13          subb    %bl, %al
(gdb) i r
rax            0x5555555551d8      93824992235992
rbx            0x7fffffffd940      140737488345408
eflags         0x287               [ CF PF SF IF ]
(gdb) n
14          subb    %bl, %al
(gdb)  i r
rax            0x555555555198      93824992235928
rbx            0x7fffffffd940      140737488345408
eflags         0x282               [ SF IF ]
```

