set terminal png size 1280,1024
set output './ex3_d.png'
set xlabel 'Durchläufe'
set ylabel 'Time [ns]'
set yrange [-1:3500000]
set grid
set title 'Aufgabe 3 d)'
plot './ex3_d.csv'
