set terminal png size 800,600
set output "plot.png"

set logscale x 10
set logscale y 10
set grid
set key left top

set title "Comparing Partial Sorting"
set xlabel "size"
set ylabel "runtime (ms)"

plot for [n=2:4] "results.txt" u 1:(column(n)) w lines lw 2 title columnhead(n)


