#ifndef FILE_IO_H
#define FILE_IO_H




#include "algorithm.h"
#include "population.h"




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
 */
void generate_results_table(
        const fitness_function_s fitness_function,
        population_ref * const population );


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
 */
void generate_data_set(
        fitness_function_s * const fitness_function );


/**
 * @brief Recursive function to print tree associated with an individual's f(x).
 * 
 * @param [in] individual A pointer to \ref individual_s whose tree is printed.
 */
void print_individual_function(
        const individual_s * const individual );




#endif //FILE_IO_H
