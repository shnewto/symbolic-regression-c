
#ifndef GLOBAL_MEMORY_H
#define GLOBAL_MEMORY_H




#include "population.h"




/**
 * @brief Max populations allowed.
 */
#define GLOBAL_POPULATION_MEMORY_TABLE_SIZE (10)




population_ref * GLOBAL_POPULATION_MEMORY_TABLE;




/**
 * @brief Initialize global memory. 
 * 
 * At the moment the global memory is just a solution to the 
 * "graceful exit" problem. Maybe in the future there will be more
 * sophistication involved.
 */
void init_global_memory();



/**
 * @brief Release global memory. 
 * 
 * At the moment the global memory is just a solution to the 
 * "graceful exit" problem. Maybe in the future there will be more
 * sophistication involved.
 */
void release_global_memory();


/**
 * @brief Release global memory and exit.
 * 
 * @param [in] exit_code Exit code used in call to exit(). 
 */
void graceful_exit( const unsigned int exit_code );




#endif // GLOBAL_MEMORY_H
