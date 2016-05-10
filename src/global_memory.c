
#include <stdlib.h>
#include <stdio.h>

#include "global_memory.h"




//
void init_global_memory()
{
    GLOBAL_POPULATION_MEMORY_TABLE =
            (population_ref*)
            calloc( GLOBAL_POPULATION_MEMORY_TABLE_SIZE, sizeof(population_ref) );
}


//
void release_global_memory()
{
    for( unsigned long idx = 0; idx < GLOBAL_POPULATION_MEMORY_TABLE_SIZE; ++idx )
    {
        if( GLOBAL_POPULATION_MEMORY_TABLE[ idx ] != NULL )
        {
            population_free( &GLOBAL_POPULATION_MEMORY_TABLE[ idx ] );
            GLOBAL_POPULATION_MEMORY_TABLE[ idx ] = NULL;
        }
    }

    free( GLOBAL_POPULATION_MEMORY_TABLE );
}


void graceful_exit( const unsigned int exit_code )
{
    release_global_memory();

    exit( exit_code );
}