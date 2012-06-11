set terminal png size 1280,1024
set output './10p7.png'
set xlabel '# parallel processes'
set ylabel 'Speedup'
set style data linespoints
set grid
set title '10^7'
plot './ex1b_10p7_speedup.csv' title 'b) broadcast parallel', './ex1c_10p7_speedup.csv' title 'c) rekursive Verdopplung', './ex1d_10p7_speedup.csv' title 'd) Butterfly Schema'
