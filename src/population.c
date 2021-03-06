
#include <stdlib.h>     /* srand, rand, calloc, exit, free */
#include <stdio.h>
#include <string.h>

#include "population.h"
#include "global_memory.h"




//
population_s * population_alloc( void )
{
    unsigned long idx;
    unsigned int break_flag = 0;

    for( idx = 0; idx < GLOBAL_POPULATION_MEMORY_TABLE_SIZE; ++idx )
    {
        if( GLOBAL_POPULATION_MEMORY_TABLE[idx] == NULL )
        {
             GLOBAL_POPULATION_MEMORY_TABLE[idx] =
                     (population_s*)calloc( 1, sizeof(population_s) );

            if( GLOBAL_POPULATION_MEMORY_TABLE[idx] == NULL )
            {
                fprintf( stderr, "calloc failed in population_alloc\n");
                exit( EXIT_FAILURE );
            }

            GLOBAL_POPULATION_MEMORY_TABLE[idx]->memory_index = idx;
            break_flag = 1;
            break;
        }
    }

    // something went wrong and we
    // ran out of space, no room to alloc a new population.
    if( break_flag == 0 )
    {
        graceful_exit( EXIT_FAILURE );
    }


    return GLOBAL_POPULATION_MEMORY_TABLE[idx];
}


//
void population_evolve(
        const fitness_function_s fitness_function,
        population_ref * const population )
{
    if( population == NULL )
    {
        fprintf( stderr, "bad parameter in population_evolve\n");
        graceful_exit( EXIT_FAILURE );
    }

    population_spawn( population );

    printf( "\nInitial:" );
    printf( "\n--------------------" );

    population_print_evaluation( fitness_function, population );

    for( unsigned long idx = 0; idx < GENERATIONS; ++idx )
    {
        population_calc_all( fitness_function, population );

        population_new_generation( fitness_function, population );
    }

    printf( "\nFinal:" );
    printf( "\n--------------------" );

    population_print_evaluation( fitness_function, population );

    printf( "\n" );

}


//
void population_spawn(
        population_ref * const population )
{
    if( *population == NULL )
    {
        fprintf( stderr, "bad parameter in population_spawn\n");
        graceful_exit( EXIT_FAILURE );
    }

    for( unsigned long idx = 0; idx < POPULATION_SIZE; ++idx )
    {
        (*population)->individuals[ idx ] = individual_alloc();
        individual_spawn(
                (*population)->individuals[ idx ] );
    }
}


//
void population_free(
        population_ref * const population )
{
    if( (*population) == NULL )
    {
        return;
    }

    unsigned long memory_index = (*population)->memory_index;


    for( unsigned long idx = 0; idx < POPULATION_SIZE; ++idx )
    {
        individual_free(
                &GLOBAL_POPULATION_MEMORY_TABLE[ memory_index ]->individuals[ idx ] );
    }

    free( GLOBAL_POPULATION_MEMORY_TABLE[ memory_index ] );

    GLOBAL_POPULATION_MEMORY_TABLE[ memory_index ] = NULL;
    (*population) = NULL;
}


//
individual_s * population_tournament(
        individual_s * const contenders[TOURNEMENT_ROUNDS] )
{
    if( contenders == NULL )
    {
        fprintf( stderr, "bad parameter in population_tournament\n");
        graceful_exit( EXIT_FAILURE );
    }

    unsigned long best_idx = 0;
    double best_fitness = contenders[ 0 ]->fitness;

    for( unsigned long idx = 1; idx < TOURNEMENT_ROUNDS; ++idx )
    {
        if( contenders[ idx ] == NULL )
        {
            fprintf( stderr, "bad contenders array in population_tournament\n");
            graceful_exit( EXIT_FAILURE );
        }

        // smallest number == best fitness
        if( best_fitness > contenders[ idx ]->fitness )
        {
            best_fitness = contenders[ idx ]->fitness;
            best_idx = idx;
        }
    }

    individual_s *winner = individual_alloc();

    individual_copy( contenders[ best_idx ], winner );


    return winner;
}


//
void population_calc_all(
        const fitness_function_s fitness_function,
        population_ref * const population )
{
    if( (*population) == NULL )
    {
        fprintf( stderr, "bad contenders array in population_calc_all\n");
        graceful_exit( EXIT_FAILURE );
    }

    for( unsigned long idx = 0; idx < POPULATION_SIZE; ++idx )
    {
        individual_evaluate( fitness_function, (*population)->individuals[ idx ] );
        individual_calc_size( (*population)->individuals[ idx ] );
    }
}


