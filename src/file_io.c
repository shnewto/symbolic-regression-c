

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global_memory.h"
#include "file_io.h"




//
void generate_results_table(
        const fitness_function_s fitness_function,
        population_ref * const population )
{
    if( (*population) == NULL )
    {
        fprintf( stderr, "bad parameter in generate_results_table\n");
        graceful_exit( EXIT_FAILURE );
    }

    const char file_name[] =
    "results.txt";

    FILE * stream = NULL;

    stream = fopen( file_name, "w" );

    if( stream == NULL )
    {
        fprintf( stderr, "failed to open %s\n", file_name );

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

    fclose( stream );
}


//
void generate_data_set(
        fitness_function_s * const fitness_function )
{
    // Record of the x and f(x) values.
    const char file_name[] = "regression-data-set.txt";

    FILE* stream = fopen( file_name, "w" );

    if( stream == NULL )
    {
        fprintf( stderr, "failed to open %s\n", file_name );
        graceful_exit( EXIT_FAILURE );
    }

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

    fclose( stream );
}


//
void print_individual_function(
        const individual_s * const individual )
{
    if( individual == NULL )
    {
        fprintf( stderr, "bad parameter in print_individual_function\n");
        graceful_exit( EXIT_FAILURE );
    }

    const char file_name[] =
    "function.txt";

    FILE * stream = NULL;

    stream = fopen( file_name, "w" );

    if( stream == NULL )
    {
        fprintf( stderr, "failed to open %s\n", file_name );

        graceful_exit( EXIT_FAILURE );
    }

    fprintf( stream, "f( x )\n" );

    node_print_operations(
            individual->tree_root_node,
            stream,
            1 );

    fprintf( stream, "\n" );

    fclose( stream );
}
