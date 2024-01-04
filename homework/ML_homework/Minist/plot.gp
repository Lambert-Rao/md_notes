set terminal pngcairo size 1200,900 enhanced font 'Verdana,10'
set output 'results_precision.png'
set title "Training Results - Precision"
set xlabel "Epoch"
set ylabel "Score"
plot 'results.txt' using 1:2 title 'Precision' with lines

set output 'results_recall.png'
set title "Training Results - Recall"
set xlabel "Epoch"
set ylabel "Score"
plot 'results.txt' using 1:3 title 'Recall' with lines

set output 'results_f1score.png'
set title "Training Results - F1 Score"
set xlabel "Epoch"
set ylabel "Score"
plot 'results.txt' using 1:4 title 'F1 Score' with lines