//
void population_new_generation(
        const fitness_function_s fitness_function,
        population_ref * const population )
{
    if( (*population) == NULL )
    {
        fprintf( stderr, "bad contenders array in population_new_generation\n");
        graceful_exit( EXIT_FAILURE );
    }

    population_s * new_population = NULL;

    new_population = population_alloc( );

    individual_s *contenders[ TOURNEMENT_ROUNDS ] = { NULL };

    individual_s *elite_indiviual = NULL;

    unsigned long random_index_a = 0;
    unsigned long random_index_b = 0;

    elite_indiviual = individual_alloc();

    individual_copy( population_best_get( population ), elite_indiviual );

    for( unsigned long idx = 0; idx < POPULATION_SIZE; ++idx )
    {
        for( unsigned long jdx = 0; jdx < TOURNEMENT_ROUNDS; ++jdx )
        {
            random_index_a = random_unsigned_long( POPULATION_SIZE - 1 );

            contenders[ jdx ] = (*population)->individuals[ random_index_a ];
        }

        new_population->individuals[ idx ] = population_tournament( contenders );
    }

    for( unsigned long idx = 0; idx < POPULATION_SIZE - 2; idx += 2 )
    {
        individual_crossover(
                new_population->individuals[ idx ],
                new_population->individuals[ idx + 1 ] );
    }

    for( unsigned long idx = 0; idx < POPULATION_SIZE; ++idx )
    {
        individual_mutate( new_population->individuals[ idx ] );
    }

    population_free( population );

    (*population) = population_alloc();

    for( unsigned long idx = 0; idx < POPULATION_SIZE; ++idx )
    {
        (*population)->individuals[ idx ] = individual_alloc();
        individual_copy(
                new_population->individuals[ idx ],
                (*population)->individuals[ idx ] );
    }

    /* Elitism */
    random_index_a = random_unsigned_long( POPULATION_SIZE );
    random_index_b = random_unsigned_long( POPULATION_SIZE );

    individual_free( &(*population)->individuals[ random_index_a ] );
    (*population)->individuals[ random_index_a ] = individual_alloc();

    individual_copy( elite_indiviual, (*population)->individuals[ random_index_a ] );

    individual_free( &(*population)->individuals[ random_index_b ] );
    (*population)->individuals[ random_index_b ] = individual_alloc();

    individual_copy( elite_indiviual, (*population)->individuals[ random_index_b ] );

    population_calc_all( fitness_function, population );

    individual_free( &elite_indiviual );

    population_free( &new_population );
}


//
individual_s * population_best_get(
        const population_ref * const population )
{
    if( (*population) == NULL )
    {
        fprintf( stderr, "bad contenders array in population_best_get\n");
        graceful_exit( EXIT_FAILURE );
    }

    double temp;
    double best_fitness = (*population)->individuals[ 0 ]->fitness;
    int index_of_best_fitness = 0;


    for( unsigned long idx = 0; idx < POPULATION_SIZE; ++idx )
    {
        temp = (*population)->individuals[ idx ]->fitness;

        if( temp < best_fitness )
        {
            best_fitness = temp;
            index_of_best_fitness = idx;
        }
    }


    return (*population)->individuals[ index_of_best_fitness ];
}


//
unsigned long population_avg_size_get(
        const population_ref * const population )
{
    if( (*population) == NULL )
    {
        fprintf( stderr, "bad contenders array in population_avg_size_get\n");
        graceful_exit( EXIT_FAILURE );
    }

    double sum = 0.0;


    for( unsigned long idx = 0; idx < POPULATION_SIZE; ++idx )
    {
        sum += (*population)->individuals[ idx ]->tree_node_count;
    }

    double average = ( sum / ((double)POPULATION_SIZE) );


    return (unsigned long)average;
}


//
unsigned long population_max_size_get(
        const population_ref * const population )
{
    if( (*population) == NULL )
    {
        fprintf( stderr, "bad contenders array in population_max_size_get\n");
        graceful_exit( EXIT_FAILURE );
    }

    unsigned long temp;
    unsigned long max_size = (*population)->individuals[ 0 ]->tree_node_count;


    for( unsigned long idx = 0;idx < POPULATION_SIZE;++idx )
    {
        temp = (*population)->individuals[ idx ]->tree_node_count;

        if( temp > max_size )
        {
            max_size = temp;
        }
    }


    return max_size;
}


//
unsigned long population_min_size_get(
        const population_ref * const population )
{
    if( (*population) == NULL )
    {
        fprintf( stderr, "bad contenders array in population_min_size_get\n");
        graceful_exit( EXIT_FAILURE );
    }

    unsigned long temp = 0;
    unsigned long min_size = (*population)->individuals[ 0 ]->tree_node_count;


    for( unsigned long idx = 0; idx < POPULATION_SIZE; ++idx )
    {
        temp = (*population)->individuals[ idx ]->tree_node_count;

        if( temp < min_size )
        {
            min_size = temp;
        }
    }


    return min_size;
}


//
void population_print_evaluation(
        const fitness_function_s fitness_function,
        population_ref * const population )
{
    if( (*population) == NULL )
    {
        fprintf( stderr, "bad contenders array in population_print_evaluation\n");
        graceful_exit( EXIT_FAILURE );
    }

    population_calc_all( fitness_function, population );

    individual_s *best_individual = population_best_get( population );

    population_avg_print( population );

    printf( "\nBest Individual's Fitness: %4.4f\n", best_individual->fitness );
    printf( "\nBest Individual's Size: %lu", best_individual->tree_node_count );
        printf( "\n" );
    printf( "\nAverage Size: %lu", population_avg_size_get( population ) );
    printf( "\nMax Size: %lu", population_max_size_get( population ) );
    printf( "\nMin Size: %lu", population_min_size_get( population ) );

    printf( "\n" );
}


//
void population_avg_print(
        const population_ref * const population )
{
    if( (*population) == NULL )
    {
        fprintf( stderr, "bad contenders array in population_avg_print\n");
        graceful_exit( EXIT_FAILURE );
    }

    double sum = 0.0;

    for( unsigned long idx = 0; idx < POPULATION_SIZE; ++idx )
    {
        sum += (*population)->individuals[ idx ]->fitness;
    }

    double average = sum / (double)POPULATION_SIZE;

    printf( "\nAverage Fitness: %4.4f\n", average );
}
