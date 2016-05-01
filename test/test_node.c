#include <cgreen/cgreen.h>

#include "node.h"

Describe( node_tests );

BeforeEach( node_tests )
{}

AfterEach( node_tests )
{}

Ensure( node_tests, alloc_and_free_succeed )
{

    node_s *node = NULL;
    
    node = node_alloc();

    assert_that(
            node,
            is_not_equal_to(NULL) );
    
    node_free( &node );
    
    assert_that(
            node, 
            is_equal_to(NULL));
}
