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
