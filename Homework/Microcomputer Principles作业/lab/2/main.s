.section .text
.globl main
main:
    pushq   %rbp
    movq    %rsp, %rbp

    movb    $0b10011000, %al
    movb    $0b01000000, %bl

    subb    %bl, %al
    subb    %bl, %al
    subb    %bl, %al
    subb    %bl, %al
    subb    %bl, %al

    xor     %eax, %eax
    leave
    ret
    