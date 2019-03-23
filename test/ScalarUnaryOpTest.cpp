#include "../include/ScalarUnaryOp.h"
#include "../include/UnaryMathOp.h"
#include "../include/Scalar.h"
#include "catch.hpp"


using namespace metal;


TEST_CASE( "Scalars can be modified by adding numbers", "[scalar_modify_add]" )
{
    SECTION( "Sine without partials" )
    {
        const Scalar x{ 2.0 };
        const auto y = sin( x );

        REQUIRE( y.value() == sin( 2.0 ) );
    }

    SECTION( "Sine with partials" )
    {
        const Scalar x{ 2.0, "x" };
        const auto y = sin( x );

        REQUIRE( y.value() == sin( 2.0 ) );
    }
}
