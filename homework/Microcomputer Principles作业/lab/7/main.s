.section .text
.globl main
main:
    pushq   %rbp
    movq    %rsp, %rbp

    movw    $0x71D2, %ax
    movw    $0x5DF1, %cx

    shrd    $2, %cx, %ax

    movw    $0x71D2, %ax
    movw    $0x5DF1, %cx

    shld    $4, %ax, %cx

    xor     %eax, %eax
    leave
    ret
