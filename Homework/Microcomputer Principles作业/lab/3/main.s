.section .text
.globl main
main:
    pushq   %rbp
    movq    %rsp, %rbp

    movw    $0x100, %ax
    movw    $0x100, %bx
    imulw   %bx, %ax

    movl    $0x0F0F, %eax
    movl    $0xFF00, %ebx
    imul   %ebx, %eax

    xor     %eax, %eax
    leave
    ret
