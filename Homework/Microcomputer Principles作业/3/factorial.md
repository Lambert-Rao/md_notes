 

## Background

经过一段时间的研究，我发现syscall对于我还是有点难了，直接用C库printf和scanf吧。

https://evian-zhang.github.io/introduction-to-linux-x86_64-syscall/src/introduction.html

## Run

```sh
sh run.sh
```

## Basic Knowledge

传参顺序

`rdi, rsi, rdx, rcx, r8, r9`

当使用`syscall`时, 使用`%rax`传入系统调用号，使用`printf`时，把`%rax`置零表示没有浮点参数。

bwlq

![img](https://devinkin.github.io/ox-hugo/register.png)

## Code

```assembly
.section .data
format_in: .string "%ld"
format_out: .string "Result: %ld\n"

.section .text
.globl main
main:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp #int a,int res,对齐
    movq    $1, -8(%rbp) #res=1
    leaq    -16(%rbp), %rax #&a
    leaq    format_in(%rip), %rdi #scanf param
    movq    %rax, %rsi #scanf param
    xorl    %eax, %eax
    call    scanf


    movq   -16(%rbp), %r8 #a,result from scanf
    movq   -8(%rbp), %r9 #res
factorial:
    cmpq   $1, %r8
    jle    end_factorial
    imulq  %r8, %r9
    subq   $1, %r8
    jmp    factorial
end_factorial:
    movq   %r9, -8(%rbp) #res
    movq   -8(%rbp), %rax 
    leaq   format_out(%rip), %rdi #printf param
    movq   %rax, %rsi #printf param
    xorl   %eax, %eax
    call   printf

    movl   $0, %eax
    leave
    ret
```

没啥好解释的，不解释了。

## Link

https://github.com/Limpol-Rao/md_notes/tree/main/Homework/Microcomputer%20Principles%E4%BD%9C%E4%B8%9A/3
