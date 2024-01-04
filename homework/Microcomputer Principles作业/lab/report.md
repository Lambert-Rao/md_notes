# 计算机组成原理和汇编程序设计实验

> 不如直接点击[Github链接](https://github.com/Lambert-Rao/md_notes/tree/main/Homework/Microcomputer%20Principles%E4%BD%9C%E4%B8%9A/lab)

## 编写一个累计加法,从 1 加到 5,将结果保存至 AX 中。

```assembly
.section .text
.globl main
main:
    pushq   %rbp
    movq    %rsp, %rbp

    movw    $1, %bx
loop:

    addw    %bx, %ax
    addw    $1, %bx

    cmpw    $6, %bx
    jne     loop

    xor     %eax, %eax
    leave
    ret

```



## 编写一个累计减法,被减数是 10011000B,减数是 01000000B,连续减 5 次,观察 FLAGS 的变化

 

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



## 编写一个 16 位的乘法,被乘数是 100H,乘数是 100H,观察 Flags 的变化,编写一个 32 位的乘法,被乘数是 0F0FH,乘数是 FF00H,观察 Flags 的变化。

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



## 编写一个 16 位的除法,被除数是 100H,除数是 100H,观察 Flags 的变化,编写一个 32 位的除法,被除数是 0F0FH,除数是 00FFH,观察 Flags 的变化。

代码

```ass	
.section .text
.globl main
main:
    pushq   %rbp
    movq    %rsp, %rbp

    xor     %dx, %dx
    movw    $0x100, %ax
    movw    $0x100, %bx
    divw    %bx, %ax

    xor     %edx, %edx
    movl    $0x0F0F, %eax
    movl    $0x00FF, %ebx
    divl    %ebx, %eax


    xor     %eax, %eax
    leave
    ret

```

结果

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



## 编写一个累计加法,被加数是 0FH,加数是 01H,观察 Flags 的变化,被加数是 0FFH,加数是 01H,观察 Flags 的变化,被加数是 0FFFH,加数是 01H,观察 Flags 的变化,被加数是 FFFFH,加数是 01H,观察 Flags 的变化,被加数是 FFFFFFFFH 加数是 01H,观察 Flags 的变化。

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



## 编写一个移位运算,将 8F1DH 存至 AX,然后用指令右移 1 位然后左移 1 位,显示结果并观察 Flags 的变化。将 8F1DH 存至 AX 中,然后带 CF 位左移 5位,并右移 7 位,观察 Flags 的变化,并给出结果。

现在我们也升级了，使用gdb-tui了

![image-20230521093147767](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305210931373.png)

![image-20230521093428007](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305210934624.png)



![image-20230521093952138](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305210939681.png)

36,637 *2 = 73,274





![image-20230521094826106](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305210948635.png)

![image-20230521095056638](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305210950179.png)

![image-20230521095352917](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305210953350.png)

36,637 *32 = 1172384(11e3a0)

1,172,384/128=9159(23c7)

e3a0(1110001110100000) >>8 1111111111000111(ffc7)

## 将 71D2H 存至 AX 中,5DF1H 存至 CX 中,DST 为 AX,REG 为 AX,实现双精度右移 2 次,交换 DST 与 REG,然后左移 4 次,分别查看结果.

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

## 实现压缩 BCD 码的加减法,用压缩 BCD 码实现(21+71), (12+49), (65+82),(46-33), (74-58),,(43-54)的十进制加减法。后又用非压缩 BCD 实现上述 6 个式子。

我们使用组合BCD码, 也就是1byte表示一个两位数

https://www.osgeo.cn/post/3130g

按照16位计算之后, 使用daa来自动调整. 

64位不支持daa, 我使用32位计算

### BCD组合码计算

![image-20230523221454470](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305232214737.png)

### BCD不压缩

![image-20230523221705916](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202305232217238.png)

## 实现 KMP 算法,输入两个字符串(可以直接保存在内存中),实现快速匹配

用汇编实现KMP实在是逆天，谁能做出来实在是厉害，反正我做不出来，我们来赏析一下编译器实现的KMP吧。

```assem
	.file	"main.c"
	.text
	.globl	prefixSuffixArray
	.type	prefixSuffixArray, @function
prefixSuffixArray:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movq	%rdx, -40(%rbp)
	movl	$0, -8(%rbp)
	movq	-40(%rbp), %rax
	movl	$0, (%rax)
	movl	$1, -4(%rbp)
	jmp	.L2
.L5:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movl	-8(%rbp), %eax
	movslq	%eax, %rcx
	movq	-24(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	jne	.L3
	addl	$1, -8(%rbp)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rax, %rdx
	movl	-8(%rbp), %eax
	movl	%eax, (%rdx)
	addl	$1, -4(%rbp)
	jmp	.L2
.L3:
	cmpl	$0, -8(%rbp)
	je	.L4
	movl	-8(%rbp), %eax
	cltq
	salq	$2, %rax
	leaq	-4(%rax), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -8(%rbp)
	jmp	.L2
.L4:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, (%rax)
	addl	$1, -4(%rbp)
.L2:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L5
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	prefixSuffixArray, .-prefixSuffixArray
	.section	.rodata
.LC0:
	.string	"Found pattern at index %d\n"
	.text
	.globl	KMPAlgorithm
	.type	KMPAlgorithm, @function
KMPAlgorithm:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	movq	%rsp, %rax
	movq	%rax, %rbx
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movl	%eax, -80(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movl	%eax, -76(%rbp)
	movl	-80(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -72(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, %r14
	movl	$0, %r15d
	movslq	%eax, %rdx
	movq	%rdx, %r12
	movl	$0, %r13d
	cltq
	leaq	0(,%rax,4), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %esi
	movl	$0, %edx
	divq	%rsi
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rdx
	movl	-80(%rbp), %ecx
	movq	-112(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	prefixSuffixArray
	movl	$0, -88(%rbp)
	movl	$0, -84(%rbp)
	jmp	.L7
.L11:
	movl	-84(%rbp), %eax
	movslq	%eax, %rdx
	movq	-112(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movl	-88(%rbp), %eax
	movslq	%eax, %rcx
	movq	-104(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	jne	.L8
	addl	$1, -84(%rbp)
	addl	$1, -88(%rbp)
.L8:
	movl	-84(%rbp), %eax
	cmpl	-80(%rbp), %eax
	jne	.L9
	movl	-88(%rbp), %eax
	subl	-84(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-84(%rbp), %eax
	leal	-1(%rax), %edx
	movq	-64(%rbp), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	movl	%eax, -84(%rbp)
	jmp	.L7
.L9:
	movl	-88(%rbp), %eax
	cmpl	-76(%rbp), %eax
	jge	.L7
	movl	-84(%rbp), %eax
	movslq	%eax, %rdx
	movq	-112(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movl	-88(%rbp), %eax
	movslq	%eax, %rcx
	movq	-104(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	je	.L7
	cmpl	$0, -84(%rbp)
	je	.L10
	movl	-84(%rbp), %eax
	leal	-1(%rax), %edx
	movq	-64(%rbp), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	movl	%eax, -84(%rbp)
	jmp	.L7
.L10:
	addl	$1, -88(%rbp)
.L7:
	movl	-88(%rbp), %eax
	cmpl	-76(%rbp), %eax
	jl	.L11
	movq	%rbx, %rsp
	nop
	movq	-56(%rbp), %rax
	subq	%fs:40, %rax
	je	.L12
	call	__stack_chk_fail@PLT
.L12:
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	KMPAlgorithm, .-KMPAlgorithm
	.section	.rodata
	.align 8
.LC1:
	.string	"The pattern is found in the text at the following index : \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movabsq	$8678849290383817080, %rax
	movq	%rax, -21(%rbp)
	movabsq	$29104598811177335, %rax
	movq	%rax, -16(%rbp)
	movl	$8026488, -25(%rbp)
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-25(%rbp), %rdx
	leaq	-21(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	KMPAlgorithm
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L15
	call	__stack_chk_fail@PLT
.L15:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (GNU) 12.2.1 20230201"
	.section	.note.GNU-stack,"",@progbits

```



## 斐波纳契数列:1,1,2,3,5,8,13。通常可以使用递归函数实现,现用汇编实现该过程。

使用递归求斐波那契太愚蠢了, 不过我们来看一下调用是什么样儿吧.

直接看代码吧, 没啥好解释的.

```assem
.section .data
format_in: .string "%ld"
format_out: .string "Fibonacci number at index %ld is: %ld\n"

.section .text
.globl main
fibonacci:
        pushq   %rbp
        movq    %rsp, %rbp

        #callee saved register
        pushq   %rbx

        #allocate 24 bytes for local variables
        subq    $24, %rsp

        #存储参数index于-24 -> -16(%rbp)
        movq    %rdi, -24(%rbp)

        #index > 1
        cmpq    $1, -24(%rbp)
        jg      continue
        #将结果存入%rax for ret
        movq    -24(%rbp), %rax
        jmp     stop
continue:
        #get index to rax
        movq    -24(%rbp), %rax
        subq    $1, %rax
        movq    %rax, %rdi
        call    fibonacci
        movq    %rax, %rbx
        movq    -24(%rbp), %rax
        subq    $2, %rax
        movq    %rax, %rdi
        call    fibonacci
        addq    %rbx, %rax
stop:
        #恢复栈
        movq    -8(%rbp), %rbx
        leave
        ret

main:
        pushq   %rbp
        movq    %rsp, %rbp
        #预留16字节的栈空间
        subq    $16, %rsp

        #scanf 读取一个整数，存入-16(%rbp) [index]
        leaq    -16(%rbp), %rsi
        leaq    format_in(%rip), %rdi
        movq    $0, %rax
        call    scanf

        #将index存入%rdi
        movq    -16(%rbp), %rax
        movq    %rax, %rdi
        call    fibonacci
        #把结果存入-8(%rbp)
        movq    %rax, -8(%rbp)

        #index to rsi
        movq    -16(%rbp), %rsi
        leaq    format_out(%rip), %rdi
        #result to rdx
        movq    -8(%rbp), %rdx
        movq    $0, %rax
        call    printf

        movl    $0, %eax
        leave
        ret

```

