set terminal png size 1280,1024
set output './ex3_d_flops.png'
set xlabel 'Durchläufe'
set ylabel 'GFlops'
#set yrange [-1:3500000]
set grid
set title 'Aufgabe 3 d)'
plot './ex3_d_flops_only.csv'
