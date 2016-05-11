#ifndef ALGORITHM_H
#define ALGORITHM_H




#include <math.h>




/**
 * Proof of concept function used in this algorithm.
 * Here f(x) --> x^2
 */
#define FUNCTION(value) \
( x * x )

/**
 * Maybe a more intersting function.
 * Here f(x) --> sin(x) * cos(x) * x^3
 */ 
//#define FUNCTION(value) \
//( ( sin(x) * cos(x) * x * x * x ) )


/**
 * @brief Depth to generate initial f(x) tree. 
 */
#define INITIAL_TREE_DEPTH (5)


/**
 * @brief Tree size fitness penalty. This is a pretty extreme penalty.
 */
#define TREE_SIZE_PENALTY(tree_size) \
( tree_size * 0.1 ) 


/**
 * @brief Mutate probability. N% chance to mutate node.
 */
#define MUTATE_PROBABILITY (3)


/**
 * @brief Number of rounds / contenders to pit fitnesses against each other for
 * selection process.
 */
#define TOURNEMENT_ROUNDS (3)


/**
 * @breif Number of f(x) trees in population.
 */
#define POPULATION_SIZE (50) 


/**
 * @brief Number of iterations to evolve new populations over.
 */
#define GENERATIONS (50)


/**
 * @brief Max arity of nodes in tree.
 */
#define MAX_ARITY (2)


/**
 * @brief The size at which an individual's tree becomes heavily 
 * penalized for its size.
 */
#define MAX_TREE_NODE_COUNT (512)


/**
 * Defines minimum value in the range of the fitness f(x). 
 */
#define DATA_SET_RANGE_MIN (-6)


/**
 * Defines maximum value in the range of the fitness f(x). 
 */
#define DATA_SET_RANGE_MAX (6)


/**
 * Defines step size in points between min and max in the range 
 * of the fitness f(x). 
 */
#define DATA_SET_RANGE_STEP (1)


/**
 * @brief Non-terminals are operators that require nodes
 * below them for input. The f(x) operators rather than the values.
 */
#define NUM_NON_TERMS (6)


/**
 * @brief Terminals are values the nonterminals operate on.
 * Constants and the x in f(x).
 */
#define NUM_TERMS (2)


/**
 * @breif Invalid node type.
 */
#define INVALID_NODE (0xFF)


/**
 * @brief Nonterminal operator node type. 
 * If less than. Pass up lesser of two branch values.
 */
#define MINIMUM (0)


/**
 * @brief Nonterminal operator node type. 
 * If greater than. Pass up greater of two branch values.
 */
#define MAXIMUM (1)


/**
 * @brief Nonterminal operator node type. 
 * Pass up sum of two branch values.
 */
#define ADD (2)


/**
 * @brief Nonterminal operator node type. 
 * Pass up difference of two branch values.
 */
#define SUBTRACT (3)


/**
 * @brief Nonterminal operator node type. 
 * Pass up product of two branch values.
 */
#define MULTIPLY (4)


/**
 * @brief Nonterminal operator node type. 
 * Pass up quotient of two branch values.
 */
#define DIVIDE (5)


/**
 * @brief Number of nonterminal operator node types.
 */
#define OPERATOR_COUNT (6)


/**
 * @brief Terminal node type. Constant value.
 */
#define CONSTANT (100)


/**
 * @brief Terminal node type. Input x of f(x).
 */
#define INPUTX (101)


/**
 * @brief Number of terminal node types. 
 */
#define TERMINAL_COUNT (2)


/**
 * @brief Offset of terminal node type vaules.
 * Prevents collision with non-terminal node types.
 */
#define TERMINAL_OFFSET (100)


/**
 * @brief Value maximum for constants inserted into the f(x) trees.
 */
#define CONSTANT_VALUE_LIMIT (5)


/**
 * @brief Arbitrary. Tuneable.
 */
#define MAX_DATA_POINTS (2048)


/**
 * Contains the generated input values and output f(x) values.
 */
typedef struct fitness_function
{
    //
    //
    double input[ MAX_DATA_POINTS ]; /*!< Input contains x values. */
    //
    //
    double output[ MAX_DATA_POINTS ]; /*!< Output contains f(x) values. */
    //
    //
    unsigned long data_point_count; /*!< Data points in the set. */
}fitness_function_s;


/**
 * @brief Global used to track number of nodes walked over
 * during crossover. Deep recursion makes passing around a counter messy.
 */
long int GLOBAL_STEP_COUNT;


/**
 * @brief Global used to indicate the number of nodes to walk
 * during crossover. Deep recursion makes verifying a counter value messy. 
 */
long int GLOBAL_LAST_STEP;




#endif //ALGORITHM_H
