#include "TestSuite.h"


using namespace metal;


TEST_CASE( "Scalars can be created", "[scalar_construct]" )
{
    SECTION( "Simple construction from value" )
    {
        const Scalar x{ 1.5 };

        REQUIRE_VALUE_EQUAL( x, 1.5 );
        REQUIRE_PARTIALS_EMPTY( x );
        REQUIRE_THROWS( x.at( nullptr ) );
    }

    SECTION( "Construction from value by giving a name" )
    {
        const Scalar x{ 2.5, "x" };

        REQUIRE_VALUE_EQUAL( x, 2.5 );
        REQUIRE_PARTIALS_EQUAL( x, 1.0 );
    }
}


TEST_CASE( "Scalars can be modified by adding numbers", "[scalar_modify_add]" )
{
    SECTION( "Addition without partials" )
    {
        Scalar x{ 3.5 };
        x += 1.5;

        REQUIRE_VALUE_EQUAL( x, 5.0 );
        REQUIRE_PARTIALS_EMPTY( x );
    }

    SECTION( "Addition with partials" )
    {
        Scalar x{ 3.5, "x" };
        x += 1.5;

        REQUIRE_VALUE_EQUAL( x, 5.0 );
        REQUIRE_PARTIALS_EQUAL( x, 1.0 );
    }
}


TEST_CASE( "Scalars can be modified by subtracting numbers", "[scalar_modify_sub]" )
{
    SECTION( "Subtraction without partials" )
    {
        Scalar x{ 3.5 };
        x -= 1.5;

        REQUIRE_VALUE_EQUAL( x, 2.0 );
        REQUIRE_PARTIALS_EMPTY( x );
    }

    SECTION( "Subtraction with partials" )
    {
        Scalar x{ 3.5, "x" };
        x -= 1.5;

        REQUIRE_VALUE_EQUAL( x, 2.0 );
        REQUIRE_PARTIALS_EQUAL( x, 1.0 );
    }
}


TEST_CASE( "Scalars can be modified by multiplication by numbers", "[scalar_modify_mul]" )
{
    SECTION( "Subtraction without partials" )
    {
        Scalar x{ 3.0 };
        x *= 1.5;

        REQUIRE_VALUE_EQUAL( x, 4.5 );
        REQUIRE_PARTIALS_EMPTY( x );
    }

    SECTION( "Subtraction with partials" )
    {
        Scalar x{ 3.0, "x" };
        x *= 1.5;

        REQUIRE_VALUE_EQUAL( x, 4.5 );
        REQUIRE_PARTIALS_EQUAL( x, 1.5 );
    }
}


TEST_CASE( "Scalars can be modified by dividing by numbers", "[scalar_modify_div]" )
{
    SECTION( "Divide without partials" )
    {
        Scalar x{ 3.0 };
        x /= 1.5;

        REQUIRE_VALUE_EQUAL( x, 2.0 );
        REQUIRE_PARTIALS_EMPTY( x );
    }

    SECTION( "Divide with partials" )
    {
        Scalar x{ 3.0, "x" };
        x /= 1.5;

        REQUIRE_VALUE_EQUAL( x, 2.0 );
        REQUIRE_PARTIALS_EQUAL( x, 1.0 / 1.5 );
    }
}
