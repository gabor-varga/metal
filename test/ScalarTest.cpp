#include "../include/Scalar.h"
#include "catch.hpp"


using namespace metal;


TEST_CASE( "Scalars can be created", "[scalar_construct]" )
{
    SECTION( "Simple construction from value" )
    {
        Scalar x{ 2.5 };

        REQUIRE( x.value() == 2.5 );
        REQUIRE( x.partial() == Scalar::Partial{} );
        REQUIRE( x.parameterMap() == ParameterMap{} );
        REQUIRE( x.dim() == 0 );
        REQUIRE( x.size() == 0 );
        REQUIRE( x.parameters() == ParameterPtrVector{} );
        REQUIRE_THROWS( x.at( nullptr ) );
    }

    SECTION( "Construction from value by giving a name" )
    {
        Scalar x{ 3.5, "x" };
        const auto p = x.parameters().front();

        REQUIRE( x.value() == 3.5 );
        REQUIRE( x.partial() == Scalar::Partial::Ones( 1 ) );
        REQUIRE( x.parameterMap() == ParameterMap{ { p, 0 } } );
        REQUIRE( x.dim() == 1 );
        REQUIRE( x.size() == 1 );
        REQUIRE( x.parameters() == ParameterPtrVector{ p } );
        REQUIRE( x.at( p ) == Scalar::Partial::Ones( 1 ) );
    }
}
