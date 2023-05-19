## 排序算法的汇编表示

今天再写写陈老师作业，老师留了作业，这我很苦恼啊，因为我不懂汇编，所以只能一点点尝试了，然后问chatgpt了。

### 设备和环境信息

```shell
$ lscpu     
架构：                   x86_64
  CPU 运行模式：         32-bit, 64-bit
  Address sizes:         48 bits physical, 48 bits virtual
  字节序：               Little Endian
CPU:                     16
  在线 CPU 列表：        0-15

```

那么我知道我的cpu是x86架构了，所以我们要使用的是x86汇编

## 从最简单的开始

准备一个空文件，然后编译看看，`bubblesort.cpp`，对不起拿错了，是`bubblesort.c`。

```sh
gcc -E bublesort.c -o bublesort.E
```

```c
# 0 "bublesort.c"
# 0 "<built-in>"
# 0 "<命令行>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<命令行>" 2
# 1 "bublesort.c"
```

应该是一些无关紧要的信息

```sh
gcc -S bublesort.c
```

```assembly
	.file	"bublesort.c"
	.text
	.ident	"GCC: (GNU) 12.2.1 20230201"
	.section	.note.GNU-stack,"",@progbits
```

.file指定了源文件名称

.text表示当前代码位于代码段

.ident指定编译器信息(identity)

.section 指令用于指定代码的存放位置和属性，指定程序的栈属性？没搞懂

> ELF（Executable and Linkable Format）:linux系统下的可执行文件和可链接文件，比如.o和.so，也就是说我平时用的指令就属于ELF

为什么汇编要加`.` ？

> 点号（.）通常用于表示当前行的符号地址或者节（section）名称
>
> 此外，点号还用于指示汇编器（assembler）在汇编过程中需要执行的一些指令或者操作

什么是节？

> 一种用于组织二进制文件的基本单元，描述二进制文件中的一段连续的数据或代码
>
> - .text：代码节，用于存储程序的可执行代码。
> - .data：数据节，用于存储程序的全局变量和静态变量的初始化数据。
> - .bss：数据节，用于存储程序的未初始化全局变量和静态变量的数据。
> - .rodata：数据节，用于存储程序的只读数据，例如字符串常量、全局常量等。
> - .got：数据节，用于存储全局偏移表（Global Offset Table），用于进行动态链接时的地址重定位。
> - .plt：代码节，用于存储过程链接表（Procedure Linkage Table），用于进行动态链接时的过程调用。
>
> 与内存四区不同，节是一种用于组织二进制文件的基本单元，在链接过程中与内存的划分没有直接关系。
>
> 在程序加载和执行的过程中，操作系统会根据程序的结构和属性将不同的节加载到内存的相应区域中。

定义一个数据看看

```c
 int g;
 static float s;
```

```assembly
	.file	"bublesort.c"
	.text
	.globl	g ;这是全局标识符，表示g是global symble
	.bss	;数据节
	.align 4 ;表示g需要4bytes对齐
	.type	g, @object ;数据对象而不是代码
	.size	g, 4 ;g的大小为4
g:
	.zero	4 ;给g清零
	.local	s ;局部符号，只能local使用
	.comm	s,4,4 ;表示共享数据
	.ident	"GCC: (GNU) 12.2.1 20230201"
	.section	.note.GNU-stack,"",@progbits

```

".align 4" 和 ".size g, 4" 是两个不同的汇编指令。4字对齐和4字大小。

```c
int func(){return 7;};
double dunc(){return 3.14;}
int main(int argc, char *argv[]){return 0;}
```

```sh
gcc -S -Og  bublesort.c # 我们启用Og优化
```

```assembly
	.file	"bublesort.c"
	.text
	.globl	func
	.type	func, @function
func:
.LFB0: ;指令标记lable,Local Function Begin
	.cfi_startproc
	movl	$7, %eax
	;在 x86 架构中，%eax 寄存器通常被用作函数返回值的寄存器
	ret
	.cfi_endproc;调试信息
.LFE0:;Local Function End
	.size	func, .-func
	.globl	dunc
	.type	dunc, @function
dunc:
.LFB1:
	.cfi_startproc
	movsd	.LC0(%rip), %xmm0
	ret
	.cfi_endproc
.LFE1:
	.size	dunc, .-dunc
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	movl	$0, %eax
	ret ;返回0了
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
;.LC0是一个存储常量的标签，在这段代码中它存储了一个双精度浮点数值，可以通过 %rip 寄存器和偏移量来访问它。
	.long	1374389535
	.long	1074339512
	.ident	"GCC: (GNU) 12.2.1 20230201"
	.section	.note.GNU-stack,"",@progbits

```

