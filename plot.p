reset
set term png
set output "graph.png"
plot "results.txt" using 1 with lines title "Best" linewidth 3, "results.txt" using 2 with lines title "Actual" linewidth 3
