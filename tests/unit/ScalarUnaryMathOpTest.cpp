#include "TestSuite.h"


using namespace metal;


TEST_CASE( "Sine operation can be applied to scalars", "[scalar_unary_sin]" )
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
        const auto f = [] ( const Scalar& a ) { return sin( a ); };
        const auto vec = generate( -Pi, Pi, 100 );
        testPartial( f, vec );
    }
}

TEST_CASE( "Cosine operation can be applied to scalars", "[scalar_unary_cos]" )
{
    SECTION( "Cosine without partials" )
    {
        const Scalar x{ 2.0 };
        const auto y = cos( x );

        REQUIRE_VALUE_EQUAL( y, cos( 2.0 ) );
        REQUIRE_PARTIALS_EMPTY( y );
    }

    SECTION( "Cosine with partials" )
    {
        const auto f = [] ( const Scalar& a ) { return cos( a ); };
        const auto vec = generate( -Pi, Pi, 100 );
        testPartial( f, vec );
    }
}

TEST_CASE( "Tangent operation can be applied to scalars", "[scalar_unary_tan]" )
{
    SECTION( "Tangent without partials" )
    {
        const Scalar x{ 2.0 };
        const auto y = tan( x );

        REQUIRE_VALUE_EQUAL( y, tan( 2.0 ) );
        REQUIRE_PARTIALS_EMPTY( y );
    }

    SECTION( "Tangent with partials" )
    {
        const auto f = [] ( const Scalar& a ) { return tan( a ); };
        const auto vec = generate( -Pi / 3, Pi / 3, 100 );
        testPartial( f, vec );
    }
}

