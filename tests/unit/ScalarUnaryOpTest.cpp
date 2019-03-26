#include "TestSuite.h"


using namespace metal;


TEST_CASE( "Unary negate operation", "[scalar_unary_negate]" )
{
    SECTION( "Negation without partials" )
    {
        const Scalar x{ 1.5 };
        
        const auto y = -x;
        REQUIRE_VALUE_EQUAL( y, -1.5 );
        REQUIRE_PARTIALS_EMPTY( y );
    }

    SECTION( "Negation with partials" )
    {
        const Scalar x{ 1.5, "x" };
        
        const auto y = -x;
        REQUIRE_VALUE_EQUAL( y, -1.5 );
        REQUIRE_PARTIALS_EQUAL( y, -1.0 );

    }
}


TEST_CASE( "Unary addition operator", "[scalar_unary_add]" )
{
    SECTION( "Addition without partials" )
    {
        const Scalar x{ 1.5 };
        
        const auto y = x + 2.5;
        REQUIRE_VALUE_EQUAL( y, 4.0 );
        REQUIRE_PARTIALS_EMPTY( y );

        const auto z = 2.5 + x;
        REQUIRE_VALUE_EQUAL( z, 4.0 );
        REQUIRE_PARTIALS_EMPTY( z );
    }

    SECTION( "Addition with partials" )
    {
        const Scalar x{ 1.5, "x" };
        
        const auto y = x + 2.5;
        REQUIRE_VALUE_EQUAL( y, 4.0 );
        REQUIRE_PARTIALS_EQUAL( y, 1.0 );

        const auto z = 2.5 + x;
        REQUIRE_VALUE_EQUAL( z, 4.0 );
        REQUIRE_PARTIALS_EQUAL( z, 1.0 );
    }
}


TEST_CASE( "Unary subtraction operator", "[scalar_unary_sub]" )
{
    SECTION( "Subtraction without partials" )
    {
        const Scalar x{ 1.5 };
        
        const auto y = x - 2.5;
        REQUIRE_VALUE_EQUAL( y, -1.0 );
        REQUIRE_PARTIALS_EMPTY( y );

        const auto z = 2.5 - x;
        REQUIRE_VALUE_EQUAL( z, 1.0 );
        REQUIRE_PARTIALS_EMPTY( z );
    }

    SECTION( "Subtraction with partials" )
    {
        const Scalar x{ 1.5, "x" };
        
        const auto y = x - 2.5;
        REQUIRE_VALUE_EQUAL( y, -1.0 );
        REQUIRE_PARTIALS_EQUAL( y, 1.0 );

        const auto z = 2.5 - x;
        REQUIRE_VALUE_EQUAL( z, 1.0 );
        REQUIRE_PARTIALS_EQUAL( z, -1.0 );
    }
}


TEST_CASE( "Unary multiplication operator", "[scalar_unary_mul]" )
{
    SECTION( "Multiplication without partials" )
    {
        const Scalar x{ 1.5 };
        
        const auto y = x * 3.0;
        REQUIRE_VALUE_EQUAL( y, 4.5 );
        REQUIRE_PARTIALS_EMPTY( y );

        const auto z = 3.0 * x;
        REQUIRE_VALUE_EQUAL( z, 4.5 );
        REQUIRE_PARTIALS_EMPTY( z );
    }

    SECTION( "Multiplication with partials" )
    {
        const Scalar x{ 1.5, "x" };
        
        const auto y = x * 3.0;
        REQUIRE_VALUE_EQUAL( y, 4.5 );
        REQUIRE_PARTIALS_EQUAL( y, 3.0 );

        const auto z = 3.0 * x;
        REQUIRE_VALUE_EQUAL( z, 4.5 );
        REQUIRE_PARTIALS_EQUAL( z, 3.0 );
    }
}


TEST_CASE( "Unary division operator", "[scalar_unary_div]" )
{
    SECTION( "Division without partials" )
    {
        const Scalar x{ 1.5 };
        
        const auto y = x / 3.0;
        REQUIRE_VALUE_EQUAL( y, 0.5 );
        REQUIRE_PARTIALS_EMPTY( y );

        const auto z = 3.0 / x;
        REQUIRE_VALUE_EQUAL( z, 2.0 );
        REQUIRE_PARTIALS_EMPTY( z );
    }

    SECTION( "Division with partials" )
    {
        const Scalar x{ 1.5, "x" };
        
        const auto y = x / 3.0;
        REQUIRE_VALUE_EQUAL( y, 0.5 );
        REQUIRE_PARTIALS_EQUAL( y, 1.0 / 3.0 );

        const auto z = 3.0 / x;
        REQUIRE_VALUE_EQUAL( z, 2.0 );
        REQUIRE_PARTIALS_EQUAL( z, 1.0 / 1.5 );
    }
}


TEST_CASE( "Unary math operations can be applied on scalars", "[scalar_unary_sine]" )
{
    SECTION( "Sine without partials" )
    {
        const Scalar x{ 2.0 };
        const auto y = sin( x );

        REQUIRE_VALUE_EQUAL( y, sin( 2.0 ) );
        REQUIRE_PARTIALS_EMPTY( y );
    }

    SECTION( "Sine with partials" )
    {
        const Scalar x{ 2.0, "x" };
        const auto y = sin( x );

        REQUIRE_VALUE_EQUAL( y, sin( 2.0 ) );
        REQUIRE_PARTIALS_EQUAL( y, cos( 2.0 ) );
    }
}
