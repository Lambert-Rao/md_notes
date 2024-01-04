#!/bin/bash

# 主循环
for i in {1..10}
do
    # 创建目录
    mkdir $i

    # 切换到新创建的目录
    cd $i

    # 创建 main.s 文件
    touch main.s

    # 创建 run.sh 文件，并添加一些内容，这里添加的是一个执行 main.s 的 shell 脚本
    echo "current_dir=\$(basename \"\$PWD\")" > run.sh
    echo "gcc -g -o lab_\"\$current_dir\" main.s && ./lab_\"\$current_dir\"" >> run.sh

    touch info.md

    # 使 run.sh 可执行
    chmod +x run.sh

    # 切换回父目录
    cd ..
done
