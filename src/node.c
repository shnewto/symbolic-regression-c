
#include <stdio.h>
#include <stdlib.h> 

#include "node.h"




//
node_s * node_alloc( )
{
    node_s *node = (node_s*)calloc( 1, sizeof(node_s) );

    if( node == NULL )
    {
        fprintf( stderr, "calloc failed in node_alloc\n");
        exit( EXIT_FAILURE );
    }
    
    return node;
}


//
void node_spawn( node_s * node )
{
    node->parent = NULL;
    node->constant_value = 0.0;
    node->type = INVALID_NODE;

    for( unsigned long idx = 0; idx < MAX_ARITY; ++idx )
    {
        node->branches[ idx ] = NULL;
    }
}


//
void generate_full_tree(
        node_s * root,
        unsigned long depth,
        node_s * parent )
{
    if( root == NULL )
    {
        fprintf( stderr, "bad parameter in generate_full_tree\n" );
        exit( EXIT_FAILURE );
    }

    node_spawn( root );

    root->parent = parent;// point to parent node
    
    if( depth > INITIAL_TREE_DEPTH )
    {
        fprintf( stderr, "bad recursion in generate_full_tree\n" );
    }
    
    if( depth == INITIAL_TREE_DEPTH ) // if at max depth put in terminal
    {
        root->type = random_unsigned_long( TERMINAL_COUNT )
                + TERMINAL_OFFSET;  

        if ( root->type == CONSTANT ) // if a constant include a value
        {
            root->constant_value = random_double_in_range( -CONSTANT_VALUE_LIMIT, CONSTANT_VALUE_LIMIT ); 
        }        
    }
    else // else add non-terminal
    {
        root->type = random_unsigned_long( OPERATOR_COUNT );

        if( (root->type == MINIMUM)
                || (root->type == MAXIMUM)
                || (root->type == ADD)
                || (root->type == SUBTRACT)
                || (root->type == MULTIPLY) 
                || (root->type == DIVIDE) )
        {
            for( unsigned long idx = 0; idx < MAX_ARITY; ++idx )
            {
                root->branches[ idx ] = node_alloc();

                generate_full_tree(
                        root->branches[ idx ],
                        depth + 1,
                        root );
            }
        }
        else
        {
            fprintf( stderr, "Unknown case in generate_full_tree\n" );
            exit( EXIT_FAILURE );
        }
    }
}


//
void node_copy( node_s * in, node_s * out, node_s * parent )
{
    if( (in == NULL) || (out == NULL) )
    {
        fprintf( stderr, "bad parameter in node_copy\n" );
        exit( EXIT_FAILURE );
    }
           
    out->type = in->type;
    out->constant_value = in->constant_value;
    out->parent = parent;

    // check for non-terminal source node
    if( (in->type != INPUTX) && (in->type != CONSTANT) )
    {
        for( unsigned long idx = 0; idx < MAX_ARITY; ++idx )
        {
            out->branches[ idx ] = node_alloc();
            node_copy( in->branches[ idx ], out->branches[ idx ], in );
        }
    }
}


//
void node_free( node_s ** root )
{
    if( (*root) == NULL )
    {
        return;
    }

    if( ((*root)->type == MINIMUM)
            || ((*root)->type == MAXIMUM)
            || ((*root)->type == ADD)
            || ((*root)->type == SUBTRACT) 
            || ((*root)->type == MULTIPLY)
            || ((*root)->type == DIVIDE) )
    {
        for( unsigned long idx = 0; idx < MAX_ARITY; ++idx )
        {
            node_free( &(*root)->branches[ idx ] );
        }
    }

    free( (*root) );
    (*root) = NULL;
}


//
double node_evaluate( node_s * root, double input_x )
{
    if( root == NULL )
    {
        fprintf( stderr, "bad parameter in node_evaluate\n" );
        exit( EXIT_FAILURE );
    }
    
    /* evaluates the tree , for a given X. */
    double left_branch = 0.0;
    double right_branch = 0.0;

    if( root->type == INPUTX )
    {
        return input_x;
    }

    if( root->type == CONSTANT )
    {
        return ( root->constant_value );
    }

    left_branch = node_evaluate( root->branches[0], input_x );
    right_branch = node_evaluate( root->branches[1], input_x );

    if( root->type == MINIMUM )
    {
        if( left_branch < right_branch )
        {
            return left_branch;
        }
        else
        {
            return right_branch;
        }
    }
    else if( root->type == MAXIMUM )
    {
        if( left_branch < right_branch )
        {
            return right_branch;
        }
        else
        {
            return left_branch;
        }
    }
    else if( root->type == ADD )
    {
        return ( left_branch + right_branch );
    }
    else if( root->type == SUBTRACT )
    {
        return ( left_branch - right_branch );
    }
    else if( root->type == MULTIPLY )
    {
        return ( left_branch * right_branch );
    }
    else if( root->type == DIVIDE )
    {
        if( right_branch == 0 )
        {
            return ( left_branch );
        }
        else
        {
            return ( left_branch / right_branch );
        }
    }
    else
    {
        fprintf( stderr, "Error, unknown case in node_evaluate \n" );
        exit( EXIT_FAILURE );
    }


    return 0;
}


