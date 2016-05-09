

#include <cgreen/cgreen.h>

#include "population.h"

population_s *test_population;

Describe(population_tests);

BeforeEach(population_tests)
{
    test_population = population_alloc();
}

AfterEach(population_tests)
{
    population_free( &test_population );
}

Ensure( population_tests, alloc_and_free_succeed )
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

