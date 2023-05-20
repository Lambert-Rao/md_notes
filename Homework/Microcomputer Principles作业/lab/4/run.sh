current_dir=$(basename "$PWD")
gcc -g -o lab_"$current_dir" main.s && ./lab_"$current_dir"
