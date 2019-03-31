#ifndef METAL_TEST_SUITE_H
#define METAL_TEST_SUITE_H


#include "Core.h"
#include "catch.hpp"
#include <random>


constexpr double Pi = 3.141592653589793;

using Vector = std::vector< double >;
using PairVector = std::vector< std::pair< double, double > >;


class Random
{
public:
    static double generate( double start, double end )
    {
        std::uniform_real_distribution< double > distribution( start, end );
        return distribution( engine );
    }

    static Vector generate( double start, double end, int num )
    {
        Vector out( static_cast< size_t >( num ) );
        std::generate( out.begin(), out.end(), [=]() { return generate( start, end ); } );
        return out;
    }

private:
    static std::default_random_engine engine;
};

std::default_random_engine Random::engine{};


inline bool almostEqual( double left, double right, double rtol = 0.0, double atol = 0.0 )
{
    return std::fabs( left - right )
        <= rtol * std::max( std::fabs( left ), std::fabs( right ) ) + atol;
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


template< typename Func, typename SFunc >
inline void testUnary(
    Func func, SFunc sfunc, double x, double eps = 1e-6, double rtol = 1e-6, double atol = 1e-9 )
{
    {
        metal::Scalar s{ x };
        REQUIRE_PARTIALS_EMPTY( s );
        const auto y = sfunc( s );
        REQUIRE( almostEqual( func( x ), y.value() ) );
        REQUIRE_PARTIALS_EMPTY( y );
    }

    metal::Scalar s{ x, "x" };
    REQUIRE( almostEqual( func( x ), sfunc( s ).value() ) );

    const auto p = s.parameters().front();

    const double f1 = func( x + eps );
    const double f2 = func( x - eps );
    const double numeric = ( f1 - f2 ) / ( 2 * eps );
    const double analytic = sfunc( s ).at( p )[0];

    if ( !almostEqual( numeric, analytic, rtol, atol ) )
    {
        std::cout << "x: " << x << std::endl;
        std::cout << "f1: " << f1 << std::endl;
        std::cout << "f2: " << f2 << std::endl;
        std::cout << "numeric: " << numeric << std::endl;
        std::cout << "analytic: " << analytic << std::endl;
        std::cout << "numeric - analytic: " << numeric - analytic << std::endl;
        std::cout << "rtol: " << rtol << std::endl;
        std::cout << "atol: " << atol << std::endl;
        std::cout << "tol: "
                  << rtol * std::max( std::fabs( numeric ), std::fabs( analytic ) ) + atol
                  << std::endl;
    }

    REQUIRE( almostEqual( numeric, analytic, rtol, atol ) );
}

template< typename Func, typename SFunc >
inline void testUnary( Func func, SFunc sfunc, const Vector& vec, double eps = 1e-6,
    double rtol = 1e-6, double atol = 1e-9 )
{
    for ( const auto& x : vec )
    {
        testUnary( func, sfunc, x, eps, rtol, atol );
    }
}

template< typename Func, typename SFunc >
inline void testBinary( Func func, SFunc sfunc, double x, double y, double eps = 1e-6,
    double rtol = 1e-6, double atol = 1e-9 )
{
    const auto func1 = [&]( double x_ ) { return func( x_, y ); };
    const auto sfunc1 = [&]( const metal::Scalar& x_ ) { return sfunc( x_, metal::Scalar{ y } ); };
    testUnary( func1, sfunc1, x, eps, rtol, atol );

    const auto func2 = [&]( double y_ ) { return func( x, y_ ); };
    const auto sfunc2 = [&]( const metal::Scalar& y_ ) { return sfunc( metal::Scalar{ x }, y_ ); };
    testUnary( func2, sfunc2, x, eps, rtol, atol );
}

template< typename Func, typename SFunc >
inline void testBinary( Func func, SFunc sfunc, const PairVector& vec, double eps = 1e-6,
    double rtol = 1e-6, double atol = 1e-9 )
{
    for ( const auto& entry : vec )
    {
        testBinary( func, sfunc, entry.first, entry.second, eps, rtol, atol );
    }
}


#define TEST_SCALAR_UNARY( NAME, TAG, FUNC, START, END, NUM )                                      \
    TEST_CASE( NAME, TAG )                                                                         \
    {                                                                                              \
        const auto f = []( double x ) { return FUNC( x ); };                                       \
        const auto sf = []( const metal::Scalar& x ) { return FUNC( x ); };                        \
        const auto vec = Random::generate( START, END, NUM );                                      \
        testUnary( f, sf, vec );                                                                   \
    }


#define TEST_SCALAR_BINARY( NAME, TAG, FUNC, START1, END1, START2, END2, NUM )                     \
    TEST_CASE( NAME, TAG )                                                                         \
    {                                                                                              \
        const auto f = []( double x, double y ) { return FUNC( x, y ); };                          \
        const auto sf                                                                              \
            = []( const metal::Scalar& x, const metal::Scalar& y ) { return FUNC( x, y ); };       \
        const auto vec1 = Random::generate( START1, END1, NUM );                                   \
        const auto vec2 = Random::generate( START2, END2, NUM );                                   \
        PairVector vec( NUM );                                                                     \
        for ( size_t i = 0; i < NUM; i++ )                                                         \
        {                                                                                          \
            vec[i] = std::make_pair( vec1[i], vec2[i] );                                           \
        }                                                                                          \
        testBinary( f, sf, vec );                                                                  \
    }

#endif // METAL_TEST_SUITE
