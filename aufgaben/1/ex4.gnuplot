set terminal png size 1280,1024
set output './ex4.png'
set xlabel 'Durchlauf n'
set ylabel 'Time [ns]'
set style data linespoints
set grid
set title 'Aufgabe 4'
plot './ex4_icc.csv' title 'ICC', './ex4_gcc.csv' title 'GCC'
