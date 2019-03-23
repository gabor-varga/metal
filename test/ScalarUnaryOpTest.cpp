#include "../include/ScalarUnaryOp.h"
#include "../include/UnaryMathOp.h"
#include "TestSuite.h"


using namespace metal;


TEST_CASE( "Unary operations can be applied on scalars", "[scalar_unary_sine]" )
{
    SECTION( "Sine without partials" )
    {
        const Scalar x{ 2.0 };
        const auto y = sin( x );

        REQUIRE( y.value() == sin( 2.0 ) );
        REQUIRE_PARTIALS_EMPTY( y );
    }

    SECTION( "Sine with partials" )
    {
        const Scalar x{ 2.0, "x" };
        const auto y = sin( x );

        REQUIRE( y.value() == sin( 2.0 ) );
        REQUIRE_PARTIALS_EQUAL( y, cos( 2.0 ) );
    }
}
