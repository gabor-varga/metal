#include "include/Core.h"


int main()
{
    metal::Scalar x{ 2.0, "x" };
    std::cout << x << std::endl;

    // auto y = 4.0 * ( x * 3.0 + 1.5 );
    const auto y = 4.0 * ( sin( x ) * 3.0 + 1.5 );
    // auto y = sin( x );
    // auto y = 4.0 * sin( x );
    // auto y = x * 3.0;
    // auto y = x * 2.0;

    // const auto p = x.parameters().front();
    // std::cout << y.at( p ) << std::endl;
    
    metal::Scalar z = y;
    std::cout << z << std::endl;

    return 0;
}
