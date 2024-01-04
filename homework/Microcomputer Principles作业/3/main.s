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
