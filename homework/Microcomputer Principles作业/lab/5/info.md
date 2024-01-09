```assem
.section .text
.globl main
main:
    pushq   %rbp
    movq    %rsp, %rbp

    movq    $0x1, %r9 # 1
    movq    $0x0, %rax # 0
    movq    $0x8, %r8 # 7
    movq    $0xF, %rbx # F

    movb    $0xF, %al

shift_loop:

    movq    %rax, %r11 # r11 = rax
    addq    %r9, %r11 # r11 = r11 + 1
    
    salq    $0x4, %rax # rax = rax << 4
    addq    %rbx, %rax # rax = rax + rbx

    decq    %r8 # r8 = r8 - 1
    jnz     shift_loop

    xor     %eax, %eax
    leave
    ret

```



```sh
Type "apropos word" to search for commands related to "word"...
Reading symbols from lab_5...
(gdb) b 17
Breakpoint 1 at 0x113e: file main.s, line 17.
(gdb) r
Starting program: /home/lambert/CLionProjects/md_notes/Homework/Microcomputer Principles作业/lab/5/lab_5 

This GDB supports auto-downloading debuginfo from the following URLs:
  <https://debuginfod.archlinux.org>
Enable debuginfod for this session? (y or [n]) 
Debuginfod has been disabled.
To make this setting permanent, add 'set debuginfod enabled off' to .gdbinit.
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/usr/lib/libthread_db.so.1".

Breakpoint 1, shift_loop () at main.s:17
17          addq    %r9, %r11 # r11 = r11 + 1
(gdb) i r
r11            0xf                 15
eflags         0x246               [ PF ZF IF ]
(gdb) n'
Unmatched single quote.
(gdb) n
19          salq    $0x4, %rax # rax = rax << 4
(gdb) i r
r11            0x10                16
eflags         0x212               [ AF IF ]
(gdb) c
Continuing.

Breakpoint 1, shift_loop () at main.s:17
17          addq    %r9, %r11 # r11 = r11 + 1
(gdb) i r
r11            0xff                255
eflags         0x202               [ IF ]
(gdb) n
19          salq    $0x4, %rax # rax = rax << 4
(gdb) i r
r11            0x100               256
eflags         0x216               [ PF AF IF ]
(gdb) i r
r11            0xfff               4095
eflags         0x206               [ PF IF ]
(gdb) n
19          salq    $0x4, %rax # rax = rax << 4
(gdb) i r
r11            0x1000              4096
eflags         0x216               [ PF AF IF ]
(gdb) c
Continuing.

Breakpoint 1, shift_loop () at main.s:17
17          addq    %r9, %r11 # r11 = r11 + 1
(gdb) i r
r11            0xffff              65535
eflags         0x206               [ PF IF ]
(gdb) n
19          salq    $0x4, %rax # rax = rax << 4
(gdb) i r
r11            0x10000             65536
eflags         0x216               [ PF AF IF ]
(gdb) c
Continuing.

Breakpoint 1, shift_loop () at main.s:17
17          addq    %r9, %r11 # r11 = r11 + 1
(gdb) c
Continuing.

Breakpoint 1, shift_loop () at main.s:17
17          addq    %r9, %r11 # r11 = r11 + 1
(gdb) c
Continuing.

Breakpoint 1, shift_loop () at main.s:17
17          addq    %r9, %r11 # r11 = r11 + 1
(gdb) c
Continuing.

Breakpoint 1, shift_loop () at main.s:17
17          addq    %r9, %r11 # r11 = r11 + 1
(gdb) i r
r11            0xffffffff          4294967295
eflags         0x202               [ IF ]
gs             0x0                 0
(gdb) i r
r11            0xffffffff          4294967295
eflags         0x202               [ IF ]
(gdb) n
19          salq    $0x4, %rax # rax = rax << 4
(gdb) i r
r11            0x100000000         4294967296
eflags         0x216               [ PF AF IF ]
```

