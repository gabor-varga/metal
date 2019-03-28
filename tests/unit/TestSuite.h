#ifndef METAL_TEST_SUITE_H
#define METAL_TEST_SUITE_H


#include "Core.h"
#include "catch.hpp"


constexpr double Pi = 3.141592653589793;


using Vector = std::vector< double >;


inline bool almostEqual( double left, double right, double tol = 0.0 )
{
    return std::fabs( left - right ) <= tol;
}

inline Vector generate( double start, double end, unsigned num )
{
    Vector out( num );
    const double step = ( end - start ) / num;
    for ( unsigned i = 0; i < num; i++ )
    {
        out[i] = start + i * step;
    }
    return out;
}

inline void REQUIRE_PARTIALS_EMPTY( const metal::Scalar& x )
{
    REQUIRE( x.dim() == 0 );
    REQUIRE( x.size() == 0 );
    REQUIRE( x.parameters() == metal::ParameterPtrVector{} );
}

template< typename Expr >
inline void REQUIRE_VALUE_EQUAL( const metal::ScalarBase< Expr >& x, double v )
{
    REQUIRE( almostEqual( x.value(), v ) );
}

template< typename Expr >
inline void REQUIRE_PARTIALS_EQUAL( const metal::ScalarBase< Expr >& x, double v )
{
    metal::Scalar::Partial partial{ 1 };
    partial << v;
    const auto p = x.parameters().front();
    REQUIRE( x.dim() == 1 );
    REQUIRE( x.size() == 1 );
    REQUIRE( x.parameters() == metal::ParameterPtrVector{ p } );
    REQUIRE( x.at( p ) == partial );
}

template< typename Func >
inline void testPartial( Func func, double x, double eps = 1e-6, double tol = 1e-6 )
{
    metal::Scalar s{ x, "x" };
    const auto p = s.parameters().front();

    const double f1 = func( s + eps ).value();
    const double f2 = func( s - eps ).value();
    const double numeric = ( f1 - f2 ) / ( 2 * eps );
    const double analytic = func( s ).at( p )[0];

    if ( ! almostEqual( numeric, analytic, tol ) )
    {
        std::cout << "x: " << x << std::endl;
        std::cout << "f1: " << f1 << std::endl;
        std::cout << "f2: " << f2 << std::endl;
        std::cout << "numeric: " << numeric << std::endl;
        std::cout << "analytic: " << analytic << std::endl;
        std::cout << "numeric - analytic: " << numeric - analytic << std::endl;
        std::cout << "tol: " << tol << std::endl;
    }

    REQUIRE( almostEqual( numeric, analytic, tol ) );
}

template< typename Func >
inline void testPartial( Func func, const Vector& vec, double eps = 1e-6, double tol = 1e-6 )
{
    for ( const auto& x : vec )
    {
        testPartial( func, x, eps, tol );
    }
}

#endif // METAL_TEST_SUITE