> 在 x86-64 架构下，除了通用寄存器 `%rax`、`%rbx`、`%rcx`、`%rdx`、`%rsi` 和 `%rdi` 以外，还增加了 16 个向量寄存器 `%xmm0`~`%xmm15`。这些寄存器可以用来进行 SIMD（单指令多数据）计算，提高程序的并行度和效率。

我的 `main(int argc, char *argv[])`似乎被优化掉了

```sh
gcc -S -O0  bublesort.c
```

```assembly
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc; 标记函数的开始和结束位置，以便进行调试和堆栈帧的生成
	pushq	%rbp
	; %rbp表示当前函数调用栈开始的位置,也就是说把中断之前执行的位置记录了
	.cfi_def_cfa_offset 16 
	;记录栈底指针 %rbp 的位置，以便调试和堆栈帧的生成
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	;将栈顶指针保存到%rbp中，现在%rbp用来表示当前函数的信息
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp) ;记录argc
	movq	%rsi, -16(%rbp) ;记录argv
	;这是压栈
	movl	$0, %eax
	;返回值
	popq	%rbp
	;恢复原来的状态
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
```

> `pushq`将操作数压入栈顶，同时将栈指针 `%rsp` 减去 8
>
> 通常情况下，`pushq` 指令用于保存函数调用现场

然后测试下标准输入输出，换回-Og优化

```c
int main() {
    int a;
    scanf("%d", &a);
    printf("Hello%d",a);
    return 0;
}
```

```assembly
.LC0:
	.string	"%d";存储字符串
.LC1:
	.string	"Hello%d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp ;分配栈空间，用于存放变量
	movq	%fs:40, %rax ;将 fs:40 处的值保存到寄存器 rax 中
	;用来访问线程本地存储（Thread Local Storage，TLS）?我已经不懂了？
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-12(%rbp), %rax ;将变量 a 的地址保存到寄存器 rax 中
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	scanf@PLT 
	;调用 scanf 函数，读取一个整数，并将其保存到变量 a 中
	;这里 scanf 是调用的标准库，没有使用系统调用
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	;大概明白在干嘛了，不想看这东西了
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc

```

看看循环

```c
void loop()
{
    for(int i=0;i<128;++i);
}
```

```sh
gcc -S -O0  bublesort.c
```

```assembly
	.file	"bublesort.c"
	.text
	.globl	loop
	.type	loop, @function
loop:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp ;开始函数
	.cfi_def_cfa_register 6
	movl	$0, -4(%rbp) ;一个小优化，先跳到L3
	jmp	.L2
.L3:
	addl	$1, -4(%rbp) ;++i
.L2:
	cmpl	$127, -4(%rbp) ;127-i
	jle	.L3 ;if(127-i<0) jump to L3
	nop
	nop
	;，NOP（No Operation）是一种指令，它不执行任何操作，但会占用一个指令周期。
	;它通常用于调整指令的执行时间或填充指令的空隙，以便在编写程序时保持代码的结构良好或实现某些特定的延迟。
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	loop, .-loop
	.ident	"GCC: (GNU) 12.2.1 20230201"
	.section	.note.GNU-stack,"",@progbits

```

## 冒泡排序

### 裸函数

写个冒泡先

```c
void bubble_sort(int arr[], int size) {
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
```

```sh
gcc -S -Og  bublesort.c
```

```assembly
	.file	"bublesort.c"
	.text
	.globl	bubble_sort
	.type	bubble_sort, @function
bubble_sort:
.LFB0:
	.cfi_startproc
	movl	$0, %r10d ;i = 0
	jmp	.L2
.L3:
	addl	$1, %edx ;j++
.L5:
	movl	%esi, %eax ;int eax = size
	subl	%r10d, %eax ;eax -= i
	subl	$1, %eax ;eax--
	cmpl	%edx, %eax ;j <= eax
	;为啥cmp又opr1 - opr2 顺序正常的！
	jle	.L7 ;if(j <= (size -i -1)) jmp to L7
	movslq	%edx, %rax ;rax = j
	leaq	(%rdi,%rax,4), %r8 ;r8 = &arr[j]寻址(arr+j*4)
	;在C语言中，函数参数按照从右到左的顺序依次被压入栈中，因此在函数调用时，第一个参数通常被存储在寄存器%rdi中。
	;因此，在这段汇编中，第一个参数arr被存储在%rdi中，第二个参数size被存储在%esi中。
	movl	(%r8), %ecx ;ecx = arr[j]
	leaq	4(%rdi,%rax,4), %rax ;rax = &arr[j+1]
	movl	(%rax), %r9d ;r9d = arr[j+1] 解引用
	cmpl	%r9d, %ecx ;arr[j+1] - arr[j]
	jle	.L3 ;if((arr[j+1] - arr[j]) > 0)jmp 跳过交换
	movl	%r9d, (%r8) ;arr[j] = arr [j+1]
	movl	%ecx, (%rax) ;arr[j+1] = temp(ecx存着arr[j])
	jmp	.L3
.L7:
	addl	$1, %r10d ;++j
.L2:
	leal	-1(%rsi), %eax ;size - 1
	;load effective address: 计算出正确的地址,这里是算 size - 1
	cmpl	%r10d, %eax ;i< (size -1)
	jle	.L8 ;if(i< (size -1)) jump to L8
	movl	$0, %edx ;j = 0
	jmp	.L5
.L8:
	ret
	.cfi_endproc
.LFE0:
	.size	bubble_sort, .-bubble_sort
	.ident	"GCC: (GNU) 12.2.1 20230201"
	.section	.note.GNU-stack,"",@progbits

```

