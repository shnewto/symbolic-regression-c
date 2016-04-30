

#include <cgreen/cgreen.h>

#include "population.h"

Describe(population);

BeforeEach(population)
{}

AfterEach(population)
{}

Ensure( population, alloc_and_free_succeed )
{

    population_s *population = NULL;
    
    population = population_alloc();

    assert_that(
            population,
            is_not_equal_to(NULL) );
    
    population_free( &population );
    
    assert_that(
            population, 
            is_equal_to(NULL));
}
