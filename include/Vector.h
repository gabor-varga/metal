#ifndef METAL_VECTOR_H
#define METAL_VECTOR_H


#include "Core.h"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <Eigen/Geometry>
#pragma clang diagnostic pop
#elif defined __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <Eigen/Geometry>
#pragma GCC diagnostic pop
#else
#include <Eigen/Geometry>
#endif


namespace Eigen
{

template<>
struct NumTraits< metal::Scalar > : NumTraits< double >
{
    using Real = metal::Scalar;
    using NonInteger = metal::Scalar;
    using Nested = metal::Scalar;
    using Literal = double;

    enum
    {
        IsComplex = 0,
        IsInteger = 0,
        IsSigned = 1,
        RequireInitialization = 1,
        ReadCost = 1,
        AddCost = 3,
        MulCost = 3
    };
};

template< typename BinaryOp >
struct ScalarBinaryOpTraits< metal::Scalar, double, BinaryOp >
{
    using ReturnType = metal::Scalar;
};

template< typename BinaryOp >
struct ScalarBinaryOpTraits< double, metal::Scalar, BinaryOp >
{
    using ReturnType = metal::Scalar;
};

} // Eigen


namespace metal
{

template< int Rows, int Cols >
using MatrixT = Eigen::Matrix< metal::Scalar, Rows, Cols >;

using Vector = MatrixT< -1, 1 >;
using Vector3 = MatrixT< 3, 1 >;


inline Vector create( const Eigen::Matrix< double, -1, 1 >& value, const std::string& name )
{
    const auto dim = value.size();
    Vector out{ dim };
    const auto partial = Eigen::Matrix< double, -1, -1 >::Identity( dim, dim );

    const auto p = std::make_shared< NamedParameter >( dim, name );
    for ( int i = 0; i < dim; i++ )
    {
        out[i] = metal::Scalar{ value[i], p, partial.row( i ) };
    }
    return out;
}

} // metal

#endif // METAL_VECTOR_H