先分析C代码结构，两层循环之下一个`if`比较，比较条件成立有一个简单的变量交换，就是这么简单！看汇编！

这段汇编代码，先赋值`i = 0`, 然后跳到`.L2`, 这里对`i < (size - 1)`做范围判断，如果一开始就不符合条件，直接跳到`.L8`, `ret`了。(这个`.L2`只在这里用了一次，所以`.L2`里面有赋值`j = 0`。)

否则，开始/继续我们的循环，赋值`j = 0`，跳到`.L5`, L5下面判断第二层循环的条件`(j <= (size -i -1))`, 拿出我们的`arr[j]`和`arr[j+1]`，做个比较，比较完两个分支，要么回到第一层循环`.L3`，要么做一个变量交换再回`.L3`.

```c
void bubble_sort(int arr[], int size) {
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    int a;
    int arr[n];
    for(int i = 0;i < n;++i)
    {scanf("%d",&a);
    arr[i]=a;}
    bubble_sort(arr,n);
    for(int i = 0;i < n;++i)
    {printf("%d\n",arr[i]);
    }
}
```

```assembly
	.file	"bublesort.c"
	.text
	.globl	bubble_sort
	.type	bubble_sort, @function 
bubble_sort:
.LFB0:
	.cfi_startproc
	movl	$0, %r10d
	jmp	.L2
.L3:
	addl	$1, %edx
.L5:
	movl	%esi, %eax
	subl	%r10d, %eax
	subl	$1, %eax
	cmpl	%edx, %eax
	jle	.L7
	movslq	%edx, %rax
	leaq	(%rdi,%rax,4), %r8
	movl	(%r8), %ecx
	leaq	4(%rdi,%rax,4), %rax
	movl	(%rax), %r9d
	cmpl	%r9d, %ecx
	jle	.L3
	movl	%r9d, (%r8)
	movl	%ecx, (%rax)
	jmp	.L3
.L7:
	addl	$1, %r10d
.L2:
	leal	-1(%rsi), %eax
	cmpl	%r10d, %eax
	jle	.L8
	movl	$0, %edx
	jmp	.L5
.L8:
	ret
	.cfi_endproc
.LFE0:
	.size	bubble_sort, .-bubble_sort
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d"
.LC1:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$16, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-32(%rbp), %rsi
	leaq	.LC0(%rip), %rdi
	call	scanf@PLT
	movslq	-32(%rbp), %rax
	leaq	15(,%rax,4), %rax
	andq	$-16, %rax
	subq	%rax, %rsp
	movq	%rsp, %r12
	movl	$0, %ebx
	jmp	.L10
.L11:
	leaq	-28(%rbp), %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	scanf@PLT
	movslq	%ebx, %rax
	movl	-28(%rbp), %edx
	movl	%edx, (%r12,%rax,4)
	addl	$1, %ebx
.L10:
	movl	-32(%rbp), %esi
	cmpl	%ebx, %esi
	jg	.L11
	movq	%r12, %rdi
	call	bubble_sort
	movl	$0, %ebx
	jmp	.L12
.L13:
	movslq	%ebx, %rax
	movl	(%r12,%rax,4), %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, %ebx
.L12:
	cmpl	%ebx, -32(%rbp)
	jg	.L13
	movq	-24(%rbp), %rax
	subq	%fs:40, %rax
	jne	.L16
	movl	$0, %eax
	leaq	-16(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L16:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 12.2.1 20230201"
	.section	.note.GNU-stack,"",@progbits
```

先不想写了，我去学学rust，学CSAPP的时候再深入了解一下。
