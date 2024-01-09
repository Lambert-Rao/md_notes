.section .text
.globl main
main:
    pushq   %rbp
    movq    %rsp, %rbp

    movw    $0x8F1D, %ax
    shl    $0x1, %ax
    shr    $0x1, %ax

    movw    $0x8F1D, %ax
    sal     $0x5, %ax
    sar     $0x7, %ax

    xor     %eax, %eax
    leave
    ret
