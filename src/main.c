
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mtwist.h"

#include "algorithm.h"
#include "population.h"
#include "global_memory.h"
#include "file_io.h"




//
int main( )
{
    init_global_memory();

    // initialize some pseudo-random numbers
    // with time as the seed.
    init_genrand((unsigned long) time(NULL));

    // contains input and output data sets.
    fitness_function_s fitness_function;

    memset( &fitness_function,
            0,
            sizeof(fitness_function_s) );

    population_s * initial_population = NULL;

    initial_population = population_alloc();


    generate_data_set( &fitness_function );


    population_evolve(
            fitness_function,
            &initial_population );


    generate_results_table(
            fitness_function,
            &initial_population );

    print_individual_function(
            population_best_get(&initial_population) );


    population_free( &initial_population );


    release_global_memory();


    return EXIT_SUCCESS;
}
