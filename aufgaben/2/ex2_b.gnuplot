set terminal png size 1280,1024
set output './ex2_b.png'
set xlabel 'Packet size [kB]'
set ylabel 'Data rate [MB/s]
set style data linespoints
set grid
set title 'Aufgabe 2 b)'
plot './ex2_b_1.csv' title 'One node', './ex2_b_2.csv' title 'Two nodes'
