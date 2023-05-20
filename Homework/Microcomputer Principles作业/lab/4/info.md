```sh
warning: Source file is more recent than executable.
4           pushq   %rbp
(gdb) n
5           movq    %rsp, %rbp
(gdb) n
7           xor     %dx, %dx
(gdb) n
8           movw    $0x100, %ax
(gdb) n
9           movw    $0x100, %bx
(gdb) n
10          divw    %bx, %ax
(gdb) i r
rax            0x555555550100      93824992215296
rbx            0x7fffffff0100      140737488290048
eflags         0x246               [ PF ZF IF ]
(gdb) n
12          xor     %edx, %edx
(gdb) i r
rax            0x555555550001      93824992215041
rbx            0x7fffffff0100      140737488290048
eflags         0x212               [ AF IF ]
(gdb) n
13          movl    $0x0F0F, %eax
(gdb) n
14          movl    $0x00FF, %ebx
(gdb) n
15          divl    %ebx, %eax
(gdb) i r
rax            0xf0f               3855
rbx            0xff                255
eflags         0x246               [ PF ZF IF ]
(gdb) n
18          xor     %eax, %eax
(gdb) i r
rax            0xf                 15
rbx            0xff                255
eflags         0x212               [ AF IF ]
```

