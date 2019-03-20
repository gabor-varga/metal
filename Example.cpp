#include "include/Core.h"


int main()
{
    metal::Scalar a{ 1.0, "a" };
    metal::Scalar b{ 2.0, "b" };
    metal::Scalar c{ 3.0, "c" };
    metal::Scalar x = sin( a ) * 0.5 + b * c;

    std::cout << x << std::endl;

    return 0;
}
