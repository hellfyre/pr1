set terminal png size 1280,1024
set output './ex2_a.png'
set xlabel 'Packet size [kB]'
set ylabel 'Time [ns]'
set style data linespoints
set grid
set title 'Aufgabe 2 a)'
plot './ex2_a_1.csv' title 'One node', './ex2_a_2.csv' title 'Two nodes'
