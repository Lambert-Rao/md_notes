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

