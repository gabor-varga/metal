#include "Core.h"
#include "Vector.h"


int main()
{
    metal::Scalar t{ 1.0 };
    std::cout << t << std::endl;

    metal::Scalar a{ 1.0, "myVeryLongParameterName" };
    metal::Scalar b{ 2.0, "b" };
    metal::Scalar c{ 3.0, "c" };
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;

    metal::Scalar x = -sin( a + b ) + 0.5 * c;
    std::cout << x << std::endl;

    const auto y = a + b;
    std::cout << y.at( a.parameters().front() ) << std::endl;
    std::cout << y << std::endl;
    std::cout << metal::Scalar{ y } << std::endl;
    // std::cout << cos( a.value() ) << std::endl;

    Eigen::Matrix< double, Eigen::Dynamic, 1 > v( 3 );
    v << 1.0, 2.0, 3.0;

    Eigen::Matrix< double, Eigen::Dynamic, 1 > u( 3 );
    u << -2.0, 3.0, -1.0;


    const auto s = metal::create( v, "s" );
    std::cout << s << std::endl;

    const auto r = metal::create( u, "r" );
    std::cout << r << std::endl;

    const metal::Scalar d = s.dot( r );
    std::cout << d << std::endl;

    // const auto cr = metal::Vector3{ s }.cross( v );
    const auto cr = metal::Vector3{ s }.cross( metal::Vector3{ r } );
    std::cout << std::setprecision( 3 ) << cr << std::endl;

    // Eigen::cross( s, v );
    // auto e = metal::create( v, "e" );
    // e = e * metal::Scalar{ 2.0 };

    return 0;
}
