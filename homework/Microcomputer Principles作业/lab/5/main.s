.section .text
.globl main
main:
    pushq   %rbp
    movq    %rsp, %rbp

    movq    $0x1, %r9 # 1
    movq    $0x0, %rax # 0
    movq    $0x7, %r8 # 7
    movq    $0xF, %rbx # F

    movb    $0xF, %al

shift_loop:

    movq    %rax, %r11 # r11 = rax
    addq    %r9, %r11 # r11 = r11 + 1

    salq    $0x4, %rax # rax = rax << 4
    addq    %rbx, %rax # rax = rax + rbx

    decq    %r8 # r8 = r8 - 1
    jnz     shift_loop

    xor     %eax, %eax
    leave
    ret
