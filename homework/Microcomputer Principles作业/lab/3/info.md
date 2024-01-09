16位溢出乘法

```sh
Breakpoint 1, main () at main.s:4
4           pushq   %rbp
(gdb) n
5           movq    %rsp, %rbp
(gdb) i r
rax            0x555555555119      93824992235801
rbx            0x7fffffffd9b8      140737488345528
eflags         0x246               [ PF ZF IF ]
(gdb) n
7           movw    $0x100, %ax
(gdb) i r
rax            0x555555555119      93824992235801
rbx            0x7fffffffd9b8      140737488345528
eflags         0x246               [ PF ZF IF ]
(gdb) n
8           movw    $0x100, %bx
(gdb) i r
rax            0x555555550100      93824992215296
rbx            0x7fffffffd9b8      140737488345528
eflags         0x246               [ PF ZF IF ]
(gdb) n
9           imulw   %bx, %ax
(gdb) i r
rax            0x555555550100      93824992215296
rbx            0x7fffffff0100      140737488290048
eflags         0x246               [ PF ZF IF ]
(gdb) n
12          xor     %eax, %eax
(gdb) i r
rax            0x555555550000      93824992215040
rbx            0x7fffffff0100      140737488290048
eflags         0xa47               [ CF PF ZF IF OF ]
```

32位不溢出乘法

```sh
11          movl    $0x0F0F, %eax
(gdb) i r
rax            0x555555550000      93824992215040
rbx            0x7fffffff0100      140737488290048
eflags         0xa47               [ CF PF ZF IF OF ] //这是上面继承下来的
(gdb) n
12          movl    $0xFF00, %ebx
(gdb) i r
rax            0xf0f               3855
rbx            0x7fffffff0100      140737488290048
eflags         0xa47               [ CF PF ZF IF OF ]
(gdb) n
13          imul   %ebx, %eax
(gdb) i r
rax            0xf0f               3855
rbx            0xff00              65280
eflags         0xa47               [ CF PF ZF IF OF ]
(gdb) n
15          xor     %eax, %eax
(gdb) i r
rax            0xefff100           251654400
rbx            0xff00              65280
eflags         0x246               [ PF ZF IF ]
```

