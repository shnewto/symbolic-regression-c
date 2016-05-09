
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "algorithm.h"
#include "population.h"
#include "global_memory.h"




/**
 * @brief Generates tab character delimited table
 * of results for use in gnuplot script.
 *
 * best_fitness_f(x)    actual_f(x)
 * ...
 *
 * @param [in] fitness_function \ref fitness_function_s struct containing
 * the generated input values and output f(x) values.
 *
 * @param [in] population \ref population_s struct containing the tress
 * representing the evolved f(x) solutions.
 * @param [in] stream File * to write results to.
 */
static void generate_results_table(
        fitness_function_s fitness_function,
        population_ref * population,
        FILE* stream );


/**
 * @brief Generates data set to evolve solutions for. Fills
 * \ref fitness_function_s struct for use in program and
 * also writes data to a tab character delimited table.
 *
 * input x value    output f(x)
 * ...
 *
 * @param [in] fitness_function A pointer to \ref fitness_function_s
 * struct to write the generated input values and output f(x) values to.
 * @param [in] stream File * to write data set to.
 */
static void generate_data_set(
        fitness_function_s * fitness_function,
        FILE * stream );




//
int main( )
{
    init_global_memory();

    // initialize some pseudo-random numbers
    // with time as the seed.
    srand((unsigned) time(NULL));

    // contains input and output data sets.
    fitness_function_s fitness_function;

    // sanity initialization.
    memset( &fitness_function, 0, sizeof(fitness_function_s) );

    // Record of the x and f(x) values.
    const char data_set_file_name[] = "regression-data-set.txt";

    FILE* data_set_stream = fopen( data_set_file_name, "w" );

    if( data_set_stream == NULL )
    {
        fprintf( stderr, "failed to open %s\n", data_set_file_name );
        graceful_exit( EXIT_FAILURE );
    }

    generate_data_set( &fitness_function, data_set_stream );

    fclose( data_set_stream );

    population_s *initial_population = NULL;

    initial_population = population_alloc();

    population_evolve( fitness_function, &initial_population );

    const char results_filename[] =
    "results.txt";

    FILE * results_stream = NULL;

    results_stream = fopen( results_filename, "w" );

    if( results_stream == NULL )
    {
        fprintf( stderr, "failed to open %s\n", results_filename );

        graceful_exit( EXIT_FAILURE );
    }

    generate_results_table(
            fitness_function,
            &initial_population,
            results_stream );

    fclose( results_stream );

    const char function_filename[] =
    "function.txt";

    FILE * function_stream = NULL;

    function_stream = fopen( function_filename, "w" );

    if( function_stream == NULL )
    {
        fprintf( stderr, "failed to open %s\n", function_filename );

        graceful_exit( EXIT_FAILURE );
    }

    individual_print_function(
            population_best_get(&initial_population),
            function_stream );

    fclose( function_stream );

    population_free( &initial_population );

    release_global_memory();

    return EXIT_SUCCESS;
}


//
static void generate_results_table(
        fitness_function_s fitness_function,
        population_ref * population,
        FILE* stream )
{
    if( ((*population) == NULL) || (stream == NULL) )
    {
        fprintf( stderr, "bad parameter in generate_results_table\n");
        graceful_exit( EXIT_FAILURE );
    }

    individual_s * individual = NULL;
    individual = population_best_get( population );

    for( unsigned long idx = 0; idx < fitness_function.data_point_count; ++idx )
    {
        // evaluate function on each input point
        fprintf(
                stream,
                "%f\t%f\n",
                node_evaluate(
                    individual->tree_root_node,
                    fitness_function.input[ idx ] ),
                fitness_function.output[ idx ] );
    }
}


//
static void generate_data_set(
        fitness_function_s * fitness_function,
        FILE* stream )
{
    if( stream == NULL )
    {
        fprintf( stderr, "bad parameter in generate_data_set\n");
        graceful_exit( EXIT_FAILURE );
    }

    double range_min = -6;
    double range_max = 6;
    double step = 1;

    unsigned long * idx = &fitness_function->data_point_count;
    (*idx) = 0;

    for( double x = DATA_SET_RANGE_MIN; x < DATA_SET_RANGE_MAX; x += DATA_SET_RANGE_STEP )
    {
        fitness_function->input[ (*idx) ] = x; // x

        fitness_function->output[ (*idx) ]
        = FUNCTION(x);

        fprintf(
                stream,
                "%.2f %.2f\n",
                fitness_function->input[ (*idx) ],
                fitness_function->output[ (*idx) ] );

        (*idx)++;

        if( (*idx) > MAX_DATA_POINTS )
        {
            fprintf( stderr, "Data point count exceeded MAX_DATA_POINTS\n" );
            graceful_exit( EXIT_FAILURE );
        }
    }
}
