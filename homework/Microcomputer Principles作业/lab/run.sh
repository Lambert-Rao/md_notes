current_dir=$(basename "$PWD")
gcc -o "lab_$current_dir" main.s && ./lab_"$current_dir"
