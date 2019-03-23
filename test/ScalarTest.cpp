#include "../include/Scalar.h"
#include "catch.hpp"


using namespace metal;


TEST_CASE( "Scalars can be created", "[scalar_construct]" )
{
    Scalar x{ 2.5 };

    REQUIRE( x.value() == 2.5 );
    REQUIRE( x.partial() == Scalar::Partial{} );
    REQUIRE( x.parameterMap() == ParameterMap{} );
    REQUIRE( x.dim() == 0 );
    REQUIRE( x.size() == 0 );
    REQUIRE( x.parameters() == ParameterPtrVector{} );
    REQUIRE_THROWS( x.at( nullptr ) );

    SECTION( "resizing bigger changes size and capacity" )
    {
        // x.resize( 10 );

        // REQUIRE( v.size() == 10 );
        // REQUIRE( v.capacity() >= 10 );
    }
}
