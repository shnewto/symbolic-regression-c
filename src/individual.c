
#include <stdio.h>      /* printf, fopen */
#include <stdlib.h>     /* srand, rand, calloc, exit, free */

#include "algorithm.h"
#include "node.h"
#include "individual.h"
#include "global_memory.h"




//
individual_s * individual_alloc( )
{
    individual_s *individual = (individual_s*)calloc( 1, sizeof(individual_s) );

    if( individual == NULL )
    {
        fprintf( stderr, "calloc failed in individual_alloc\n");
        graceful_exit( EXIT_FAILURE );
    }

    return individual;
}


//
void individual_spawn(
        individual_s * const individual )
{
    if( individual == NULL )
    {
        fprintf( stderr, "bad parameter in individual_spawn\n");
        graceful_exit( EXIT_FAILURE );
    }

    individual->tree_root_node = node_alloc();
    individual->fitness = 0;
    individual->tree_node_count = 1;
    individual->tree_nonterminal_count = 0;
    individual->tree_terminal_count = 0;

    node_s *parent = NULL;
    unsigned long current_depth = 0;

    generate_full_tree(
            individual->tree_root_node,
            current_depth,
            parent );
}


//
void individual_free(
        individual_s ** const individual )
{
    if( *individual == NULL )
    {
        return;
    }

    node_free( &(*individual)->tree_root_node );

    free( *individual );
    *individual = NULL;
}


//
void individual_copy(
        const individual_s * const in,
        individual_s * const out )
{
    if( (in == NULL) || (out == NULL) )
    {
        fprintf( stderr, "bad param in individual_copy" );
        graceful_exit( EXIT_FAILURE );
    }

    out->tree_root_node = node_alloc();

    node_copy( in->tree_root_node, out->tree_root_node, NULL );

    out->tree_node_count = in->tree_node_count;
    out->fitness = in->fitness;
    out->tree_terminal_count = in->tree_terminal_count;
    out->tree_nonterminal_count = in->tree_nonterminal_count;
}


//
unsigned long individual_calc_size(
        individual_s * const individual )
{
    if( individual == NULL )
    {
        fprintf( stderr, "bad parameter in individual_calc_size\n");
        graceful_exit( EXIT_FAILURE );
    }

    individual->tree_node_count = 0; // at least a root node
    individual->tree_terminal_count = 0;
    individual->tree_nonterminal_count = 0;

    unsigned long terminal_nodes = 0;
    unsigned long nonterminal_nodes = 0;

    node_calc_size(
            individual->tree_root_node,
            &terminal_nodes,
            &nonterminal_nodes );

    individual->tree_node_count += terminal_nodes + nonterminal_nodes;
    individual->tree_terminal_count = terminal_nodes;
    individual->tree_nonterminal_count = nonterminal_nodes;

    return individual->tree_node_count;
}


//
void individual_mutate(
        individual_s * const individual )
{
    if( individual == NULL )
    {
        fprintf( stderr, "bad parameter in individual_mutate\n");
        graceful_exit( EXIT_FAILURE );
    }

    node_mutate( individual->tree_root_node );
}


//
void individual_evaluate(
        const fitness_function_s fitness_function,
        individual_s * const individual )
{
    if( individual == NULL )
    {
        fprintf( stderr, "bad parameter in individual_evaluate\n");
        graceful_exit( EXIT_FAILURE );
    }


    double output;


    individual->fitness = 0;

    for( unsigned long idx = 0; idx < fitness_function.data_point_count; ++idx )
    {
        // evaluate function on each input point
        output = node_evaluate(
                individual->tree_root_node,
                fitness_function.input[ idx ] );

        // outputs array holds correct values
        individual->fitness += pow( ( output - fitness_function.output[ idx ] ), 2 );
    }

    individual->fitness = sqrt( individual->fitness );
            + TREE_SIZE_PENALTY(individual->tree_node_count);

    if( individual->tree_node_count > MAX_TREE_NODE_COUNT )
    {
        individual->fitness += individual->tree_node_count;
    }
}


//
void individual_crossover(
        individual_s * const individual_a,
        individual_s * const individual_b )
{
    if( (individual_a == NULL) || (individual_b == NULL) )
    {
        fprintf( stderr, "bad parameter in individual_crossover\n" );
        graceful_exit( EXIT_FAILURE );
    }

    node_s *temp = NULL;

    temp = node_alloc();

    node_s *crossover_node_1 = NULL;
    node_s *crossover_node_2 = NULL;

    unsigned long step_range = 0;

    GLOBAL_LAST_STEP = 0;
    GLOBAL_STEP_COUNT = 0;

    step_range = individual_a->tree_terminal_count - 1;

    if( random_unsigned_long( 100 ) < 90 )
    {
        GLOBAL_LAST_STEP
                = (int)random_unsigned_long_in_range( 2, step_range );

        node_walk_nonterminals( individual_a->tree_root_node, &crossover_node_1 );
    }
    else
    {
        GLOBAL_LAST_STEP
                = (int)random_unsigned_long_in_range( 2, step_range );

        node_walk_terminals( individual_a->tree_root_node, &crossover_node_1 );
    }

    GLOBAL_STEP_COUNT = 0;

    step_range = individual_b->tree_nonterminal_count - 1;

    if( random_unsigned_long( 100 ) < 90 )
    {
        GLOBAL_LAST_STEP
                = (int)random_unsigned_long_in_range( 2, step_range );

        node_walk_nonterminals( individual_b->tree_root_node, &crossover_node_2 );
    }
    else
    {
        GLOBAL_LAST_STEP
                = (int)random_unsigned_long_in_range( 2, step_range );

        node_walk_terminals( individual_b->tree_root_node, &crossover_node_2 );
    }

    if( crossover_node_1 == NULL )
    {
        fprintf( stderr,
                "bad crossover_node_1 pointer in individual_crossover\n" );
        graceful_exit( EXIT_FAILURE );
    }

    node_copy( crossover_node_1, temp, crossover_node_1->parent );

    if( crossover_node_2 == NULL )
    {
        fprintf( stderr, "bad "
                "crossover_node_2 pointer in individual_crossover\n" );
        graceful_exit( EXIT_FAILURE );
    }

    node_copy( crossover_node_2, crossover_node_1, crossover_node_2->parent );

    node_copy( temp, crossover_node_2, temp->parent );

    crossover_node_1 = NULL;
    crossover_node_2 = NULL;

    node_free( &temp );
}
