#ifndef METAL_TEST_SUITE_H
#define METAL_TEST_SUITE_H


#include "../include/Scalar.h"
#include "catch.hpp"


inline void REQUIRE_PARTIALS_EMPTY( const metal::Scalar& x )
{
    REQUIRE( x.partial() == metal::Scalar::Partial{} );
    REQUIRE( x.parameterMap() == metal::ParameterMap{} );
    REQUIRE( x.dim() == 0 );
    REQUIRE( x.size() == 0 );
    REQUIRE( x.parameters() == metal::ParameterPtrVector{} );
}

inline void REQUIRE_PARTIALS_EQUAL( const metal::Scalar& x, double v )
{
    metal::Scalar::Partial partial{ 1 };
    partial << v;
    const auto p = x.parameters().front();
    REQUIRE( x.partial() == partial );
    REQUIRE( x.parameterMap() == metal::ParameterMap{ { p, 0 } } );
    REQUIRE( x.dim() == 1 );
    REQUIRE( x.size() == 1 );
    REQUIRE( x.parameters() == metal::ParameterPtrVector{ p } );
    REQUIRE( x.at( p ) == partial );
}

#endif // METAL_TEST_SUITE
