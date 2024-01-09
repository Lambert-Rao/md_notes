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
