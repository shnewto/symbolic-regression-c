#include <cgreen/cgreen.h>

#include "individual.h"

Describe( individual_tests );

// Unfortunately required even if unused
BeforeEach( individual_tests )
{}

AfterEach( individual_tests )
{}

Ensure( individual_tests, alloc_and_free_succeed )
{

    individual_s *individual = NULL;
    
    individual = individual_alloc();

    assert_that(
            individual,
            is_not_equal_to(NULL) );
    
    individual_free( &individual );
    
    assert_that(
            individual, 
            is_equal_to(NULL));
}
