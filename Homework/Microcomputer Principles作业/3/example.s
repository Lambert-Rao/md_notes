.LC0:                     // 定义一个标签，用于存储后面的字符串常量。
    .string "%d"          // 存储一个字符串常量，用于后面的 scanf 和 printf 函数。

main:                     // 主程序开始。
    pushq   %rbp          // 保存当前的基址指针。
    movq    %rsp, %rbp    // 将当前的栈指针值移动到基址指针，为新的函数调用设置新的栈帧。
    subq    $16, %rsp     // 从栈指针中减去16，为两个局部变量（各需要8字节）分配空间。

    movl    $1, -4(%rbp)  // 初始化局部变量，这里用于计算阶乘。

    leaq    -8(%rbp), %rax  // 将局部变量的地址加载到寄存器rax中，准备为scanf函数调用。
    movq    %rax, %rsi      // 将rax的值移到rsi，用作scanf的参数。
    movl    $.LC0, %edi     // 将标签.LC0的地址移到edi，用作scanf的参数。
    movl    $0, %eax        // 清除eax，这是因为在64位调用约定中，eax用于表示浮点数参数的数量。
    call    scanf            // 调用scanf函数，读取用户的输入。

    jmp     .L2              // 跳转到.L2标签。

.L3:                        // 循环开始的标签。
    movl    -8(%rbp), %eax   // 将用户输入的数移到eax。
    movl    -4(%rbp), %edx   // 将当前阶乘的结果移到edx。
    imull   %edx, %eax       // 将这两个值相乘，并将结果存回eax。
    movl    %eax, -4(%rbp)   // 将结果存回局部变量。

    movl    -8(%rbp), %eax   // 将用户输入的数移到eax。
    subl    $1, %eax         // 从eax中减1。
    movl    %eax, -8(%rbp)   // 将结果存回局部变量。

.L2:                        // 检查循环条件的标签。
    movl    -8(%rbp), %eax   // 将用户输入的数移到eax。
    testl   %eax, %eax       // 测试eax的值，如果它是0，ZF标志就会被设置。
    jg      .L3              // 如果ZF标志未设置（即输入的数大于0），则跳转到.L3标签。

    movl    -4(%rbp), %eax   // 将阶乘的结果移到eax。
    movl    %eax, %esi       // 将eax的值移到rsi，用作printf的参数。
    movl    $.LC0, %edi      // 将标签.LC0的地址移到edi，用作printf的参数。
    movl    $0, %eax         // 清除eax，这是因为在64位调用约定中，eax用于表示浮点数参数的数量。
    call    printf           // 调用printf函数，打印阶乘的结果。

    movl    $0, %eax         // 将0移动到eax，表示函数正常结束。
    leave                    // 清除当前的栈帧，与之前的pushq %rbp和movq %rsp, %rbp对应。
    ret                      // 返回主调函数。
