#ifndef NODE_H
#define NODE_H




#include "algorithm.h"



/**
 * @brief Ideally shorthand for unsigned long. 
 * @TODO Incorporate \ref node_type further.
 */
typedef unsigned long node_type;


/**
 * @brief Nodes in f(x) trees. Nodes are either
 * terminals (constant values or an x value) or 
 * nonterminal operators. 
 */
typedef struct node 
{
    double constant_value; /*!< stores the constant, if any */

    node_type type; /*!< stores the terminal or non-terminal */

    struct node *parent; /*!< pointer to parent node */

    struct node *branches[ MAX_ARITY ]; /*!< pointers to branches */

} node_s;




/**
 * @brief Memory allocation function. Wrapper for
 * calls to calloc for now, potentially wrapper for
 * custom memory stack allocation later. 
 * 
 * @return Pointer to new \ref node_s.
 */
node_s * node_alloc( );


/**
 * @brief Generates random f(x) tree node.
 * 
 * @param [out] individual Pointer to \ref node_s which contains
 * the f(x) tree node generated. 
 */
void node_spawn( node_s * node );


/**
 * @brief Generates full f(x) tree under a root node.
 * 
 * @param [out] root A pointer to \ref node_s which a tree is generated for. 
 * @param [in] depth The depth at which to generate the f(x) tree.
 * @param [in] parent A pointer to \ref node_s which is the parent of
 * the root node in this context. Required so that we can traverse f(x) trees
 * after swapping branches.
 */
void generate_full_tree(
        node_s * root,
        unsigned long depth,
        node_s * parent ); // generate random full trees

/**
 * 
 * @param [in] in A pointer to \ref node_s to copy to. 
 * @param [out] out A pointer to \ref node_s to copy.
 * @param [in] parent A pointer to \ref node_s which is the parent of the node
 * copied.
 */
void node_copy(node_s * in, node_s * out, node_s * parent);


/**
 * @brief Cleans up memory associated with the \ref node_s data.
 * 
 * @param [in] root Pointer to \ref node_s which contains
 * the f(x) tree noed generated.
 */
void node_free( node_s ** root ); 


/**
 * @brief Evaluates a tree's fitness.  
 * 
 * Recursive function that evaluates branches
 * and applies operators to their values.
 * 
 * @param [in] root A pointer to \ref node_s which is the node to traverse 
 * for evaluation.
 * @param [in] input_x The x in input x value to evaluate the tree's f(x) value.
 * 
 * @return The value of the operation evaluated. 
 */
double node_evaluate( 
        node_s * root, 
        double input_x ); 


/**
 * @brief Recursively counts terminal and nonterminal nodes. 
 * 
 * @param [in] root A pointer to \ref node_s which indicates the 
 * tree to traverse.
 * @param [out] A pointer to unsigned long which records the number of
 * terminal nodes in the tree. 
 * @param [out] A pointer to unsigned long which records the number of
 * nonterminal nodes in the tree. 
 */
void node_calc_size(
        node_s * root, 
        unsigned long * terminals, 
        unsigned long * nonterminalss); 


/**
 * @brief Traverses tree until a target number of terminal nodes have
 * been traversed. Used to find nodes to crossover. 
 * 
 * @param [in] root A pointer to \ref node_s which is walked over in the 
 * search for a node to crossover.
 * @param [out] target A pointer to a pointer to \ref node_s which references the
 * node to crossover once it is found.
 */
void node_walk_terminals(
        node_s * root, 
        node_s ** target );


/**
 * @brief Traverses tree until a target number of nonterminal nodes have
 * been traversed. Used to find nodes to crossover. 
 * 
 * @param [in] root A pointer to \ref node_s which is walked over in the 
 * search for a node to crossover.
 * @param [out] target A pointer to a pointer to \ref node_s which references the
 * node to crossover once it is found.
 */
void node_walk_nonterminals(
        node_s * node, 
        node_s ** target );


/**
 * @brief With \ref MUTATE_PROBABILITY the node passed to the function
 * will be mutated.
 * 
 * @param [out] root A pointer to \ref node_s which has a chance 
 * of being mutated.
 */
void node_mutate( node_s * root );


/**
 * @brief Utility function.
 * 
 * @param [in] min
 * @param [out] max
 * 
 * @return random number 
 */
double random_double_in_range( double min, double max );


/**
 * @brief Utility function.
 * 
 * @param [in] mod_value i.e, rand() % mod_value.
 * 
 * @return random number 
 */
unsigned long random_unsigned_long( unsigned long mod_value );


/**
 * @brief Utility function.
 * 
 * @param [in] min
 * @param [in] max
 * 
 * @return random number 
 */
unsigned long random_unsigned_long_in_range( 
        unsigned long min, 
        unsigned long max );


/**
 * @brief Recursive function to print operations associated with each node.
 * 
 * @param [in] root A pointer to \ref node_s whose operation is printed.
 * @param [in] stream File * to write operations to.
 * @param [in] level Positive number representing level of tree depth where root is 1.
 */
void node_print_operations( 
        node_s * root, 
        FILE * stream,
        int level );




#endif //NODE_H