//
void node_calc_size( 
        node_s * root, 
        unsigned long * terminals, 
        unsigned long * nonterminals )
{
    if( (root == NULL) || (terminals == NULL) || (nonterminals == NULL) )
    {
        fprintf( stderr, "bad parameter in node_calc_size\n" );
        exit( EXIT_FAILURE );
    }
    
    if( (root->type == INPUTX) || (root->type == CONSTANT) )
    { 
        (*terminals)++;
    }
    else
    {
        (*nonterminals)++;

        for( unsigned long idx = 0; idx < MAX_ARITY; idx++ )
        {
            node_calc_size( root->branches[ idx ], terminals, nonterminals );
        }
    }
    
}


//
void node_walk_terminals(
        node_s * node, 
        node_s ** target )
{
    if( node == NULL )
    {
        fprintf( stderr, "bad parameter in node_walk_terms\n" );
        exit( EXIT_FAILURE );
    }
    
    if( GLOBAL_LAST_STEP == GLOBAL_STEP_COUNT )
    {
        GLOBAL_STEP_COUNT++;

        *target = node;            
        
        return;
    }

    if( (node->type == INPUTX) || (node->type == CONSTANT) )
    {
        GLOBAL_STEP_COUNT++;
    }
    else
    {
        for( unsigned long idx = 0; idx < MAX_ARITY; ++idx )
        {
            node_walk_terminals( node->branches[ idx ], target );
        }
    }
}


//
void node_walk_nonterminals(
        node_s * node, 
        node_s ** target )
{
    if( node == NULL )
    {
        fprintf( stderr, "bad parameter in node_walk_terms\n" );
        exit( EXIT_FAILURE );
    }    

    if( GLOBAL_LAST_STEP == GLOBAL_STEP_COUNT )
    {
        GLOBAL_STEP_COUNT++;

        *target = node;            
        
        return;
    }
    
    if( (node->type != INPUTX) && (node->type != CONSTANT) )
    {
        for( unsigned long idx = 0;idx < MAX_ARITY;++idx )
        {
            GLOBAL_STEP_COUNT++;
            
            node_walk_nonterminals( 
                    node->branches[ idx ], 
                    target );
        }
    }
}


//
void node_mutate( node_s *root )
{
    if( root == NULL )
    {
        fprintf( stderr, "bad parameter in node_mutate\n" );
        exit( EXIT_FAILURE );
    }
    
    if( random_unsigned_long( 100 ) < MUTATE_PROBABILITY )
    {
        if( (root->type == CONSTANT) || (root->type == INPUTX) )
        { 
            root->type = random_unsigned_long( TERMINAL_COUNT ) 
                    + TERMINAL_OFFSET;

            if( root->type == CONSTANT )
            {
                root->constant_value = random_double_in_range( -CONSTANT_VALUE_LIMIT, CONSTANT_VALUE_LIMIT );
            }                
        }
        else
        {
            root->type = random_unsigned_long( OPERATOR_COUNT );

            for( unsigned long idx = 0;idx < MAX_ARITY;++idx )
            {
                node_mutate( root->branches[ idx ] );
            }
        }        
    }   
}


//
double random_double_in_range( double min, double max )
{
    return ( ((double)rand() * ( max - min )) 
            / (double)RAND_MAX + min );
}


//
unsigned long random_unsigned_long( unsigned long mod_value )
{
    return ( (unsigned long)rand() % mod_value );
}


//
unsigned long random_unsigned_long_in_range( 
        unsigned long min, 
        unsigned long max )
{
       double scaled = (double)rand()/RAND_MAX;

       return (max - min +1)*scaled + min;

}


//
void node_print_operations( 
        node_s * root, 
        FILE * stream,
        int level )
{
    if( stream == NULL )
    {
        fprintf( stderr, "bad parameter in node_print_operation\n" );
        exit( EXIT_FAILURE );
    }
    
    if( root == NULL )
    {
        return;
    }    

    
    node_print_operations( root->branches[1], stream, level + 1 );   
//    fprintf( stream, "%*s", level, " ");


    
    if( root->type == INPUTX )
    {   
        fprintf( stream, "%*sx\n", level*10 + 2, " " );
        return;
    }

    if( root->type == CONSTANT )
    {
        fprintf( stream, "%*s%f\n", level*10 + 2, " ", root->constant_value );        
        return;
    }        
    
    fprintf( stream, "%*s/\n", level*10 + 10, " " );      
    
    if( root->type == MINIMUM )
    {
        fprintf( stream, "%*sL%d::min::\n", level*10, " ", level );
    }
    else if( root->type == MAXIMUM )
    {
        fprintf( stream, "%*sL%d::max::\n", level*10, " ", level );
    }
    else if( root->type == ADD )
    {
        fprintf( stream, "%*sL%d::add::\n", level*10, " ", level ); 
    }
    else if( root->type == SUBTRACT )
    {
        fprintf( stream, "%*sL%d::sub::\n", level*10, " ", level );  
    }
    else if( root->type == MULTIPLY )
    {
        fprintf( stream, "%*sL%d::mul::\n", level*10, " ", level );
    }
    else if( root->type == DIVIDE )
    {   
        fprintf( stream, "%*sL%d::div::\n", level*10, " ", level );
    }
    else
    {
        fprintf( stderr, "Error, unknown case in node_print_operation\n" );
        exit( EXIT_FAILURE );
    }
    
    fprintf( stream, "%*s\\\n", level*10 + 10, " " );              
    
    node_print_operations( root->branches[0], stream, level + 1 );
}