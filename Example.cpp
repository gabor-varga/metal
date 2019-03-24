#include "include/Core.h"


int main()
{
    metal::Scalar a{ 1.0, "a" };
    // metal::Scalar b{ 2.0, "b" };
    // metal::Scalar c{ 3.0, "c" };
    // metal::Scalar x = -sin( a + b ) + 0.5 * c;
    // std::cout << x << std::endl;

    const auto y = sin( a );
    std::cout << y.at( a.parameters().front() ) << std::endl;
    // std::cout << metal::Scalar{ y } << std::endl;
    // std::cout << cos( a.value() ) << std::endl;

    return 0;
}
