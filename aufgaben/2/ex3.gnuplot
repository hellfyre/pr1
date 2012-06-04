set terminal png size 1280,1024
set output './ex3.png'
set xlabel '# processes'
set ylabel 'Time [ns]'
set style data linespoints
set grid
set title 'Aufgabe 3'
plot './ex3.csv'
