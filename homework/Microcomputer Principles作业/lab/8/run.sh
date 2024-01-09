current_dir=$(basename "$PWD")
gcc -m32 -g -o  lab_"$current_dir" main.s && ./lab_"$current_dir"
