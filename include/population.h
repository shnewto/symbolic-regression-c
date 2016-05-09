#ifndef POPULATION_H
#define POPULATION_H




#include "algorithm.h"
#include "individual.h"




/**
 * @brief Contains the tress representing
 * the evolved f(x).
 * 
 */
typedef struct population 
{
    //
    //
    individual_s *individuals[POPULATION_SIZE]; /*!< Pointers to \ref individual_s. 
                                                 * Each is a tree representing an 
                                                 * evolved f(x). 
                                                 */
    //
    //
    unsigned long memory_index; /*!< Index in GLOBAL_POPULATION_MEMORY_TABLE */
} population_s;


typedef population_s * population_ref;




/**
 * @brief Memory allocation function. Wrapper for
 * calls to calloc for now, potentially wrapper for
 * custom memory stack allocation later. 
 * 
 * @return Pointer to new \ref population_s. 
 */
population_s * population_alloc( );


/**
 * @brief Wraps the work of the algorithm. Contains convenience output.
 * 
 * @TODO Pull printf calls out into output functions. 
 * @TODO Print progress bar. 
 * 
 * @param [in] fitness_function \ref fitness_function_s struct containing 
 * the generated input values and output f(x) values.
 * @param [in] population Pointer to \ref population_s which contains
 * the f(x) trees.
 */
void population_evolve( 
        fitness_function_s fitness_function, 
        population_ref * population );


/**
 * @brief Generates random population of f(x) trees.
 * 
 * @param [out] population Pointer to \ref population_s which contains
 * the f(x) trees generated.
 */
void population_spawn( 
        population_ref * population );


/**
 * @brief Cleans up memory associated with the \ref population_s data.
 * 
 * @param [in] population Pointer to \ref population_s which contains
 * the f(x) trees generated.
 */
void population_free(
        population_ref * population );

/**
 * @brief Calculates fitness, number of terminal nodes, 
 * non-terminal nodes and total nodes in tree.
 * 
 * @param [in] fitness_function \ref fitness_function_s struct containing 
 * the generated input values and output f(x) values.
 * @param [out] population Pointer to \ref population_s which contains
 * the f(x) trees that fitness and size are calculated for.
 */
void population_calc_all( 
        fitness_function_s fitness_function, 
        population_ref * population );


/**
 * @brief Tournament where fitnesses of the \ref individual_s trees are
 * compared and the best of the group is returned.
 * 
 * @param [in] contenders Array of pointers to \ref individual_s that 
 * undergo tournament selection. Pointer to \ref individual_s with best 
 * fitness is returned.
 * 
 * @return Pointer to \ref individual_s that represents the best fitness
 * of all the contenders. 
 */
individual_s * population_tournament( 
        individual_s * contenders[ TOURNEMENT_ROUNDS ] );


/**
 * @brief Generates a new generation. Population undergoes
 * selection, crossover and mutation. New generation takes 
 * place of previous population and previous population is cleaned up.
 * 
 * @param [in] fitness_function \ref fitness_function_s struct containing 
 * the generated input values and output f(x) values.
 * @param [out] population Pointer to \ref population_s which contains
 * the f(x) trees that undergo the transition to a new generation.
 */
void population_new_generation( 
        fitness_function_s fitness_function,    
        population_ref * population );


/**
 * @brief Calculates the average number of nodes in the population's f(x)
 * trees.
 * 
 * @param [in] population Pointer to \ref population_s which contains
 * the f(x) trees calculated.
 * 
 * @return unsigned long value representing average number of nodes in the population's
 * f(x) trees.
 */
unsigned long population_avg_size_get(
        population_ref * population );


/**
 * @brief Calculates the maximum number of nodes in the population's f(x)
 * trees.
 * 
 * @param [in] population Pointer to \ref population_s which contains
 * the f(x) trees calculated.
 * 
 * @return unsigned long value representing maximum number of nodes in the population's
 * f(x) trees.
 */
unsigned long population_max_size_get(
        population_ref * population );


/**
 * @brief Calculates the minimum number of nodes in the population's f(x)
 * trees.
 * 
 * @param [in] population Pointer to \ref population_s which contains
 * the f(x) trees calculated.
 * 
 * @return unsigned long value representing minimum number of nodes in the population's
 * f(x) trees.
 */
unsigned long population_min_size_get( 
        population_ref * population );


/**
 * @brief Returns f(x) tree with best fitness in population.
 * 
 * @param [in] population Pointer to \ref population_s which contains
 * the f(x) trees calculated.
 * 
 * @return Pointer to \ref individual_s that represents the soultion tree with 
 * the population's best fitness. 
 */
individual_s * population_best_get(
        population_ref * population );


/**
 * @brief Prints a formatted evaluation of the populations f(x)
 * for the input data set.
 * 
 * @param [in] fitness_function \ref fitness_function_s struct containing 
 * the generated input values and output f(x) values.
 * @param [out] population Pointer to \ref population_s which contains
 * the f(x) trees that fitness and size are calculated for.
 */
void population_print_evaluation(
        fitness_function_s fitness_function, 
        population_ref * population );

/**
 * @brief Prints a formatted evaluation of the population's average 
 * fitness.
 * 
 * @param [out] population Pointer to \ref population_s which contains
 * the f(x) trees that fitness and size are calculated for.
 */
void population_avg_print(
        population_ref * population );




#endif // POPULATION_H
