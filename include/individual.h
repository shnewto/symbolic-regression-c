
#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H




#include "algorithm.h"
#include "node.h"




/**
 * @brief Individuals represent the evolved f(x) trees.
 */
typedef struct individual 
{
    //
    //
    double fitness; /*!< Fitness of the individual. */
    //
    //
    unsigned long tree_node_count; /*!< Total number of nodes in the tree. */
    //
    //
    unsigned long tree_terminal_count; /*!< Total number of terminals in the tree.
                                        * Constants and x. 
                                        */
    //
    //
    unsigned long tree_nonterminal_count; /*!< Total number of non-terminals in 
                                           * the tree. Operators. 
                                           */
    //
    //
    node_s *tree_root_node; /*!< Pointer to \ref node_s which is the root of 
                             * the f(x) tree. */
} individual_s;




/**
 * @brief Memory allocation function. Wrapper for
 * calls to calloc for now, potentially wrapper for
 * custom memory stack allocation later. 
 * 
 * @return Pointer to new \ref individual_s. 
 */
individual_s * individual_alloc( );


/**
 * @brief Generates random f(x) tree.
 * 
 * @param [out] individual Pointer to \ref individual_s which contains
 * the f(x) tree generated.
 */
void individual_spawn( 
        individual_s * const individual );

/**
 * @brief Cleans up memory associated with the \ref individual_s data.
 * 
 * @param [in] population Pointer to \ref individual_s which contains
 * the f(x) tree generated.
 */
void individual_free( 
        individual_s ** const individual );


/**
 * @brief Performs a deep copy of an f(x) tree.  
 * 
 * @param [out] in A pointer to \ref individual_s which is copied to.
 * @param [in] out A pointer to \ref individual_s which is copied.
 */
void individual_copy( 
        const individual_s * const in, 
        individual_s * const out );


/**
 * @brief Calculates the size of an individual's f(x) tree.
 * 
 * @param [in] individual A pointer to \ref individual_s whose size is calculated. 
 
 * @return The number of node in the individual's f(x) tree.  
 */
unsigned long individual_calc_size( 
        individual_s * const individual );


/**
 * @breif Each node has a \ref MUTATE_PROBABILITY chance to change node type.
 * 
 * @param [out] individual A pointer to \ref individual_s that 
 * receives the mutations. 
 */
void individual_mutate( 
        individual_s * const individual );


/**
 * 
 * @brief Calculates tree's f(x) fitness.
 * 
 * For the symbolic regression problem it has to reevaluate the expression
 * tree for each of the input points.
 * 
 * The square root of the sum of the squared errors at each of those
 * points designates fitness. Tree size accounts for a fitness penalty. 
 * 
 * @param [in] fitness_function A \ref fitness_function_s that contains 
 * data to compare fitness against. 
 * @param [out] individual A pointer to \ref individual_s whose fitness is 
 * calculated.
 */

void individual_evaluate( 
        const fitness_function_s fitness_function, 
        individual_s * const individual );


/**
 * @brief Randomly selects branches from two trees and swaps them.
 * 
 * @param [out] individual_a A pointer to \ref individual_s whose branches are
 * crossed over with individual_b.
 * @param [out] individual_b A pointer to \ref individual_s whose branches are
 * crossed over with individual_a.
 */
void individual_crossover( 
        individual_s * const individual_a, 
        individual_s * const individual_b );


/**
 * @brief Recursive function to print tree associated with an individual's f(x).
 * 
 * @param [in] individual A pointer to \ref individual_s whose tree is printed.
 * @param [in] stream File * to write operations to.
 */
void individual_print_function(
        const individual_s * const individual,
        FILE * const stream );




#endif //INDIVIDUAL_H
