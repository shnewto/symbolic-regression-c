Genetic Algorithm : Symbolic Regression
=================

A configurable genetic algorithm in written in C.

Notes:

- Perfect fitness == 0.0. The higher the fitness value the less fit the individual.
- This can be a beast with the right configuration. There is a heavy penalty for
trees with more than 512 nodes. Without that penalty expect execution time to grow incredibly 
fast with large data sets, populations sizes or numbers of generations.

External Dependencies:

- Cgreen, available [here](https://github.com/cgreen-devs/cgreen).

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

1. Extend tests for more coverage. 
2. Optimize the hell out of this.
3. Convert documentation to Markdown?
4. Add some more sophistication to global memory management.
5. Tune.
6. Add command line options for a range of preset functions?
7. Add command line help string.
8. Generalize beyond symbolic regression. Next step add the ability to run the Sante Fe Trail problem as well.
