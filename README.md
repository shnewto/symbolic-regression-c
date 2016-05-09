Genetic Algorithm : Symbolic Regression
=================

A configurable genetic algorithm in written in C.

Notes:

- Perfect fitness == 0.0. The higher the fitness value the less fit the individual.

Usage:

1. Build with `cmake && make`
2. Run with `./bin/symbolic-regression`
3. View best function's tree in function.txt after running.

Optional:

1. Install gnuplot and gnuplot-x11 packages.
2. Run the plot.p script with`gnuplot plot.p` in the directory where the executable was run and the file results.txt was generated.
3. View the Best Fitness and Actual function ploted in graph.png 
4. Use the -DDEBUG_ON=ON flag with cmake to enable debugging and profiling.
5. Tune parameters defined in algorithm.h and see what this thing
can do!

TODO:

1. Optimize the hell out of this.
2. Convert documentation to Markdown.
3. Write "graceful exit" function to cleanup memory before an 
exit( EXIT_FAILURE ) 
4. Tune.

Known Issues:

- With the right combination of large data sets, large populations and a lot of generations this program can "get lost" and may or may not run to completion. If you run into this let me know!
 

