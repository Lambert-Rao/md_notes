.section .text
.globl main
main:
    pushl   %ebp
    movl    %esp, %ebp

    movw    $0x2171, %ax
    add     %ah, %al
    daa
    movw    %ax, %bx

    movw    $0x1249, %ax
    add     %ah, %al
    daa
    movw    %ax, %cx

    movw    $0x6582, %ax
    add     %ah, %al
    daa
    movw    %ax, %dx

    movw    $0x3346, %ax
    sub     %ah, %al
    das
    movw    %ax, %si

    movw    $0x5874, %ax
    sub     %ah, %al
    das
    movw    %ax, %di

    movw    $0x5443, %ax
    sub     %ah, %al
    das

    movw    $0x0071, %ax
    add     $0x0021, %ax
    daa
    movw    %ax, %bx

    movw    $0x0049, %ax
    add     $0x0012, %ax
    daa
    movw    %ax, %cx

    movw    $0x0082, %ax
    add     $0x0065, %ax
    daa
    movw    %ax, %dx

    movw    $0x0046, %ax
    sub     $0x0033, %ax
    das
    movw    %ax, %si

    movw    $0x0074, %ax
    sub     $0x0058, %ax
    das
    movw    %ax, %di

    movw    $0x0043, %ax
    sub     $0x0054, %ax
    das

    xor     %eax, %eax
    leave
    ret
