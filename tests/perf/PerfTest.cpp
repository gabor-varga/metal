#include "src/Core.h"
#include <chrono>
#include <iomanip>


template< typename Func >
double measure( const Func& func, int runs )
{
    auto start = std::chrono::steady_clock::now();

    for ( int i = 0; i < runs; i++ )
    {
        func();
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    return std::chrono::duration< double, std::nano >( diff ).count();
}

template< typename Func >
void measure( const Func& func, bool verbose = false )
{
    int runs = 1;
    double dt = 0;

    while ( true )
    {
        dt = measure( func, runs );
        if ( verbose )
        {
            std::cout << std::setw( 15 ) << runs;
            std::cout << std::setw( 15 ) << dt << " ns";
            std::cout << std::setw( 15 ) << dt / runs << " ns";
            std::cout << std::endl;
        }
        if ( dt > 1e7 )
        {
            break;
        }
        runs *= 2;
    };

    std::cout << dt / runs << " ns" << std::endl;
}


int main()
{
    const metal::Scalar a{ 3.0, "a" };
    const metal::Scalar b{ 4.0, "b" };
    const metal::Scalar c{ 2.0, "c" };
    const metal::Scalar d{ 5.0, "d" };

    const auto f1 = [&]() -> metal::Scalar 
    {
        return metal::Scalar{ metal::Scalar{ a * b } - metal::Scalar{ c * d } };
    };

    const auto f2 = [&]() -> metal::Scalar 
    {
        return metal::Scalar{ a * b - c * d };
    };

    measure( f1, true );
    measure( f2, true );

    return 0;
}
