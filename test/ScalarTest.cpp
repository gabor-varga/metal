#include "../include/Scalar.h"
#include "catch.hpp"


using namespace metal;


void REQUIRE_PARTIALS_EMPTY( const Scalar& x )
{
    REQUIRE( x.partial() == Scalar::Partial{} );
    REQUIRE( x.parameterMap() == ParameterMap{} );
    REQUIRE( x.dim() == 0 );
    REQUIRE( x.size() == 0 );
    REQUIRE( x.parameters() == ParameterPtrVector{} );
}

void REQUIRE_PARTIALS_UNITY( const Scalar& x )
{
    const auto p = x.parameters().front();
    REQUIRE( x.partial() == Scalar::Partial::Ones( 1 ) );
    REQUIRE( x.parameterMap() == ParameterMap{ { p, 0 } } );
    REQUIRE( x.dim() == 1 );
    REQUIRE( x.size() == 1 );
    REQUIRE( x.parameters() == ParameterPtrVector{ p } );
    REQUIRE( x.at( p ) == Scalar::Partial::Ones( 1 ) );
}


TEST_CASE( "Scalars can be created", "[scalar_construct]" )
{
    SECTION( "Simple construction from value" )
    {
        const Scalar x{ 1.5 };

        REQUIRE( x.value() == 1.5 );
        REQUIRE_PARTIALS_EMPTY( x );
        REQUIRE_THROWS( x.at( nullptr ) );
    }

    SECTION( "Construction from value by giving a name" )
    {
        const Scalar x{ 2.5, "x" };

        REQUIRE( x.value() == 2.5 );
        REQUIRE_PARTIALS_UNITY( x );
    }
}


TEST_CASE( "Scalars can be modified by adding numbers", "[scalar_modify_add]" )
{
    SECTION( "Addition without partials" )
    {
        Scalar x{ 3.5 };
        x += 1.5;

        REQUIRE( x.value() == 5.0 );
        REQUIRE_PARTIALS_EMPTY( x );
    }

    SECTION( "Addition with partials" )
    {
        Scalar x{ 3.5, "x" };
        x += 1.5;

        REQUIRE( x.value() == 5.0 );
        REQUIRE_PARTIALS_UNITY( x );
    }
}


TEST_CASE( "Scalars can be modified by subtracting numbers", "[scalar_modify_sub]" )
{
    SECTION( "Subtraction without partials" )
    {
        Scalar x{ 3.5 };
        x -= 1.5;

        REQUIRE( x.value() == 2.0 );
        REQUIRE_PARTIALS_EMPTY( x );
    }

    SECTION( "Subtraction with partials" )
    {
        Scalar x{ 3.5, "x" };
        x -= 1.5;

        REQUIRE( x.value() == 2.0 );
        REQUIRE_PARTIALS_UNITY( x );
    }
}


TEST_CASE( "Scalars can be modified by multiplication by numbers", "[scalar_modify_mul]" )
{
    SECTION( "Subtraction without partials" )
    {
        Scalar x{ 3.0 };
        x *= 1.5;

        REQUIRE( x.value() == 4.5 );
        REQUIRE_PARTIALS_EMPTY( x );
    }

    SECTION( "Subtraction with partials" )
    {
        Scalar x{ 3.0, "x" };
        x *= 1.5;
        Scalar::Partial v{ 1 };
        v << 1.5;

        const auto p = x.parameters().front();
        REQUIRE( x.value() == 4.5 );
        REQUIRE( x.partial() == v );
        REQUIRE( x.parameterMap() == ParameterMap{ { p, 0 } } );
        REQUIRE( x.dim() == 1 );
        REQUIRE( x.size() == 1 );
        REQUIRE( x.parameters() == ParameterPtrVector{ p } );
        REQUIRE( x.at( p ) == v );
    }
}


TEST_CASE( "Scalars can be modified by dividing by numbers", "[scalar_modify_div]" )
{
    SECTION( "Divide without partials" )
    {
        Scalar x{ 3.0 };
        x /= 1.5;

        REQUIRE( x.value() == 2.0 );
        REQUIRE_PARTIALS_EMPTY( x );
    }

    SECTION( "Divide with partials" )
    {
        Scalar x{ 3.0, "x" };
        x /= 1.5;
        Scalar::Partial v{ 1 };
        v << 1.0 / 1.5;

        const auto p = x.parameters().front();
        REQUIRE( x.value() == 2.0 );
        REQUIRE( x.partial() == v );
        REQUIRE( x.parameterMap() == ParameterMap{ { p, 0 } } );
        REQUIRE( x.dim() == 1 );
        REQUIRE( x.size() == 1 );
        REQUIRE( x.parameters() == ParameterPtrVector{ p } );
        REQUIRE( x.at( p ) == v );
    }
}
